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

	class cCamera : public cComponent
	{
	private:

		//Vars
		glm::mat4 m_ViewMatrix, m_Projection;
		//std::list<std::shared_ptr<cShaderProgram>> m_Shaders;

	public:

		glm::mat4 getView() const; //Get the camera view
		glm::mat4 getProjection() const; //Get the projection

		//Functions
		void onBegin(); //On start
		void onInit(); //Initialise variables when called
		void onUpdate(); //Udates camera each frame

	};
}

#endif