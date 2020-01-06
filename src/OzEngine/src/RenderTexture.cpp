#include "RenderTexture.h"
#include "Context.h"

namespace Oz
{
	std::shared_ptr<cRenderTexture> cRenderTexture::Create()
	{
		std::shared_ptr<cRenderTexture> rend = std::make_shared<cRenderTexture>();
		rend->m_Self = rend;

		GLuint ID = 0;
		glGenTextures(1, &ID);

		GLuint fboID = 0;
		glGenFramebuffers(1, &fboID);

		GLuint rboID = 0;
		glGenRenderbuffers(1, &rboID);

		rend->m_ID = ID;
		rend->m_Fbo = fboID;
		rend->m_Rbo = rboID;

		rend->m_BorderSize = 0;

		return rend;
	}

	void cRenderTexture::setSize(unsigned int _width, unsigned int _height)
	{
		glGenFramebuffers(1, &m_Fbo);
		if (!m_Fbo) throw std::exception();
		glBindFramebuffer(GL_FRAMEBUFFER, m_Fbo);

		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_ID, 0);

		glGenRenderbuffers(1, &m_Rbo);
		glBindRenderbuffer(GL_RENDERBUFFER, m_Rbo);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, _width, _height);
		glBindRenderbuffer(GL_RENDERBUFFER, 0);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_Rbo);

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	GLuint cRenderTexture::getFbID()
	{
		return m_Fbo;
	}

	void cRenderTexture::Clear()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, m_Fbo);
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}
}