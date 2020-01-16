#include "RenderTexture.h"
#include "Exception.h"
#include "DepthTexture.h"

namespace Oz
{
	cDepthTexture::cDepthTexture()
	{
		glGenTextures(1, &m_ID);
		glGenFramebuffers(1, &m_RtFbo);

		glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);

		const unsigned int SHADOW_WIDTH = 2048, SHADOW_HEIGHT = 2048;
		glBindTexture(GL_TEXTURE_CUBE_MAP, m_ID);
		for (unsigned int i = 0; i < 6; i++) {
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_DEPTH_COMPONENT16, SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
		}
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

		glBindFramebuffer(GL_FRAMEBUFFER, m_RtFbo);
		glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, m_ID, 0);
		glDrawBuffer(GL_NONE);
		glReadBuffer(GL_NONE);

		GLenum res = glCheckFramebufferStatus(GL_FRAMEBUFFER);
		if (res != GL_FRAMEBUFFER_COMPLETE)
			throw Oz::Exception("Framebuffer not complete! Value = " + res);

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}
}