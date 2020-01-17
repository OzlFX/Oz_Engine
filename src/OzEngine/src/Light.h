#ifndef _CLIGHT_H_
#define _CLIGHT_H_

//Includes
#include "Components.h"

#include <glm/glm.hpp>
#include <glm/ext.hpp>

namespace Oz
{
	/* Light Component to handle light information to be passed to the shaders */
	class cLight : public cComponent
	{
	protected:

		//glm::mat4 m_LightProjection, m_LightView;
		//glm::mat4 m_LightSpaceMatrix;
		float m_NearPlane = 1.0f, m_FarPlane = 7.5f;

		glm::vec3 m_Colour;
		float m_Intensity;

	public:

		void onInit(glm::vec3 _colour, float _intensity); //Initialise the light component with the colour and intensity of the light

		float getNearPlane() { return m_NearPlane; }
		float getFarPlane() { return m_FarPlane; }
		//glm::mat4 getLightSpaceMatrix() { return m_LightSpaceMatrix; }
		glm::vec3 getColour() { return m_Colour; }

	};
}

#endif