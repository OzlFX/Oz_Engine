#include "VertexArray.h"
#include "VertexBuffer.h"
#include "OzEngine/src/Utilities/Util.h"
#include "OzEngine/src/Exception.h"
#include "OzEngine/src/Mesh.h"

#include <fstream>
#include <iostream>

namespace Oz
{
	cVertexArray::cVertexArray() : m_Dirty(false)
	{
		//Create new Vertex Array Object (VAO) on the GPU and bind it
		glGenVertexArrays(1, &m_ID);

		if (!m_ID)
		{
			throw std::exception();
		}

		m_Buffers.resize(10);
	}

	void cVertexArray::Load(const std::string& _path)
	{
		std::ifstream file(_path.c_str());

		if (!file.is_open())
		{
			throw std::exception();
		}
		
		std::string line;
		
		std::vector<glm::vec3> pos;
		std::vector<glm::vec2> texCoords;
		std::vector<glm::vec3> norms;
		std::vector<glm::vec2> lights;

		while (!file.eof())
		{
			std::getline(file, line);
			if (line.length() < 1) continue;

			std::vector<std::string> splitLine;
			Oz::cUtil::splitStringWhiteSpace(line, splitLine);

			if (splitLine.size() < 1) continue;

			if (splitLine.at(0) == "v") //Obtain object's pos and add it to the position vector
			{
				pos.push_back(glm::vec3(
					atof(splitLine.at(1).c_str()), 
					atof(splitLine.at(2).c_str()), 
					atof(splitLine.at(3).c_str())));
			}
			else if (splitLine.at(0) == "vt") //Obtain object's texture coordinates and add it to the texCoord vector
			{
				texCoords.push_back(glm::vec2(
					atof(splitLine.at(1).c_str()), 
					atof(splitLine.at(2).c_str())));
			}
			else if (splitLine.at(0) == "vn") //Obtain object's normals and add it to the normals vector
			{
				norms.push_back(glm::vec3(
					atof(splitLine.at(1).c_str()),
					atof(splitLine.at(2).c_str()),
					atof(splitLine.at(3).c_str())));
			}
			else if (splitLine.at(0) == "f") //Obtain object's faces and add it to the face object
			{
				if (splitLine.size() < 4) continue; //Normal face

				sFace face;
				std::vector<std::string> subsplit;
				Oz::cUtil::splitString(splitLine.at(1), '/', subsplit);

				if (subsplit.size() >= 1) face.posA = pos.at(atoi(subsplit.at(0).c_str()) - 1);
				if (subsplit.size() >= 2) face.texCoordA = texCoords.at(atoi(subsplit.at(1).c_str()) - 1);
				if (subsplit.size() >= 3) face.normA = norms.at(atoi(subsplit.at(2).c_str()) - 1);
				if (subsplit.size() >= 4) face.lightA = lights.at(atoi(subsplit.at(3).c_str()) - 1);

				Oz::cUtil::splitString(splitLine.at(2), '/', subsplit);

				if (subsplit.size() >= 1) face.posB = pos.at(atoi(subsplit.at(0).c_str()) - 1);
				if (subsplit.size() >= 2) face.texCoordB = texCoords.at(atoi(subsplit.at(1).c_str()) - 1);
				if (subsplit.size() >= 3) face.normB = norms.at(atoi(subsplit.at(2).c_str()) - 1);
				if (subsplit.size() >= 4) face.lightB = lights.at(atoi(subsplit.at(3).c_str()) - 1);

				Oz::cUtil::splitString(splitLine.at(3), '/', subsplit);

				if (subsplit.size() >= 1) face.posC = pos.at(atoi(subsplit.at(0).c_str()) - 1);
				if (subsplit.size() >= 2) face.texCoordC = texCoords.at(atoi(subsplit.at(1).c_str()) - 1);
				if (subsplit.size() >= 3) face.normC = norms.at(atoi(subsplit.at(2).c_str()) - 1);
				if (subsplit.size() >= 4) face.lightC = lights.at(atoi(subsplit.at(3).c_str()) - 1);

				m_Faces.push_back(face); //Add a new face

				if (splitLine.size() < 5) continue; //Quad face

				sFace quadFace;
				quadFace.posA = face.posC;
				quadFace.texCoordA = face.texCoordC;
				quadFace.normA = face.normC;
				quadFace.lightA = face.lightC;

				Oz::cUtil::splitString(splitLine.at(4), '/', subsplit);

				if (subsplit.size() >= 1) quadFace.posB = pos.at(atoi(subsplit.at(0).c_str()) - 1);
				if (subsplit.size() >= 2) quadFace.texCoordB = texCoords.at(atoi(subsplit.at(1).c_str()) - 1);
				if (subsplit.size() >= 3) quadFace.normB = norms.at(atoi(subsplit.at(2).c_str()) - 1);
				if (subsplit.size() >= 4) quadFace.lightB = lights.at(atoi(subsplit.at(3).c_str()) - 1);

				quadFace.posC = face.posA;
				quadFace.texCoordC = face.texCoordA;
				quadFace.normC = face.normA;
				quadFace.lightC = face.lightA;

				m_Faces.push_back(quadFace);
			}
		}
	}

	std::vector<sFace> cVertexArray::createFaces()
	{
		return m_Faces;
	}

	void cVertexArray::setBuffer(std::string _attrib, std::weak_ptr<cVertexBuffer> _buffer)
	{
		if (_attrib == "in_Position")
		{
			m_Buffers.at(0) = _buffer.lock();
		}
		else if (_attrib == "in_Color")
		{
			m_Buffers.at(1) = _buffer.lock();
		}
		else if (_attrib == "in_TexCoord")
		{
			m_Buffers.at(2) = _buffer.lock();
		}
		else if (_attrib == "in_Normal")
		{
			m_Buffers.at(3) = _buffer.lock();
		}
		else
		{
			throw std::exception();
		}

		m_Dirty = true;
	}

	int cVertexArray::getVertexCount()
	{
		if (!m_Buffers.at(0))
		{
			throw std::exception();
		}

		return m_Buffers.at(0)->getDataSize() / m_Buffers.at(0)->getComponents();
	}
	/*
	void cVertexArray::Parse(const std::string& _data)
	{
		std::string currLine;

		try
		{
			safeParse(_data, currLine); //Parse the data to be used
		}
		catch (std::exception& e)
		{
			throw Oz::Exception("Failed to obtain model: " + currLine);
		}
	}

	void cVertexArray::safeParse(const std::string& _data, std::string& _currLine)
	{
		std::vector<std::string> lines;
		Oz::cUtil::splitStringLineEnding(_data, lines);

		std::vector<glm::vec3> pos;
		std::vector<glm::vec2> texCoords;
		std::vector<glm::vec3> norms;

		for (std::vector<std::string>::iterator it = lines.begin(); it != lines.end(); it++)
		{
			_currLine = *it;
			if (it->length() < 1) continue;
#ifdef _DEBUG
			std::cout << "Line " + *it << std::endl;
#endif

			std::vector<std::string> splitLine;
			Oz::cUtil::splitStringWhiteSpace(*it, splitLine);
			if (splitLine.size() < 1) continue;

			if (splitLine.at(0) == "v")
			{
				pos.push_back(glm::vec3(atof(splitLine.at(1).c_str()), atof(splitLine.at(2).c_str()), atof(splitLine.at(3).c_str())));
			}
			else if (splitLine.at(0) == "vt")
			{
				texCoords.push_back(glm::vec2(atof(splitLine.at(1).c_str()), 1.0f - atof(splitLine.at(2).c_str())));
			}
			else if (splitLine.at(0) == "vn")
			{
				norms.push_back(glm::vec3(
				atof(splitLine.at(1).c_str()),
				atof(splitLine.at(2).c_str()),
				atof(splitLine.at(3).c_str())));
			}
		}
	}*/

	GLuint cVertexArray::getID()
	{
		if (m_Dirty)
		{
			glBindVertexArray(m_ID);

			//Add buffers and enable them
			for (size_t i = 0; i < m_Buffers.size(); i++)
			{
				if (m_Buffers.at(i))
				{
					glBindBuffer(GL_ARRAY_BUFFER, m_Buffers.at(i)->getID());

					glVertexAttribPointer(i, m_Buffers.at(i)->getComponents(), GL_FLOAT, GL_FALSE,
						m_Buffers.at(i)->getComponents() * sizeof(GLfloat), (void *)0);

					glEnableVertexAttribArray(i);
				}
				else
				{
					glDisableVertexAttribArray(i);
				}
			}

			glBindBuffer(GL_ARRAY_BUFFER, 0);
			glBindVertexArray(0);

			m_Dirty = false;
		}

		return m_ID;
	}

	cVertexArray::~cVertexArray()
	{

	}
}