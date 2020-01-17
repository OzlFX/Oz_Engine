#ifndef _CRENDERTEXTURE_H_
#define _CRENDERTEXTURE_H_

#include "Texture.h"

namespace Oz
{
	/* Used to draw post processing to the screen */
	class cRenderTexture : public cTexture
	{
		friend class cResources;

	private:
		GLuint m_Fbo;
		GLuint m_Rbo;

	public:

		std::shared_ptr<cRenderTexture> Create(); //Create a render texture

		void setSize(unsigned int _width, unsigned int _height);

		GLuint getFbID();
		void Clear();

	};
}

#endif