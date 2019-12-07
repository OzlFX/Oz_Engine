#ifndef _CMATERIAL_H_
#define _CMATERIAL_H_

#include <memory>
#include <list>
#include <string>

#include "Resource.h"

namespace Oz
{
	class cContext;
	class cShaderProgram;
	class cMaterialAttribute;
	class cTexture;

	class cMaterial : private cNonCopyable, public cResource
	{
		friend class cContext;
		friend class cResources;

	private:

		std::shared_ptr<cContext> m_Context;
		std::weak_ptr<cShaderProgram> m_Shader;
		std::weak_ptr<cMaterial> m_Self;
		std::list<cMaterialAttribute> m_Attrib;

	public:

		std::shared_ptr<cMaterial> Create();
		std::shared_ptr<cMaterial> Load(std::string& _path);

		void setShader(std::weak_ptr<cShaderProgram> _shader); //Set the shader

		void setValue(std::string _name, std::weak_ptr<cTexture> _texture); //Set the name and texture
		void setValue(std::string _name, float _value); //Set the value with a float

		std::shared_ptr<cShaderProgram> getShader(); //Get the shader

		~cMaterial();
	};
}

#endif