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
		m_Shaders = getCore()->getShaders();
		m_Pos = getGameObject()->getTransform()->getPos();
		m_Rotation = getGameObject()->getTransform()->getRotation();
	}

	void cCamera::onBegin()
	{
		m_Projection = glm::perspective(glm::radians(45.0f), getCore()->getWinSize().x / getCore()->getWinSize().y, 0.1f, 10000.0f);
	}

	void cCamera::onUpdate()
	{
		m_Projection = glm::perspective(glm::radians(45.0f), getCore()->getWinSize().x / getCore()->getWinSize().y, 0.1f, 10000.0f);
		
		m_Pos = getGameObject()->getTransform()->getPos();
		m_Rotation = getGameObject()->getTransform()->getRotation();

		//Camera offset


		//m_ViewMatrix = glm::inverse(getGameObject()->getTransform()->getModel());
		m_ViewMatrix = glm::mat4(1.0f);
		m_ViewMatrix = glm::translate(m_ViewMatrix, m_Pos);
		m_ViewMatrix = glm::rotate(m_ViewMatrix, glm::radians(m_Rotation.x), glm::vec3(1, 0, 0));
		m_ViewMatrix = glm::rotate(m_ViewMatrix, glm::radians(m_Rotation.y), glm::vec3(0, 1, 0));
		m_ViewMatrix = glm::rotate(m_ViewMatrix, glm::radians(m_Rotation.z), glm::vec3(0, 0, 1));

		//m_ViewMatrix = glm::rotate(m_ViewMatrix, glm::radians(0.0f), glm::vec3(0, 1, 0));

		///Maybe????
		for (std::list<std::shared_ptr<cShaderProgram>>::iterator it = m_Shaders.begin(); 
			it != m_Shaders.end(); it++)
		{
			(*it)->setUniform("in_View", glm::inverse(m_ViewMatrix));
		}
	}

	std::shared_ptr<cTransform> cCamera::getTransform()
	{
		return getGameObject()->getComponent<cTransform>();
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