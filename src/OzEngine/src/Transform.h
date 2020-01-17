#ifndef _CTRANSFORM_H_
#define _CTRANSFORM_H_

//Includes
#include "Components.h"
#include "Exception.h"

#include <glm/glm.hpp>
#include <list>

namespace Oz
{
	class cGameObject;

	class cTransform : public cComponent
	{
	private:

		glm::vec3 m_Pos;
		glm::vec3 m_Scale;
		glm::vec3 m_Rotation;

		glm::vec3 m_Forward;
		glm::vec3 m_Right;

		//std::list<std::shared_ptr<cGameObject>> m_Children;
		//
		//std::shared_ptr<cGameObject> m_Parent;
		//std::shared_ptr<cGameObject> m_Child;

	public:

		//Setters
		void setPos(glm::vec3 _pos); //Set the position of the object
		void setScale(glm::vec3 _scale); //Set the scale of the object
		void setRotation(glm::vec3 _rotation); //Set the rotation of the object
		void setForward(glm::vec3 _forward); //Set the forward of the object

		void onInit(glm::vec3 _pos, glm::vec3 _rotation, glm::vec3 _scale); //Initialise the object's postion, rotation and scale

		void lookAt(std::weak_ptr<cGameObject> _object); //Look at object

		void lookAt(std::weak_ptr<cGameObject> _object, glm::vec3 _rotation); //Look at object with a certain rotation

		void lookAt(glm::vec3 _worldPos); //Look at position in the world
		void lookAt(glm::vec3 _worldPos, glm::vec3 _rotation); //Look at position in the world with specific rotation

		void Translate(glm::vec3 _translation); //Vector3 Translation
		void Translate(float _x, float _y, float _z); //Float Translation
		void Translate(glm::vec3 _translation, std::weak_ptr<cTransform> _relativeTo); //Vector3 Translation relative to another object's Transform
		void Translate(float _x, float _y, float _z, std::weak_ptr<cTransform> _relativeTo); //Float Translation relative to another object's Transform

		//Getters
		glm::vec3 getPos(); //Get the object's position
		glm::vec3 getScale(); //Get the object's scale
		glm::vec3 getRotation(); //Get the object's rotation

		glm::vec3 getForward(); //Calculate the object's forward vector and return it
		glm::vec3 getRight(); //Calculate the object's right vector and return it

		glm::mat4 getModel(); //Calculate the object's model matrix and return it

		~cTransform();
	};
}

#endif