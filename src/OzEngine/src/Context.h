#ifndef _CCONTEXT_H_
#define _CCONTEXT_H_

#include <memory>
#include <string>
#include <AL/al.h>
#include <AL/alc.h>

namespace Oz
{
	class cShaderProgram;
	class cVertexBuffer;
	class cMesh;
	class cTexture;
	class cMaterial;
	class cRenderTexture;

	class cContext
	{
	private:

		//Vars
		std::weak_ptr<cContext> m_Self;

		ALCcontext *m_SoundContext;
		ALCdevice *m_Device;

	public:

		static std::shared_ptr<cContext> Init(); //Initialise

	};
}

#endif