#ifndef _CVERTEXARRAY_H_
#define _CVERTEXARRAY_H_

//#include "OzEngine/src/Face.h"

#include <GL/glew.h>
#include <glm/glm.hpp>

#include <vector>
#include <string>
#include <memory>

namespace Oz
{
	struct sFace
	{
		//Vars
		glm::vec3 posA, posB, posC;
		glm::vec2 texCoordA, texCoordB, texCoordC;
		glm::vec3 normA, normB, normC;
		glm::vec2 lightA, lightB, lightC;
	};

	class cVertexBuffer;
	
	class cVertexArray
	{
	private:

		GLuint m_ID;
		bool m_Dirty;

		std::vector<std::shared_ptr<cVertexBuffer>> m_Buffers;
		std::vector<sFace> m_Faces;

	public:

		void setBuffer(std::string _attrib, std::weak_ptr<cVertexBuffer> _buffer);
		int getVertexCount();

		void Load(const std::string& _path);

		GLuint getID();

		~cVertexArray();
	};
}

#endif