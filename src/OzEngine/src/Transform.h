#ifndef _TRANSFORM_H_
#define _TRANSFORM_H_

//Includes
#include "Components.h"
#include "Exception.h"

#include <glm/glm.hpp>

namespace Oz
{
	class cGameObject;

	class cTransform : public cComponent
	{
	private:

		glm::vec3 m_Pos;
		glm::vec3 m_Scale;
		glm::vec3 m_Rotation;

	public:

		//cTransform(glm::vec3 _pos, glm::vec3 _scale, glm::vec3 _rotation);

		//Setters
		void setPos(glm::vec3 _pos);
		void setScale(glm::vec3 _scale);
		void setRotation(glm::vec3 _rotation);

		void onInit();
		void onInit(glm::vec3 _pos, glm::vec3 _scale, glm::vec3 _rotation);
		void onUpdate(glm::vec3 _pos, glm::vec3 _scale, glm::vec3 _rotation);

		//Look at object
		void lookAt(std::weak_ptr<cGameObject> _object);

		//Look at object with a certain rotation

		void lookAt(std::weak_ptr<cGameObject> _object, glm::vec3 _rotation);

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

		glm::mat4 getModel();

		~cTransform();
	};
}

#endif // !_TRANSFORM_H_