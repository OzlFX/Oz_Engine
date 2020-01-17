#ifndef _CMATERIAL_H_
#define _CMATERIAL_H_

#include <glm/glm.hpp>

#include <memory>
#include <list>
#include <vector>
#include <string>

#include "Resource.h"

namespace Oz
{
	class cMaterialAttribute;
	class cTexture;
	class cRenderTexture;

	/* Material for PBR usage within the engine, handles texture and custom file loading */
	class cMaterial : private cNonCopyable, public cResource
	{
		friend class cResources;

	private:

		//Vars
		glm::vec3 m_Ambient, m_Diffuse, m_Specular;
		float m_Shininess;

		std::string m_ShaderFile1;
		std::string m_ShaderFile2;
		std::vector<std::string> m_Files;

		std::weak_ptr<cMaterial> m_Self;

		std::shared_ptr<cMaterialAttribute> m_MaterialAttrib;

	public:

		std::shared_ptr<cMaterial> Create();
		std::shared_ptr<cMaterial> Load(std::string& _path);

		//void setValue(std::string _name, float _value); //Set the value with a float
		std::shared_ptr<cTexture> getTexture(); //Get the texture
		std::shared_ptr<cTexture> getNormal(); //Get the normal texture
		std::shared_ptr<cTexture> getDisperse(); //Get the AO/disperse texture
		std::shared_ptr<cTexture> getRoughness(); //Get the roughness texture
		std::shared_ptr<cTexture> getMetallic(); //Get the metallic texture
		std::vector<std::string> getShader(); //Get the shader

		~cMaterial();
	};
}

#endif