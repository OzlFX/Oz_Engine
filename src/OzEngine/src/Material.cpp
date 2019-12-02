#include "RenderSystem/ShaderProgram.h"
#include "Texture.h"
#include "Material.h"

namespace Oz
{
	//Set the Shader
	void cMaterial::setShader(std::weak_ptr<cShaderProgram> _shader)
	{
		m_Shader = _shader; //Set the shader :P
	}

	std::shared_ptr<cMaterial> cMaterial::Load(std::string& _path)
	{
		std::shared_ptr<cMaterial> material = std::make_shared<cMaterial>();
		material->m_Self = material;

		material->setShader(std::make_shared<cShaderProgram>(_path));

		return material;
	}

	void cMaterial::setValue(std::string _name, std::weak_ptr<cTexture> _value)
	{
		//m_Shader.lock()->setUniform(_name, _value);
	}

	void cMaterial::setValue(std::string _name, float _value)
	{
		m_Shader.lock()->setUniform(_name, _value);
	}

	std::shared_ptr<cShaderProgram> cMaterial::getShader()
	{
		return m_Shader.lock();
	}

	cMaterial::~cMaterial()
	{

	}
}