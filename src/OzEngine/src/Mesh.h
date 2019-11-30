#include <vector>
#include <OzEngine/src/NonCopyable.h>

#include "RenderSystem/ShaderProgram.h"

#include "Resource.h"

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

	class cContext;
	class cVertexArray;

	class cMesh : private cNonCopyable, public cResource
	{
		friend class cContext;
		friend class cResources;
		friend class cShaderProgram;

	private:

		//Vars
		std::vector<sFace> m_Faces;
		bool m_Dirty;
		
		std::shared_ptr<cContext> m_Context;
		std::shared_ptr<cVertexArray> m_Model;
		std::weak_ptr<cMesh> m_Self;

		//Functions
		std::shared_ptr<cVertexArray> Create();
		std::shared_ptr<cMesh> Load(const std::string& _path);

	public:

		void addFace();
		GLuint getID();

		~cMesh();
	};
}