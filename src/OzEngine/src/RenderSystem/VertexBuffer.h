#include <GL/glew.h>
#include <glm/glm.hpp>

#include <vector>

namespace Oz
{
	class VertexBuffer
	{
	private:

		GLuint m_ID;
		int m_Components;
		std::vector<GLfloat> m_Data;
		bool m_Dirty;

	public:

		VertexBuffer();

		void Add(glm::vec3 _value);
		void Add(glm::vec4 _value);

		int getComponents();
		int getDataSize();

		GLuint getID();

		~VertexBuffer();
	};
}