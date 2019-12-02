#ifndef _CMESH_H_
#define _CMESH_H_

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
		std::shared_ptr<cMesh> Load(std::string& _path); //Load the mesh

	public:

		void addFace(); //Add a new face to the mesh
		GLuint getID(); //Get the ID of the mesh based on the model's ID

		~cMesh();
	};
}

#endif