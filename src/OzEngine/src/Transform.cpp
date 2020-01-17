#include "Components/ComponentIncludes.h"
#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>
#include <cmath>

namespace Oz
{
	//Initialize transforms
	void cTransform::onInit(glm::vec3 _pos, glm::vec3 _rotation, glm::vec3 _scale)
	{
		m_Pos = _pos;
		m_Scale = _scale;
		m_Rotation = _rotation;
	}

	glm::vec3 cTransform::getForward()
	{
		glm::mat4 t(1.0f);

		t = glm::rotate(t, glm::radians(m_Rotation.x), glm::vec3(1, 0, 0));
		t = glm::rotate(t, glm::radians(m_Rotation.y), glm::vec3(0, 1, 0));
		t = glm::rotate(t, glm::radians(m_Rotation.z), glm::vec3(0, 0, 1));
		t = glm::translate(t, glm::vec3(0, 0, 1));

		m_Forward = t * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);

		m_Forward = -glm::normalize(m_Forward);

		return m_Forward;
	}

	glm::vec3 cTransform::getRight()
	{
		glm::mat4 t(1.0f);

		float currentrot = m_Rotation.y;

		t = glm::rotate(t, glm::radians(m_Rotation.x), glm::vec3(1, 0, 0));
		t = glm::rotate(t, glm::radians(m_Rotation.y), glm::vec3(0, 1, 0));
		t = glm::rotate(t, glm::radians(m_Rotation.z), glm::vec3(0, 0, 1));

		t = glm::translate(t, glm::vec3(1, 0, 0));

		m_Right = t * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);

		m_Right = glm::normalize(m_Right);

		return m_Right;
	}

	//Look at object
	void cTransform::lookAt(std::weak_ptr<cGameObject> _object)
	{
		if (getGameObject()->getComponent<cCamera>())
		{
			glm::lookAt(getGameObject()->getComponent<cCamera>()->getTransform()->getPos(), _object.lock()->getTransform()->getPos(), glm::vec3(0.0f, 1.0f, 0.0f));
		}
		else
		{
			glm::vec3 distance = getGameObject()->getTransform()->getPos() - _object.lock()->getTransform()->getPos();
			glm::vec3 newRot;
			newRot.x = sin(getGameObject()->getTransform()->getRotation().y);
			newRot.y = sin(getGameObject()->getTransform()->getRotation().x);
			newRot.z = cos(getGameObject()->getTransform()->getRotation().y);

			glm::vec3 dirA = newRot;
			glm::vec3 dirB = glm::normalize(distance);

			float rotAngle = (float)acos(glm::dot(dirA, dirB));
			glm::vec3 rotAxis = glm::cross(dirA, dirB);
			rotAxis = glm::normalize(rotAxis);

			glm::vec3 temp = getGameObject()->getTransform()->getRotation();
			getGameObject()->getTransform()->setRotation(temp + (rotAngle * rotAxis.y));
		}
	}

	//Look at object with a certain rotation
	void cTransform::lookAt(std::weak_ptr<cGameObject> _object, glm::vec3 _rotation)
	{
		
	}

	//Look at position in the world
	void cTransform::lookAt(glm::vec3 _worldPos)
	{
		glm::vec3 distance = _worldPos - m_Pos;
	}

	//Look at position in the world with specific rotation
	void cTransform::lookAt(glm::vec3 _worldPos, glm::vec3 _rotation)
	{

	}

	//Vector3 Translation
	void cTransform::Translate(glm::vec3 _translation)
	{

	}


	//Float Translation
	void cTransform::Translate(float _x, float _y, float _z)
	{

	}

	//Vector3 Translation relative to another object's Transform
	void cTransform::Translate(glm::vec3 _translation, std::weak_ptr<cTransform> _relativeTo)
	{

	}

	//Float Translation relative to another object's Transform
	void cTransform::Translate(float _x, float _y, float _z, std::weak_ptr<cTransform> _relativeTo)
	{

	}

	//Set the position
	void cTransform::setPos(glm::vec3 _pos)
	{
		m_Pos = _pos;
	}

	void cTransform::setScale(glm::vec3 _scale)
	{
		m_Scale = _scale;
	}

	void cTransform::setRotation(glm::vec3 _rotation)
	{
		m_Rotation = _rotation;
	}

	void cTransform::setForward(glm::vec3 _forward)
	{
		m_Forward = _forward;
	}

	//Get Pos
	glm::vec3 cTransform::getPos()
	{
		return m_Pos;
	}

	//Get Scale
	glm::vec3 cTransform::getScale()
	{
		return m_Scale;
	}

	//Get Rotation
	glm::vec3 cTransform::getRotation()
	{
		return m_Rotation;
	}

	//Get the model matrix
	glm::mat4 cTransform::getModel()
	{
		glm::mat4 modelMat(1.0f);
		modelMat = glm::translate(modelMat, m_Pos);

		modelMat = glm::rotate(modelMat, m_Rotation.y, glm::vec3(0, 1, 0));
		modelMat = glm::rotate(modelMat, m_Rotation.x, glm::vec3(1, 0, 0));
		modelMat = glm::rotate(modelMat, m_Rotation.z, glm::vec3(0, 0, 1));

		modelMat = glm::scale(modelMat, m_Scale);

		return modelMat;
	}

	cTransform::~cTransform()
	{

	}
}