#ifndef	_CCAMERA_H_
#define _CCAMERA_H_

#include "Components.h"
#include "Exception.h"

#include <glm/glm.hpp>

namespace Oz
{
	class cCamera : public cComponent
	{
	private:


	public:

		glm::mat4 getView(); //Get the camera view
		glm::mat4 getProjection(); //Get the projection

	};
}

#endif