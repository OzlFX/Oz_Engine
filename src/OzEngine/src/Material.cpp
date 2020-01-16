#include "Texture.h"
#include "RenderTexture.h"
#include "Material.h"
#include "MaterialAttribute.h"
#include "RenderSystem/ShaderProgram.h"

#include "Exception.h"
#include "OzEngine/src/Utilities/Util.h"

#include <fstream>
#include <iostream>

namespace Oz
{
	std::shared_ptr<cMaterial> cMaterial::Create()
	{
		std::shared_ptr<cMaterial> material = std::make_shared<cMaterial>();
		
		material->m_MaterialAttrib = std::make_shared<cMaterialAttribute>();

		material->m_Self = material;

		return material;
	}

	std::shared_ptr<cMaterial> cMaterial::Load(std::string& _path)
	{
		std::ifstream file(_path.c_str());

		//Check to see if the file is open
		if (!file.is_open())
		{
			throw Exception("Cannot find file");
		}

		std::string line;
		std::string material;
		std::vector<std::string> lines;

		//Copy contents of the file into the string
		while (!file.eof())
		{
			std::getline(file, line);
			material += line + "\n";
		}

		Oz::cUtil::splitStringLineEnding(material, lines); //Remove line endings
		if (lines.at(0) != "#Material") throw Oz::Exception("File is not of correct type! .m4t expected!");

		//
		for (std::vector<std::string>::iterator it = lines.begin(); it != lines.end(); it++)
		{
			if (it->length() < 1) continue;

			std::vector<std::string> splitLine;
			Oz::cUtil::createWords(*it, splitLine); //Remove white spaces

			if (splitLine.size() < 1) continue;

			if (splitLine.at(1) == "Name")
			{
				m_MaterialAttrib->m_Name = splitLine.at(3); //Set the material attribute's name
			}
			else if (splitLine.at(1) == "Texture")
			{
				m_MaterialAttrib->m_Texture = std::make_shared<cTexture>();
				m_MaterialAttrib->m_Texture->Load(splitLine.at(4)); //Set the matterial attribute's texture's path
			}
			else if (splitLine.at(1) == "Normal")
			{
				m_MaterialAttrib->m_Normal = std::make_shared<cTexture>();
				m_MaterialAttrib->m_Normal->Load(splitLine.at(4)); //Set the matterial attribute's texture's path
			}
			else if (splitLine.at(1) == "Roughness")
			{
				m_MaterialAttrib->m_Roughness = std::make_shared<cTexture>();
				m_MaterialAttrib->m_Roughness->Load(splitLine.at(4)); //Set the matterial attribute's texture's path
			}
			else if (splitLine.at(1) == "Metallic")
			{
				m_MaterialAttrib->m_Metallic = std::make_shared<cTexture>();
				m_MaterialAttrib->m_Metallic->Load(splitLine.at(4)); //Set the matterial attribute's texture's path
			}
			else if (splitLine.at(1) == "Disperse")
			{
				m_MaterialAttrib->m_Disperse = std::make_shared<cTexture>();
				m_MaterialAttrib->m_Disperse->Load(splitLine.at(4)); //Set the matterial attribute's texture's path
			}
			else if (splitLine.at(1) == "Shader")
			{
				m_ShaderFile1 = splitLine.at(4) + ".vert";
				m_Files.push_back(m_ShaderFile1);
				m_ShaderFile2 = splitLine.at(4) + ".frag";
				m_Files.push_back(m_ShaderFile2);
			}
			else if (splitLine.at(1) == "Ambient")
			{
				m_Ambient = glm::vec3(
					atof(splitLine.at(3).c_str()),
					atof(splitLine.at(4).c_str()),
					atof(splitLine.at(5).c_str()));
			}
			else if (splitLine.at(1) == "Diffuse")
			{
				m_Diffuse = glm::vec3(
					atof(splitLine.at(3).c_str()),
					atof(splitLine.at(4).c_str()),
					atof(splitLine.at(5).c_str()));
			}
			else if (splitLine.at(1) == "Specular")
			{
				m_Specular = glm::vec3(
					atof(splitLine.at(3).c_str()),
					atof(splitLine.at(4).c_str()),
					atof(splitLine.at(5).c_str()));
			}
			else if (splitLine.at(1) == "Shininess")
			{
				m_Shininess = atof(splitLine.at(3).c_str());
			}
		}

		return m_Self.lock();
	}

	///Currently never used
	/*void cMaterial::setValue(std::string _name, float _value)
	{
		m_Shader->setUniform(_name, _value);
	}*/

	std::shared_ptr<cTexture> cMaterial::getTexture()
	{
		return m_MaterialAttrib->m_Texture;
	}

	std::shared_ptr<cTexture> cMaterial::getNormal()
	{
		return m_MaterialAttrib->m_Normal;
	}

	std::shared_ptr<cTexture> cMaterial::getDisperse()
	{
		return m_MaterialAttrib->m_Disperse;
	}

	std::shared_ptr<cTexture> cMaterial::getRoughness()
	{
		return m_MaterialAttrib->m_Roughness;
	}

	std::shared_ptr<cTexture> cMaterial::getMetallic()
	{
		return m_MaterialAttrib->m_Metallic;
	}

	std::vector<std::string> cMaterial::getShader()
	{
		return m_Files;
	}

	cMaterial::~cMaterial()
	{

	}
}