#include "Environment.h"

namespace Oz
{
	void cEnvironment::calcFrames()
	{
		//Calculate the deltatime
		m_CurrentTime = SDL_GetTicks();	//Get the ticks since the program's start
		m_DeltaTime = (float)(m_CurrentTime - m_LastTime) / 1000.0f; //Convert to float and divide by 1 second
	}

	//Cap the FPS
	void cEnvironment::capFPS(float _framerate)
	{
		if (m_DeltaTime < (1.0f / _framerate))
		{
			SDL_Delay((unsigned int)(((1.0f / _framerate) - m_DeltaTime)*1000.0f));
		}

		m_LastTime = m_CurrentTime;
	}

	//Get deltatime
	float cEnvironment::getDeltaTime()
	{
		return m_DeltaTime;
	}
}