#include "Context.h"
#include "RenderSystem/ShaderProgram.h"
#include "RenderSystem/VertexBuffer.h"

namespace Oz
{
	void cContext::Init()
	{

	}

	//Create the shader with the source files
	void cContext::createShader(std::string _vert, std::string _frag)
	{
		m_Shader = std::make_shared<cShaderProgram>(_vert, _frag);
	}

	//Create the vertex buffer
	void cContext::createBuffer()
	{
		m_VertexBuffer = std::make_shared<cVertexBuffer>();
	}
}