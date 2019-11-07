#include "Transform.h"

namespace Oz
{
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
	template <typename T>
	void cTransform::lookAt(std::weak_ptr<T> _object)
	{
		if (_object != std::static_pointer_cast<cGameObject>)
		{
			throw Oz::Exception("GameObject not found!");
		}


	}

	//Look at object with a certain rotation
	template <typename T>
	void cTransform::lookAt(std::weak_ptr<T> _object, glm::vec3 _rotation)
	{
		if (_object != std::static_pointer_cast<cGameObject>)
		{
			throw Oz::Exception("GameObject not found!");
		}

		
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

	cTransform::~cTransform()
	{

	}
}