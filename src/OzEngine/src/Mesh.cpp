#include "Mesh.h"

namespace Oz
{
	std::shared_ptr<cMesh> cMesh::Create()
	{
		return std::shared_ptr<cMesh>();
	}

	std::shared_ptr<cMesh> cMesh::Load(std::string _path)
	{
		return std::shared_ptr<cMesh>();
	}

	void cMesh::addFace(cFace & _face)
	{

	}

	GLuint cMesh::getID()
	{
		return GLuint();
	}

	cMesh::~cMesh()
	{

	}
}