#ifndef _CCOLLISION_H_
#define _CCOLLISION_H_

//Includes
#include "Components.h"

#include <memory>
#include <glm/glm.hpp>

namespace Oz
{
	/* Simple box collider for objects. Size can be defined and will check if another object intersects
	/* with the object */
	class cBoxCollider : public cComponent
	{
	private:

		//Vars
		glm::vec3 m_Size;
		glm::vec3 m_Offset;
		glm::vec3 m_LastPosition;

		//Functions
		void collideBox(); //Setup the box collider
		bool isColliding(glm::vec3 _position, glm::vec3 _size); //Check whether the object has collided with something
		glm::vec3 getCollisionResponse(glm::vec3 _position, glm::vec3 _size); //Respond to the collision by stepping back

	public:

		void onInit(glm::vec3 _size, glm::vec3 _offset);// = glm::vec3(0.0f));
		void onUpdate();

	};

	/* Complex mesh collider for obejcts. Size and shape based on the mesh's size and shape.
	/* MeshCollider checks if an object collides with any part of the object */
	//class cMeshCollider : public cComponent
	//{
	//private:
	//
	//
	//
	//public:
	//
	//	
	//
	//};
}

#endif