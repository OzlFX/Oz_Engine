#include "Components/ComponentIncludes.h"
#include <glm/gtc/matrix_transform.hpp>

namespace Oz
{
	void cTransform::onInit()
	{
		m_Pos = glm::vec3(0.0f, 0.0f, 0.0f);
		m_Scale = glm::vec3(1.0f, 1.0f, 1.0f);
		m_Rotation = glm::vec3(0.0f, 0.0f, 0.0f);
	}

	//Initialize transforms
	void cTransform::onInit(glm::vec3 _pos, glm::vec3 _scale, glm::vec3 _rotation)
	{
		m_Pos = _pos;
		m_Scale = _scale;
		m_Rotation = _rotation;
	}

	//Update Transforms
	void cTransform::onUpdate(glm::vec3 _pos, glm::vec3 _scale, glm::vec3 _rotation)
	{
		m_Pos += _pos;
		m_Scale += _scale;
		m_Rotation += _rotation;
	}

	//Look at object
	void cTransform::lookAt(std::weak_ptr<cGameObject> _object)
	{
		glm::vec3 dirToObject;

		glm::vec3 startPos = getGameObject()->getComponent<cTransform>()->getPos();
		glm::vec3 destPos = _object.lock()->getComponent<cTransform>()->getPos();

		dirToObject.x = startPos.x - destPos.x;
		dirToObject.y = startPos.y - destPos.y;
		dirToObject.z = startPos.z - destPos.z;

		glm::vec3 rotObject;

		if (startPos.y == destPos.y)
		{
			//rotObject = sin(startPos, destPos);
		}

		//Set the rotation of the object towards the destination
		getGameObject()->getComponent<cTransform>()->getRotation() = rotObject;
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