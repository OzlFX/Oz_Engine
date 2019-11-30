#include <GL/glew.h>
#include <glm/glm.hpp>

#include <vector>
#include <memory>

namespace Oz
{
	class cContext;

	class cVertexBuffer
	{
		friend class cContext;

	private:

		GLuint m_ID;
		int m_Components;
		std::vector<GLfloat> m_Data;
		bool m_Dirty;

		std::shared_ptr<cContext> m_Context;

	public:

		cVertexBuffer();

		void Add(glm::vec2 _value);
		void Add(glm::vec3 _value);
		void Add(glm::vec4 _value);

		int getComponents();
		int getDataSize();

		GLuint getID();

		~cVertexBuffer();
	};
}