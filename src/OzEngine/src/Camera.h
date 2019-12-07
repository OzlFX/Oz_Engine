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
	class cContext;

	class cCamera : public cComponent
	{
	private:

		//Vars
		std::weak_ptr<cCamera> m_Self;
		std::list<std::shared_ptr<cShaderProgram>> m_Shaders;
		std::shared_ptr<cShaderProgram> m_Shader;
		std::shared_ptr<cContext> m_Context;

		//Functions
		void onInit(); //Initialise variables when called
		void onUpdate();

	public:

		void addShader(std::weak_ptr<cShaderProgram> _shader); //Add a new shader to render 

		glm::mat4 getView(); //Get the camera view
		glm::mat4 getProjection(); //Get the projection

		void setProjection(); //Set the projection matrix

	};
}

#endif