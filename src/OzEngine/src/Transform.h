#ifndef _TRANSFORM_H_
#define _TRANSFORM_H_

//Includes
#include "Components.h"
#include "Exception.h"

#include <glm/glm.hpp>

namespace Oz
{
	class cTransform : public Oz::cComponent
	{
	private:

		glm::vec3 m_Pos;
		glm::vec3 m_Scale;
		glm::vec3 m_Rotation;

	public:

		//Setters
		void setPos(glm::vec3 _pos);
		void setScale(glm::vec3 _scale);
		void setRotation(glm::vec3 _rotation);

		void onInit(glm::vec3 _pos, glm::vec3 _scale, glm::vec3 _rotation);
		void onUpdate(glm::vec3 _pos, glm::vec3 _scale, glm::vec3 _rotation);

		//Look at object
		template <typename T>
		void lookAt(std::weak_ptr<T> _object);

		//Look at object with a certain rotation
		template <typename T>
		void lookAt(std::weak_ptr<T> _object, glm::vec3 _rotation);

		void lookAt(glm::vec3 _worldPos); //Look at position in the world
		void lookAt(glm::vec3 _worldPos, glm::vec3 _rotation); //Look at position in the world with specific rotation

		void Translate(glm::vec3 _translation); //Vector3 Translation
		void Translate(float _x, float _y, float _z); //Float Translation
		void Translate(glm::vec3 _translation, std::weak_ptr<cTransform> _relativeTo); //Vector3 Translation relative to another object's Transform
		void Translate(float _x, float _y, float _z, std::weak_ptr<cTransform> _relativeTo); //Float Translation relative to another object's Transform

		//Getters
		glm::vec3 getPos();
		glm::vec3 getScale();
		glm::vec3 getRotation();

		~cTransform();
	};
}

#endif // !_TRANSFORM_H_