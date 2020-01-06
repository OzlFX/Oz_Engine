#include "Context.h"
#include "Texture.h"
#include "RenderTexture.h"
#include "Mesh.h"
#include "Material.h"
#include "RenderSystem/ShaderProgram.h"
#include "RenderSystem/VertexBuffer.h"

#include <iostream>
#include <GL/glew.h>

namespace Oz
{
	std::shared_ptr<cContext> cContext::Init()
	{
		std::shared_ptr<cContext> context = std::make_shared<cContext>();

		//Initialise glew
		if (glewInit() != GLEW_OK)
		{
			//if glew fails to initialises, an error is returned to the console and throws an exception
#if _DEBUG
			std::cout << "ERROR: unable to initialize glew!" << std::endl;
#endif
			throw std::exception();
		}

		// Open up the OpenAL device
		context->m_Device = alcOpenDevice(NULL);

		if (context->m_Device == NULL)
		{
			throw std::exception();
		}

		// Create audio context
		context->m_SoundContext = alcCreateContext(context->m_Device, NULL);

		if (context->m_SoundContext == NULL)
		{
			alcCloseDevice(context->m_Device);
			throw std::exception();
		}

		// Set as current context
		if (!alcMakeContextCurrent(context->m_SoundContext))
		{
			alcDestroyContext(context->m_SoundContext);
			alcCloseDevice(context->m_Device);
			throw std::exception();
		}

		// Generally not needed. Translate sources instead
		alListener3f(AL_POSITION, 0.0f, 0.0f, 0.0f);

		context->m_Self = context;

		return context;
	}
}