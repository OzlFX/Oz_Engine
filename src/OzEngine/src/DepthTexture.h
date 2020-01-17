#ifndef _CDEPTHTEXTURE_H_
#define _CDEPTHTEXTURE_H_

#include "Texture.h"

namespace Oz
{
	/* Alloes for casting shadows onto objects */
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