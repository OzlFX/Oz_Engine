#ifndef _CENVIRONMENT_H_
#define _CENVIRONMENT_H_

#include <SDL2/SDL.h>

namespace Oz
{
	class cEnvironment
	{
	private:
		unsigned int m_CurrentTime;
		unsigned int m_LastTime;
		float m_DeltaTime;

	public:

		void calcFrames();
		void capFPS(float _framerate);

		float getDeltaTime();

	};
}

#endif