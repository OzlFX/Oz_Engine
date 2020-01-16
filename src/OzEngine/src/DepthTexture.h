#ifndef _CDEPTHTEXTURE_H_
#define _CDEPTHTEXTURE_H_

#include "Texture.h"

namespace Oz
{
	class cDepthTexture : public cTexture
	{
		friend class cResources;

	private:

		GLuint m_RtFbo;

	public:

		cDepthTexture();

	};
}

#endif