#include "RenderSystem/ShaderProgram.h"
#include "Texture.h"
#include "Material.h"

namespace Oz
{
	void cMaterial::setShader(std::weak_ptr<cShaderProgram> _shader)
	{

	}

	void cMaterial::setValue(std::string _name, std::weak_ptr<cTexture> _value)
	{

	}

	void cMaterial::setValue(std::string _name, float _value)
	{

	}

	std::shared_ptr<cShaderProgram> cMaterial::getShader()
	{
		return m_Shader.lock();
	}
}