#include "MeshRend.h"
#include "Mesh.h"
#include "Texture.h"
#include "Material.h"
#include "RenderSystem/ShaderProgram.h"

namespace Oz
{
	void cMeshRenderer::onInit()
	{
		m_Material->getShader();
	}

	void cMeshRenderer::onDisplay()
	{
		m_Material->getShader()->setUniform("in_Model", glm::mat4(1.0f));
		m_Material->getShader()->setUniform("in_Projection", glm::mat4(1.0f));
		m_Material->getShader()->Draw(m_Mesh.lock());
	}

	void cMeshRenderer::setMesh(std::weak_ptr<cMesh> _mesh)
	{
		m_Mesh = _mesh;
	}

	void cMeshRenderer::setMaterial(std::weak_ptr<cMaterial> _material)
	{
		m_Material = _material.lock();
	}

	//Get the mesh
	std::shared_ptr<cMesh> cMeshRenderer::getMesh()
	{
		return m_Mesh.lock();
	}

	//Get texture
	std::shared_ptr<cTexture> cMeshRenderer::getTexture()
	{
		return m_Texture;
	}

	//Get material
	std::shared_ptr<cMaterial> cMeshRenderer::getMaterial()
	{
		return m_Material;
	}

	cMeshRenderer::~cMeshRenderer()
	{

	}
}