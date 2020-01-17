#ifndef	_CCAMERA_H_
#define _CCAMERA_H_

#include "Components.h"
#include "Exception.h"

#include <list>

#include <glm/glm.hpp>
#include <glm/ext.hpp>

namespace Oz
{
	class cShaderProgram;
	class cTransform;

	/* Camera to render everything within its view matrix */
	class cCamera : public cComponent
	{
	private:

		//Vars
		glm::mat4 m_ViewMatrix, m_Projection;
		glm::vec3 m_Pos, m_Rotation;
		glm::vec3 m_CameraUp;

		bool m_FirstMouse;
		float m_Yaw;
		float m_Pitch; 
		float m_LastX; 
		float m_LastY; 
		float m_Fov;

		std::list<std::shared_ptr<cShaderProgram>> m_Shaders;

	public:

		glm::mat4 getView() const; //Get the camera view
		glm::mat4 getProjection() const; //Get the projection

		void Rotate();

		//Functions
		void onBegin(); //On start
		void onInit(); //Initialise variables when called
		void onUpdate(); //Udates camera each frame

		std::shared_ptr<cTransform> getTransform();

	};
}

#endif