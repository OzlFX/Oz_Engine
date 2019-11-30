//#include "OzEngine/src/Face.h"

#include <GL/glew.h>
#include <glm/glm.hpp>

#include <vector>
#include <string>
#include <memory>

namespace Oz
{
	class cVertexBuffer;
	struct sFace;

	class cVertexArray
	{
	private:

		GLuint m_ID;
		bool m_Dirty;

		std::vector<std::shared_ptr<cVertexBuffer>> m_Buffers;
		std::vector<sFace> m_Faces;

	public:

		cVertexArray();

		void setBuffer(std::string _attrib, std::weak_ptr<cVertexBuffer> _buffer);
		int getVertexCount();

		void Load(const std::string& _path);

		std::vector<sFace> createFaces();

		//void Parse(const std::string& _data);
		//void safeParse(const std::string& _data, std::string& _currLine);

		GLuint getID();

		~cVertexArray();
	};
}