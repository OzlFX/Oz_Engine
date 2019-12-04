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
		
		m_Self.lock()->m_Model = std::make_shared<cVertexArray>();

		m_Self.lock()->m_Model->Load(_path); //Create a new vertex based on the path given

		//for (int i = 0; i < m_Faces.size(); i++)
		//{
		//	m_Model->setBuffer(_path, m_Faces.at(i).getVertex()); //Set the mesh's buffer according to the face's values
		//}

		return m_Self.lock(); //Return the model
	}

	void cMesh::addFace()
	{
		m_Faces = m_Model->createFaces(); //Add face to the mesh

		std::shared_ptr<cVertexBuffer> posBuffer = m_Context->createBuffer();

		for (std::vector<sFace>::iterator it = m_Faces.begin();
			it != m_Faces.end(); it++)
		{
			posBuffer->Add(it->posA);
			posBuffer->Add(it->posB);
			posBuffer->Add(it->posC);
		}

		m_Model->setBuffer("in_Position", posBuffer);

		std::shared_ptr<cVertexBuffer> texCoordBuffer = m_Context->createBuffer();
		
		for (std::vector<sFace>::iterator it = m_Faces.begin();
			it != m_Faces.end(); it++)
		{
			texCoordBuffer->Add(it->texCoordA);
			texCoordBuffer->Add(it->texCoordB);
			texCoordBuffer->Add(it->texCoordC);
		}

		m_Model->setBuffer("in_TexCoord", texCoordBuffer);

		std::shared_ptr<cVertexBuffer> normBuffer = m_Context->createBuffer();

		for (std::vector<sFace>::iterator it = m_Faces.begin();
			it != m_Faces.end(); it++)
		{
			normBuffer->Add(it->normA);
			normBuffer->Add(it->normB);
			normBuffer->Add(it->normC);
		}

		m_Model->setBuffer("in_Normal", normBuffer);

		m_Dirty = true;
	}

	GLuint cMesh::getID()
	{
		GLuint ID = 0;

		if (m_Dirty)
		{
			ID = m_Model->getID();

			m_Dirty = false;
		}

		return ID;
	}

	cMesh::~cMesh()
	{

	}
}