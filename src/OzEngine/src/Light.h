#ifndef _CLIGHT_H_
#define _CLIGHT_H_

#include <glm/glm.hpp>

#include "GameObject.h"

namespace Oz
{
	class cShaderProgram;
	class cMesh;

	class cLight : public cGameObject
	{
	private:

		//Vars
		std::shared_ptr<cShaderProgram> m_LightShader;

	public:

		void setValue(std::weak_ptr<cMesh> _mesh);

	};
}

#endif