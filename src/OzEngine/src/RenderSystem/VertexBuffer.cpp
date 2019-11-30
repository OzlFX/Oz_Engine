#include "VertexBuffer.h"
#include "OzEngine/src/Context.h"

namespace Oz
{
	cVertexBuffer::cVertexBuffer() : m_Components(0), m_Dirty(false)
	{
		glGenBuffers(1, &m_ID);

		if (!m_ID)
		{
			throw std::exception();
		}
	}

	void cVertexBuffer::Add(glm::vec2 _value)
	{
		if (!m_Components)
		{
			m_Components = 2;
		}

		if (m_Components != 2)
		{
			throw std::exception();
		}

		m_Data.push_back(_value.x);
		m_Data.push_back(_value.y);

		m_Dirty = true;
	}

	void cVertexBuffer::Add(glm::vec3 _value)
	{
		if (!m_Components)
		{
			m_Components = 3;
		}

		if (m_Components != 3)
		{
			throw std::exception();
		}

		m_Data.push_back(_value.x);
		m_Data.push_back(_value.y);
		m_Data.push_back(_value.z);

		m_Dirty = true;
	}

	void cVertexBuffer::Add(glm::vec4 _value)
	{
		if (!m_Components)
		{
			m_Components = 4;
		}

		if (m_Components != 4)
		{
			throw std::exception();
		}

		m_Data.push_back(_value.x);
		m_Data.push_back(_value.y);
		m_Data.push_back(_value.z);
		m_Data.push_back(_value.w);

		m_Dirty = true;
	}

	int cVertexBuffer::getDataSize()
	{
		return m_Data.size();
	}

	int cVertexBuffer::getComponents()
	{
		if (!m_Components) throw std::exception();

		return m_Components;
	}

	GLuint cVertexBuffer::getID()
	{
		if (m_Dirty)
		{
			//Bind buffers
			glBindBuffer(GL_ARRAY_BUFFER, m_ID);
			glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * m_Data.size(), &m_Data.at(0), GL_STATIC_DRAW);
			glBindBuffer(GL_ARRAY_BUFFER, 0);

			m_Dirty = false;
		}

		return m_ID;
	}

	cVertexBuffer::~cVertexBuffer()
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		GLuint delID = m_ID;
		glDeleteBuffers(1, &delID);
	}
}