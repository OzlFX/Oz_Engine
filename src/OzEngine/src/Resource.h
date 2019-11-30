#ifndef _CRESOURCE_H_
#define _CRESOURCE_H_

#include <string>
#include <GL/glew.h>
#include <glm/glm.hpp>

namespace Oz
{
	class cCore;

	class cResource
	{
		friend class cMesh;
		friend class cShaderProgram;
		friend class cTexture;
		friend class cMaterial;

	private:

		std::string m_Path;
	};
}

#endif