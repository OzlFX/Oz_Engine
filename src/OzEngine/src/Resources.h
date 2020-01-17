#ifndef _CRESOURCES_H_
#define _CRESOURCES_H_

#include <memory>
#include <list>
#include <fstream>
#include <iostream>

#include "Mesh.h"
#include "Texture.h"
#include "Material.h"
#include "Sound.h"

namespace Oz
{
	class cResource;

	class cResources
	{
		friend class cCore;

	private:

		std::list<std::shared_ptr<cResource>> m_Resources;

	public:

		//Load a resource with a single string to the engine
		template <typename T>
		std::shared_ptr<T> Load(std::string _path)
		{
			std::shared_ptr<T> resource; //Make a new resource

			try
			{
				resource = resource->Create(); //Create the resource
			}
			catch (Oz::Exception& excp)
			{
				std::cout << "Oz Engine Error: " << excp.what() << std::endl;
			}

			resource->Load(_path); //Load a resource		

			m_Resources.push_back(resource); //add new resource to the list
			return resource;
		}

		//Load a resource without a string to the engine
		template <typename T>
		std::shared_ptr<T> Load()
		{
			std::shared_ptr<T> resource; //Make a new resource

			try
			{
				resource = resource->Create(); //Create the resource
			}
			catch (Oz::Exception& excp)
			{
				std::cout << "Oz Engine Error: " << excp.what() << std::endl;
			}

			m_Resources.push_back(resource); //add new resource to the list
			return resource;
		}

		/* Create a custom material file to use in the engine. Requires: Name, texture, normal, roughness, metallic,
		/* AO map, shader, ambient, diffuse, specular and shininess properties */
		void createMaterial(std::string _name, 
			std::string _texture, std::string _normal, std::string _roughness, std::string _metallic, std::string _AO,
			std::string _shader, glm::vec3 _ambient, glm::vec3 _diffuse, glm::vec3 _specular, float _shininess)
		{
			std::string ambient = std::to_string(_ambient.x) + " " + std::to_string(_ambient.y) + " " + std::to_string(_ambient.z);
			std::string diffuse = std::to_string(_diffuse.x) + " " + std::to_string(_diffuse.y) + " " + std::to_string(_diffuse.z);
			std::string specular = std::to_string(_specular.x) + " " + std::to_string(_specular.y) + " " + std::to_string(_specular.z);
			std::string shininess = std::to_string(_shininess);

			try
			{
				std::ofstream file("../src/Resources/Materials/" + _name + ".m4t", std::ios::out);

				file << "#Material" <<
					std::endl <<
					"string Name = " + _name
					+ ";" <<
					std::endl <<
					"string Texture src = "
					+ _texture
					+ ";" <<
					std::endl <<
					"string Normal src = "
					+ _normal
					+ ";" <<
					std::endl <<
					"string Roughness src = "
					+ _roughness
					+ ";" <<
					std::endl <<
					"string Metallic src = "
					+ _metallic
					+ ";" <<
					std::endl <<
					"string Disperse src = "
					+ _AO
					+ ";" <<
					std::endl <<
					"string Shader src = "
					+ _shader
					+ ";" <<
					std::endl <<
					"vec3 Ambient = "
					+ ambient
					+ ";" <<
					std::endl <<
					"vec3 Diffuse = "
					+ diffuse
					+ ";" <<
					std::endl <<
					"vec3 Specular = "
					+ specular
					+ ";" <<
					std::endl <<
					"vec3 Shininess = "
					+ shininess
					+ ";";
				file.close();
			}
			catch (Oz::Exception& excp)
			{
				std::cout << "Oz Engine Error: " << excp.what() << std::endl;
			}
		}
	};
}

#endif