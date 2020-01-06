#ifndef _CMATERIAL_H_
#define _CMATERIAL_H_

#include <glm/glm.hpp>

#include <memory>
#include <list>
#include <string>

#include "Resource.h"

namespace Oz
{
	class cShaderProgram;
	class cMaterialAttribute;
	class cTexture;
	class cRenderTexture;

	/*  */

	class cMaterial : private cNonCopyable, public cResource
	{
		friend class cResources;

	private:

		//Vars
		glm::vec3 m_Ambient, m_Diffuse, m_Specular;
		float m_Shininess;

		std::string m_ShaderFile;
		std::weak_ptr<cMaterial> m_Self;

		std::shared_ptr<cRenderTexture> m_RendTexture;

		std::shared_ptr<cMaterialAttribute> m_MaterialAttrib;

	public:

		std::shared_ptr<cMaterial> Create();
		std::shared_ptr<cMaterial> Load(std::string& _path);

		//void setValue(std::string _name, float _value); //Set the value with a float

		std::shared_ptr<cRenderTexture> getRendTexture(); //Get the render texture
		std::shared_ptr<cTexture> getTexture(); //Get the texture
		std::string getShader(); //Get the shader

		~cMaterial();
	};
}

#endif