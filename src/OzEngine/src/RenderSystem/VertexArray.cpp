#include "VertexArray.h"
#include "VertexBuffer.h"

namespace Oz
{
	VertexArray::VertexArray() : m_Dirty(false)
	{
		glGenVertexArrays(1, &m_ID);

		if (!m_ID)
		{
			throw std::exception();
		}

		buffers.resize(10);
	}

	void VertexArray::setBuffer(std::string _attrib, std::weak_ptr<VertexBuffer> _buffer)
	{
		if (_attrib == "in_Position")
		{
			buffers.at(0) = _buffer.lock();
		}
		else if (_attrib == "in_Color")
		{
			buffers.at(1) = _buffer.lock();
		}
		else
		{
			throw std::exception();
		}

		m_Dirty = true;
	}

	int VertexArray::getVertexCount()
	{
		if (!buffers.at(0))
		{
			throw std::exception();
		}

		return buffers.at(0)->getDataSize() / buffers.at(0)->getComponents();
	}

	GLuint VertexArray::getID()
	{
		if (m_Dirty)
		{
			glBindVertexArray(m_ID);

			//Add buffers and enable them
			for (size_t i = 0; i < buffers.size(); i++)
			{
				if (buffers.at(i))
				{
					glBindBuffer(GL_ARRAY_BUFFER, buffers.at(i)->getID());

					glVertexAttribPointer(i, buffers.at(i)->getComponents(), GL_FLOAT, GL_FALSE,
						buffers.at(i)->getComponents() * sizeof(GLfloat), (void *)0);

					glEnableVertexAttribArray(i);
				}
				else
				{
					glDisableVertexAttribArray(i);
				}
			}

			glBindBuffer(GL_ARRAY_BUFFER, 0);
			glBindVertexArray(0);

			m_Dirty = false;
		}

		return m_ID;
	}

	VertexArray::~VertexArray()
	{

	}
}