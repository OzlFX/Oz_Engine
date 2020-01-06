#include "Components/ComponentIncludes.h"
#include "Resources.h"
#include "Core.h"
#include "RenderSystem/ShaderProgram.h"

namespace Oz
{
	void cCamera::onInit()
	{
		m_Projection = glm::perspective(glm::radians(45.0f), getCore()->getWinSize().x / getCore()->getWinSize().y, 0.1f, 100.0f);
		m_ViewMatrix = glm::mat4(1.0f);
		//m_Shaders = getCore()->getShaders();
	}

	void cCamera::onBegin()
	{
		std::shared_ptr<cTransform> transform = getGameObject()->getComponent<cTransform>();

		m_Projection = glm::perspective(glm::radians(45.0f), getCore()->getWinSize().x / getCore()->getWinSize().y, 0.1f, 100.0f);
		m_ViewMatrix = glm::mat4(1.0f);

		m_ViewMatrix = glm::inverse(getGameObject()->getTransform()->getModel());
	}

	void cCamera::onUpdate()
	{
		std::shared_ptr<cTransform> transform = getGameObject()->getComponent<cTransform>();

		m_Projection = glm::perspective(glm::radians(45.0f), getCore()->getWinSize().x / getCore()->getWinSize().y, 0.1f, 100.0f);
		m_ViewMatrix = glm::mat4(1.0f);

		//Camera offset
		//transform->setPos((transform->getPos() + glm::vec3(0.0, 0.01, 0.0)));
		//transform->setRotation((transform->getRotation() + glm::vec3(0.0, 0.01, 0.0)));

		m_ViewMatrix = glm::inverse(getGameObject()->getTransform()->getModel());

		//m_ViewMatrix = glm::translate(m_ViewMatrix, transform->getPos());
		//m_ViewMatrix = glm::rotate(m_ViewMatrix, glm::radians(transform->getRotation().x), glm::vec3(1, 0, 0));
		//m_ViewMatrix = glm::rotate(m_ViewMatrix, glm::radians(transform->getRotation().y), glm::vec3(0, 1, 0));
		//m_ViewMatrix = glm::rotate(m_ViewMatrix, glm::radians(transform->getRotation().z), glm::vec3(0, 0, 1));

		//std::list<std::shared_ptr<cShaderProgram>>::iterator it = m_Shaders.begin();
		//(*it)->setUniform("in_Projection", m_Projection);

		///Maybe????
		//for (std::list<std::shared_ptr<cShaderProgram>>::iterator it = m_Shaders.begin(); 
		//	it != m_Shaders.end(); it++)
		//{
		//	(*it)->setUniform("in_View", glm::inverse(m_ViewMatrix));
		//}
	}

	//Get the camera view
	glm::mat4 cCamera::getView() const
	{
		return m_ViewMatrix;
	}
	
	//Get the projection
	glm::mat4 cCamera::getProjection() const
	{
		return m_Projection;
	}
}