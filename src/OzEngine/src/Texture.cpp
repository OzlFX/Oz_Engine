#include "Texture.h"
#include "Context.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

namespace Oz
{
	std::shared_ptr<cTexture> cTexture::Create()
	{
		std::shared_ptr<cTexture> texture = std::make_shared<cTexture>();

		texture->m_BorderSize = 0;

		texture->m_Self = texture;

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

		int w = 0;
		int h = 0;

		unsigned char *data = stbi_load(_path.c_str(), &w, &h, &m_Channels, 4); //Create the image data for usage by the GPU

		if (!data) throw std::exception();

		m_Width = w;
		m_Height = h;

		glGenTextures(1, &m_ID); //Generate the texture

		if (!m_ID) throw std::exception();

		glBindTexture(GL_TEXTURE_2D, m_ID); //Bind the texture
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_Width, m_Height, m_BorderSize, GL_RGBA, GL_UNSIGNED_BYTE, data); //Generate the texture based on values

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

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

	glm::vec2 cTexture::getSize()
	{
		return m_Size = glm::vec2(m_Width, m_Height);
	}

	GLuint cTexture::getID()
	{
		return m_ID;
	}

	cTexture::~cTexture()
	{

	}
}