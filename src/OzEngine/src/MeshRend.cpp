#include "Components/ComponentIncludes.h"
#include "Mesh.h"
#include "Texture.h"
#include "RenderTexture.h"
#include "Material.h"
#include "Core.h"
#include "RenderSystem/ShaderProgram.h"

namespace Oz
{
	void cMeshRenderer::onInit()
	{
		m_Shader = getCore()->getShader(); //Get the model loader shader
		m_NullShader = getCore()->loadShader("../src/Resources/Shaders/nullpass.vert", "../src/Resources/Shaders/nullpass.frag");

		if (m_Material == NULL) m_Default = std::make_shared<cRenderTexture>();
	}

	void cMeshRenderer::onBegin()
	{
		m_Default->setSize(m_Texture->getSize().x, m_Texture->getSize().y);
	}

	void cMeshRenderer::onDisplay()
	{
		if (getCore()->getMainCamera() != NULL)
		{
			//Check if the material is set
			if (m_Material != NULL)
			{
				m_Material->getRendTexture()->Clear();

				m_Shader->setUniform("in_Projection", getCore()->getMainCamera()->getProjection());
				m_Shader->setUniform("in_View", getCore()->getMainCamera()->getView());
				m_Shader->setUniform("in_Model", getGameObject()->getTransform()->getModel());
				m_Shader->setUniform("in_Texture", m_Material->getTexture());

				m_Shader->Draw(m_Material->getRendTexture(), m_Mesh.lock());

				m_NullShader->setViewport(glm::vec4(0, 0, getCore()->getWinSize().x, getCore()->getWinSize().y));
				m_NullShader->setUniform("in_Texture", m_Material->getRendTexture());
				m_NullShader->Draw(m_Mesh.lock());
			}
			else
			{
				m_Shader->setUniform("in_Projection", getCore()->getMainCamera()->getProjection());
				m_Shader->setUniform("in_View", getCore()->getMainCamera()->getView());
				m_Shader->setUniform("in_Model", getGameObject()->getTransform()->getModel());
				m_Shader->setUniform("in_Texture", m_Texture);
				m_Shader->Draw(m_Default, m_Mesh.lock());

				m_NullShader->setViewport(glm::vec4(0, 0, getCore()->getWinSize().x, getCore()->getWinSize().y));
				m_NullShader->setUniform("in_Texture", m_Default);
				m_NullShader->Draw(m_Mesh.lock());
			}
		}
		else
		{
			throw Oz::Exception("No Camera given, cannot render!");
		}
	}

	void cMeshRenderer::setMesh(std::weak_ptr<cMesh> _mesh)
	{
		m_Mesh = _mesh;
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