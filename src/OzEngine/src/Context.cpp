#include "Context.h"
#include "Texture.h"
//#include "RenderTexture.h"
#include "Mesh.h"
#include "Material.h"
#include "RenderSystem/ShaderProgram.h"
#include "RenderSystem/VertexBuffer.h"

#include <iostream>
#include <GL/glew.h>

namespace Oz
{
	std::shared_ptr<cContext> cContext::Init()
	{
		std::shared_ptr<cContext> context = std::make_shared<cContext>();

		//Initialise glew
		if (glewInit() != GLEW_OK)
		{
			//if glew fails to initialises, an error is returned to the console and throws an exception
#if _DEBUG
			std::cout << "ERROR: unable to initialize glew!" << std::endl;
#endif
			throw std::exception();
		}

		context->m_Self = context;

		return context;
	}

	//Create the shader with the source files
	std::shared_ptr<cShaderProgram> cContext::createShader()
	{
		std::shared_ptr<cShaderProgram> shader = std::make_shared<cShaderProgram>();
		shader->m_Context = m_Self.lock();

		return shader;
	}

	//Create the vertex buffer
	std::shared_ptr<cVertexBuffer> cContext::createBuffer()
	{
		std::shared_ptr<cVertexBuffer> buffer = std::make_shared<cVertexBuffer>();
		buffer->m_Context = m_Self.lock();

		return buffer;
	}

	//Create the mesh
	std::shared_ptr<cMesh> cContext::createMesh()
	{
		std::shared_ptr<cMesh> mesh = std::make_shared<cMesh>();
		mesh->m_Context = m_Self.lock();

		return mesh;
	}

	//Create the material
	std::shared_ptr<cMaterial> cContext::createMaterial()
	{
		std::shared_ptr<cMaterial> material = std::make_shared<cMaterial>();
		material->m_Context = m_Self.lock();

		return material;
	}

	//Create the texture
	std::shared_ptr<cTexture> cContext::createTexture()
	{
		std::shared_ptr<cTexture> texture = std::make_shared<cTexture>();
		texture->m_Context = m_Self.lock();

		return texture;
	}
}