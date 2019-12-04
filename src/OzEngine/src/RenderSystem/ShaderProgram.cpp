#include "ShaderProgram.h"
#include "VertexArray.h"
#include "OzEngine/src/Context.h"
#include "OzEngine/src/Mesh.h"
#include "OzEngine/src/Exception.h"

#include <glm/ext.hpp>

#include <fstream>
#include <iostream>

namespace Oz
{
	cShaderProgram::cShaderProgram()
	{
		const GLchar *src = NULL;

		std::string vert = "";
		vert += "#version 120\n";
		vert += "#define VERTEX\n";
		vert += m_Path;
		
		src = vert.c_str(); //Convert vertex string into GLchar for the GPU to use

		GLuint vertexShaderId = glCreateShader(GL_VERTEX_SHADER); //Create the vertex shader
		glShaderSource(vertexShaderId, 1, &src, NULL); //Set the shader source and get the vertex shader file contents
		glCompileShader(vertexShaderId); //Compile the shader
		GLint success = 0;
		glGetShaderiv(vertexShaderId, GL_COMPILE_STATUS, &success);

		//Check if compile was successful
		if (!success)
		{
			int length = 0;
			glGetShaderiv(vertexShaderId, GL_INFO_LOG_LENGTH, &length);

			std::vector<char> infoLog(length);
			glGetShaderInfoLog(vertexShaderId, length, NULL, &infoLog.at(0));

			glDeleteShader(vertexShaderId);

			std::string msg = &infoLog.at(0);
			throw Oz::Exception(msg);
		}

		std::string frag = "";
		frag += "#version 120\n";
		frag += "#define FRAGMENT\n";
		frag += src;

		src = frag.c_str(); //Convert fragment string into GLchar for the GPU to use

		GLuint fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER); //Create the fragment shader
		glShaderSource(fragmentShaderId, 1, &src, NULL); //Set the shader source and get the fragment shader file contents
		glCompileShader(fragmentShaderId); //Compile the shader
		glGetShaderiv(fragmentShaderId, GL_COMPILE_STATUS, &success);

		//Check if compile was successful
		if (!success)
		{
			int length = 0;
			glGetShaderiv(fragmentShaderId, GL_INFO_LOG_LENGTH, &length);

			std::vector<char> infoLog(length);
			glGetShaderInfoLog(fragmentShaderId, length, NULL, &infoLog.at(0));

			glDeleteShader(fragmentShaderId);

			std::string msg = &infoLog.at(0);
			throw Oz::Exception(msg);
		}

		m_ID = glCreateProgram(); //Create the shader program
		glAttachShader(m_ID, vertexShaderId); //Attach the vertex shader to the shader program
		glAttachShader(m_ID, fragmentShaderId); //Attach the fragment shader to the shader program

		glBindAttribLocation(m_ID, 0, "in_Position");
		glBindAttribLocation(m_ID, 1, "in_Color");
		glBindAttribLocation(m_ID, 2, "in_TexCoord");
		glBindAttribLocation(m_ID, 3, "in_lightColor");

		glLinkProgram(m_ID);
		glGetProgramiv(m_ID, GL_LINK_STATUS, &success);

		//Bind the shaders
		//glBindAttribLocation(m_ID, 0, "in_Position");
		//glBindAttribLocation(m_ID, 1, "in_Color");

		//Checks for errors
		if (glGetError() != GL_NO_ERROR)
		{
			throw Oz::Exception("Cannot bind the shaders!");
		}

		glDetachShader(m_ID, vertexShaderId); //Detach the vertex shader
		glDeleteShader(vertexShaderId); //Delete the vertex shader
		glDetachShader(m_ID, fragmentShaderId); //Detach the fragment shader
		glDeleteShader(fragmentShaderId); //Delete the fragment shader
	}

	//Create the shader
	std::shared_ptr<cShaderProgram> cShaderProgram::Create()
	{
		std::shared_ptr<cShaderProgram> shader = std::make_shared<cShaderProgram>();
		shader->m_Self = shader;

		return shader;
	}

	//Load the shader
	void cShaderProgram::Load(std::string _path)
	{
		std::ifstream file(_path.c_str());

		//Check to see if the file is open
		if (!file.is_open())
		{
			throw Oz::Exception("Cannot find file");
		}

		//Copy contents of the file into the string
		while (!file.eof())
		{
			std::string line;
			std::getline(file, line);
			m_Path += line + "\n";
		}
	}

	//Draw vertex array
	void cShaderProgram::Draw(std::weak_ptr<cVertexArray> _vertArray)
	{
		glUseProgram(m_ID); //Use the current shader program
		glBindVertexArray(_vertArray.lock()->getID());

		glDrawArrays(GL_TRIANGLES, 0, _vertArray.lock()->getVertexCount());

		glBindVertexArray(0);
		glUseProgram(0);
	}

	//Draw Mesh
	void cShaderProgram::Draw(std::shared_ptr<cMesh> _mesh)
	{
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);
		glEnable(GL_BLEND);

		glUseProgram(m_ID); //Use the current shader program
		glBindVertexArray(_mesh->getID());

		glDrawArrays(GL_TRIANGLES, _mesh->m_Faces.size(), _mesh->m_Model->getVertexCount());

		glBindVertexArray(0);
		glUseProgram(0);

		glDisable(GL_BLEND);
		glDisable(GL_CULL_FACE);
		glDisable(GL_DEPTH_TEST);
	}

	/*Set Uniform overloads */

	void cShaderProgram::setUniform(const std::string _uniform, glm::vec4 _value)
	{
		GLint uniformId = glGetUniformLocation(m_ID, _uniform.c_str());

		if (uniformId == -1)
		{
			throw std::exception();
		}

		glUseProgram(m_ID);
		glUniform4f(uniformId, _value.x, _value.y, _value.z, _value.w);
		glUseProgram(0);
	}

	void cShaderProgram::setUniform(const std::string _uniform, float _value)
	{
		GLint uniformId = glGetUniformLocation(m_ID, _uniform.c_str());

		if (uniformId == -1)
		{
			throw std::exception();
		}

		glUseProgram(m_ID);
		glUniform1f(uniformId, _value);
		glUseProgram(0);
	}

	void cShaderProgram::setUniform(const std::string _uniform, glm::mat4 _value)
	{
		GLint uniformId = glGetUniformLocation(m_ID, _uniform.c_str());

		if (uniformId == -1)
		{
			throw std::exception();
		}

		glUseProgram(m_ID);
		glUniformMatrix4fv(uniformId, 1, GL_FALSE, glm::value_ptr(_value));
		glUseProgram(0);
	}

	GLuint cShaderProgram::getID()
	{
		return m_ID;
	}

	cShaderProgram::~cShaderProgram()
	{
		glDeleteProgram(m_ID);
	}
}