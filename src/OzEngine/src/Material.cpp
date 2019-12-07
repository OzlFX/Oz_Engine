#include "RenderSystem/ShaderProgram.h"
#include "Texture.h"
#include "Material.h"
#include "MaterialAttribute.h"
#include "Context.h"

namespace Oz
{
	//Set the Shader
	void cMaterial::setShader(std::weak_ptr<cShaderProgram> _shader)
	{
		m_Shader = _shader; //Set the shader :P
	}

	std::shared_ptr<cMaterial> cMaterial::Create()
	{
		std::shared_ptr<cMaterial> material = m_Context->createMaterial();
		material->m_Self = material;

		return material;
	}

	std::shared_ptr<cMaterial> cMaterial::Load(std::string& _path)
	{
		m_Self.lock()->m_Shader.lock()->Load(_path);

		return m_Self.lock();
	}

	void cMaterial::setValue(std::string _name, std::weak_ptr<cTexture> _texture)
	{
		for (std::list<cMaterialAttribute>::iterator it = m_Attrib.begin(); it != m_Attrib.end(); it++)
		{
			m_Self.lock()->m_Shader.lock()->setUniform("in_Texture", _texture);

			m_Attrib.push_back(*it);
		}
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