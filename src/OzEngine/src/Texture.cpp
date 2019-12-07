#include "Texture.h"
#include "Context.h"
#include "stb_image.h"

namespace Oz
{
	std::shared_ptr<cTexture> cTexture::Create()
	{
		std::shared_ptr<cTexture> texture = m_Context->createTexture();
		texture->m_Self = texture;

		texture->m_Width = 32;
		texture->m_Height = 32;

		texture->m_BorderSize = 0;

		glGenTextures(1, &m_ID); //Generate the texture
		glBindTexture(GL_TEXTURE_2D, m_ID);  //Bind the texture
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_Width, m_Height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL); //Generate the texture based on values
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glBindTexture(GL_TEXTURE_2D, 0); //Unbind the texture

		return texture;
	}

	void cTexture::setBorder(unsigned int _borderSize)
	{
		m_BorderSize = _borderSize;
	}

	void cTexture::setSize(unsigned int _width, unsigned int _height)
	{
		m_Width = _width;
		m_Height = _height;
	}

	std::shared_ptr<cTexture> cTexture::Load(std::string _path)
	{
		m_Channels = 0;

		unsigned char *data = stbi_load(_path.c_str(), 0, 0, &m_Channels, 4); //Create the image data for usage by the GPU

		if (!data) throw std::exception();

		glGenTextures(1, &m_ID); //Generate the texture

		if (!m_ID) throw std::exception();

		glBindTexture(GL_TEXTURE_2D, m_ID); //Bind the texture
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_Width, m_Height, m_BorderSize, GL_RGBA, GL_UNSIGNED_BYTE, data); //Generate the texture based on values
		free(data);
		glGenerateMipmap(GL_TEXTURE_2D); //Generate the mipmap

		glBindTexture(GL_TEXTURE_2D, 0); //Unbind the texture

		return m_Self.lock();
	}

	/*
	void cTexture::setPixel(unsigned int _x, unsigned int _y, glm::vec3 _colour)
	{

	}

	void cTexture::setPixel(unsigned int _x, unsigned int _y, glm::vec4 _colour)
	{

	}*/

	GLuint cTexture::getID()
	{
		return m_ID;
	}

	cTexture::~cTexture()
	{

	}
}