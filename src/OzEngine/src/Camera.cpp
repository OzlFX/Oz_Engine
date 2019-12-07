#include "Camera.h"
#include "Context.h"
#include "Transform.h"
#include "RenderSystem/ShaderProgram.h"

namespace Oz
{
	void cCamera::onInit()
	{
		//std::shared_ptr<cCamera> camera = std::make_shared<cCamera>();
		//camera->m_Self = camera;

		
	}

	void cCamera::onUpdate()
	{
		std::shared_ptr<cTransform> transform = m_Self.lock()->getTransform();

		transform->setPos((transform->getPos() + glm::vec3(0.0, 0.01, 0.0)));
		transform->setRotation((transform->getRotation() + glm::vec3(0.0, 0.01, 0.0)));

		glm::mat4 model(1.0f);
		model = glm::translate(model, transform->getPos());
		model = glm::rotate(model, glm::radians(transform->getRotation().x), glm::vec3(1, 0, 0));
		model = glm::rotate(model, glm::radians(transform->getRotation().y), glm::vec3(0, 1, 0));
		model = glm::rotate(model, glm::radians(transform->getRotation().z), glm::vec3(0, 0, 1));

		//for (std::list<std::shared_ptr<cShaderProgram>>::iterator it = m_Shaders.begin(); it != m_Shaders.end(); it++)
		//{
		//	m_Shaders.front()++;
		//		shader->setUniform("in_View", glm::inverse(model));
		//}

		///Maybe????
		std::list<std::shared_ptr<cShaderProgram>>::iterator it = m_Shaders.begin();
		for (int i = 0; i < m_Shaders.size(); i++)
		{
			std::advance(it, i);
		}
	}

	void cCamera::addShader(std::weak_ptr<cShaderProgram> _shader)
	{
		m_Shaders.push_back(_shader.lock()); //Add new shader to render from
	}

	//Get the camera view
	glm::mat4 cCamera::getView()
	{
		
	}
	
	//Get the projection
	glm::mat4 cCamera::getProjection()
	{
	
	}

	void cCamera::setProjection()
	{
		m_Shader->setUniform("in_Projection", glm::perspective(glm::radians(45.0f), 512.0f / 512.0f, 0.1f, 100.0f));
	}
}