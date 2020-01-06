#include "RenderSystem/VertexBuffer.h"
#include "RenderSystem/VertexArray.h"
#include "Context.h"
#include "Mesh.h"

namespace Oz
{
	std::shared_ptr<cMesh> cMesh::Create()
	{
		std::shared_ptr<cMesh> mesh = std::make_shared<cMesh>();
		mesh->m_Self = mesh;

		return mesh;
	}

	std::shared_ptr<cMesh> cMesh::Load(std::string _path)
	{
		m_Model = std::make_shared<cVertexArray>();

		m_Model->Load(_path); //Create a new vertex based on the path given
		m_Dirty = true;

		return m_Self.lock(); //Return the model
	}

	cMesh::~cMesh()
	{

	}
}