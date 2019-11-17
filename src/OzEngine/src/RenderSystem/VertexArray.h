#include <GL/glew.h>
#include <glm/glm.hpp>

#include <vector>
#include <string>
#include <memory>

namespace Oz
{
	class VertexBuffer;

	class VertexArray
	{
	private:

		GLuint m_ID;
		bool m_Dirty;

		std::vector<std::shared_ptr<VertexBuffer>> buffers;

	public:

		VertexArray();

		void setBuffer(std::string _attrib, std::weak_ptr<VertexBuffer> _buffer);
		int getVertexCount();

		GLuint getID();

		~VertexArray();
	};
}