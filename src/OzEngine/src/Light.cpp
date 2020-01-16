#include "Components/ComponentIncludes.h"
#include "Light.h"
#include "Core.h"

#include "RenderSystem/ShaderProgram.h"

namespace Oz
{
	//Light
	//void cLight::setShadowInfo(std::shared_ptr<cShadowInfo> _shadowInfo)
	//{
	//	if (m_ShadowInfo) m_ShadowInfo = NULL;
	//	m_ShadowInfo = _shadowInfo;
	//}

	void cLight::onInit(glm::vec3 _colour, float _intensity)
	{
		m_Colour = _colour;
		m_Intensity = _intensity;
	}

	void cLight::onBegin()
	{
		//m_LightProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, m_NearPlane, m_FarPlane);
		//m_LightView = glm::lookAt(getGameObject()->getTransform()->getPos(),
		//	glm::vec3(0.0f), glm::vec3(0.0, 1.0, 0.0));
		//m_LightSpaceMatrix = m_LightProjection * m_LightView;
	}

	//std::shared_ptr<cShadowInfo> cLight::getShadowInfo()
	//{
	//	return m_ShadowInfo;
	//}

	//Directional light
	/*void cDirectionalLight::onInit(glm::vec3 _colour, float _intensity, glm::vec3 _emissive,
		glm::vec3 _ambient, glm::vec3 _specular, glm::vec3 _diffuse)
	{
		m_Colour = _colour;
		m_Intensity = _intensity;

		m_Emissive = _emissive;
		m_Ambient = _ambient;
		m_Specular = _specular;
		m_Diffuse = _diffuse;

		//m_Shader = getCore()->loadShader("");
	}

	glm::vec3 cDirectionalLight::getEmissive()
	{
		return m_Emissive;
	}

	glm::vec3 cDirectionalLight::getAmbient()
	{
		return m_Ambient;
	}

	glm::vec3 cDirectionalLight::getSpecular()
	{
		return m_Specular;
	}

	glm::vec3 cDirectionalLight::getDiffuse()
	{
		return m_Diffuse;
	}

	//Point light
	void cPointLight::onInit(glm::vec3 _colour, float _intensity, glm::vec3 _emissive,
		glm::vec3 _ambient, glm::vec3 _specular, glm::vec3 _diffuse, float _constant, float _linear, float _quadratic)
	{
		m_Colour = _colour;
		m_Intensity = _intensity;

		m_Emissive = _emissive;
		m_Ambient = _ambient;
		m_Specular = _specular;
		m_Diffuse = _diffuse;
		m_Constant = _constant;
		m_Linear = _linear;
		m_Quadratic = _quadratic;
	}

	float cPointLight::getConstant()
	{
		return m_Constant;
	}

	float cPointLight::getLinear()
	{
		return m_Linear;
	}

	float cPointLight::getQuadratic()
	{
		return m_Quadratic;
	}

	void cSpotLight::onInit(glm::vec3 _colour, float _intensity, glm::vec3 _emissive,
		glm::vec3 _ambient, glm::vec3 _specular, glm::vec3 _diffuse, float _constant, 
		float _linear, float _quadratic, float _cutOffPoint)
	{
		m_Colour = _colour;
		m_Intensity = _intensity;

		m_Emissive = _emissive;
		m_Ambient = _ambient;
		m_Specular = _specular;
		m_Diffuse = _diffuse;
		m_Constant = _constant;
		m_Linear = _linear;
		m_Quadratic = _quadratic;
		m_CutoffPoint = _cutOffPoint;
	}*/
}