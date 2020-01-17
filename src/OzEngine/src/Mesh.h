#ifndef _CMESH_H_
#define _CMESH_H_

#include <vector>
#include <OzEngine/src/NonCopyable.h>

#include "RenderSystem/ShaderProgram.h"

#include "Resource.h"

namespace Oz
{
	class cVertexArray;

	/* Front end mesh to the model loader and data handler, easier to manage */
	class cMesh : private cNonCopyable, public cResource
	{
		friend class cResources;
		friend class cShaderProgram;

	private:

		//Vars
		bool m_Dirty;
		
		std::shared_ptr<cVertexArray> m_Model;
		std::weak_ptr<cMesh> m_Self;

		//Functions
		std::shared_ptr<cMesh> Create();
		std::shared_ptr<cMesh> Load(std::string _path); //Load the mesh

	public:

		~cMesh();
	};
}

#endif