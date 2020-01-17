#include "OzEngine/src/MeshRend.h"
#include "Components/ComponentIncludes.h"
#include "OzEngine/src/Camera.h"
#include "Light.h"
#include "Mesh.h"
#include "Texture.h"
#include "RenderTexture.h"
#include "Material.h"
#include "RenderSystem/ShaderProgram.h"

namespace Oz
{
	void cMeshRenderer::onBegin()
	{
		if (m_Material == NULL)
		{
			m_Shader = getCore()->getShader(); //Get the model loader shader
		}
		else
		{
			m_Shader = getCore()->loadShader(m_Material->getShader().at(0), m_Material->getShader().at(1));
			m_Texture = m_Material->getTexture();
		}
	}

	void cMeshRenderer::onDisplay()
	{
		if (getCore()->getMainCamera() != NULL)
		{
			//Check if the material is set
			if (m_Material != NULL)
			{
				m_Lights = getCore()->getLights(); //Get the lights to render from

				for (std::list<std::shared_ptr<cGameObject>>::iterator it = m_Lights.begin(); it != m_Lights.end(); it++)
				{
					m_Shader->setUniform("in_LightPos", (*it)->getTransform()->getPos());
					m_Shader->setUniform("in_LightColor", glm::vec3(1.0f));
				}

				m_Shader->setUniform("in_View", getCore()->getMainCamera()->getView());
				m_Shader->setUniform("in_Model", getGameObject()->getTransform()->getModel());
				m_Shader->setUniform("in_albedo", m_Texture);
				m_Shader->setUniform("in_normalMap", m_Material->getNormal());
				m_Shader->setUniform("in_roughness", m_Material->getRoughness());
				m_Shader->setUniform("in_metallic", m_Material->getMetallic());
				m_Shader->setUniform("in_ao", m_Material->getDisperse());

				m_Shader->Draw(m_Mesh);
			}
			else
			{

				//m_Shader->setUniform("in_Projection", getCore()->getMainCamera()->getProjection());
				m_Shader->setUniform("in_View", getCore()->getMainCamera()->getView());
				m_Shader->setUniform("in_Model", getGameObject()->getTransform()->getModel());
				m_Shader->setUniform("in_Texture", m_Texture);

				m_Shader->Draw(m_Mesh);
			}
		}
		else
		{
			throw Oz::Exception("No Camera given, cannot render!");
		}
	}

	void cMeshRenderer::setMesh(std::weak_ptr<cMesh> _mesh)
	{
		m_Mesh = _mesh.lock();
	}

	void cMeshRenderer::setTexture(std::weak_ptr<cTexture> _texture)
	{
		m_Texture = _texture.lock();
	}

	void cMeshRenderer::setMaterial(std::weak_ptr<cMaterial> _material)
	{
		m_Material = _material.lock();
	}

	//Get the mesh
	std::shared_ptr<cMesh> cMeshRenderer::getMesh()
	{
		return m_Mesh;
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