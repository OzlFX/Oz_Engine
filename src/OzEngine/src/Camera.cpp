#include "Camera.h"
#include "Components/ComponentIncludes.h"
#include "Resources.h"
#include "RenderSystem/ShaderProgram.h"
#include "Input.h"

namespace Oz
{
	void cCamera::onInit()
	{
		m_Projection = glm::perspective(glm::radians(45.0f), getCore()->getWinSize().x / getCore()->getWinSize().y, 0.1f, 100.0f);
		m_ViewMatrix = glm::mat4(1.0f);
		m_Shaders = getCore()->getShaders();
		m_Pos = getGameObject()->getTransform()->getPos();
		m_Rotation = getGameObject()->getTransform()->getRotation();
		//m_CameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
		m_CameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

		m_FirstMouse = true;
		m_Yaw = -90.0f;
		m_Pitch = 0.0f;
		m_LastX = 800.0f / 2.0;
		m_LastY = 600.0 / 2.0;
		m_Fov = 45.0f;
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

	void cCamera::Rotate()
	{
		if (m_FirstMouse)
		{
			m_LastX = getCore()->getInputHandler()->getMousePos().x;
			m_LastY = getCore()->getInputHandler()->getMousePos().y;
			m_FirstMouse = false;
		}

		float xoffset = getCore()->getInputHandler()->getMousePos().x - m_LastX;
		float yoffset = m_LastY - getCore()->getInputHandler()->getMousePos().y;
		m_LastX = getCore()->getInputHandler()->getMousePos().x;
		m_LastY = getCore()->getInputHandler()->getMousePos().y;

		float sensitivity = 0.05;
		xoffset *= sensitivity;
		yoffset *= sensitivity;

		m_Yaw += xoffset;
		m_Pitch += yoffset;

		if (m_Pitch > 89.0f)
			m_Pitch = 89.0f;
		if (m_Pitch < -89.0f)
			m_Pitch = -89.0f;

		glm::vec3 direction;
		direction.x = cos(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
		direction.y = sin(glm::radians(m_Pitch));
		direction.z = sin(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
		getGameObject()->getTransform()->setForward(glm::normalize(direction));
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