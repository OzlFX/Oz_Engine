#ifndef _CCONTEXT_H_
#define _CCONTEXT_H_

#include <memory>
#include <string>

namespace Oz
{
	class cShaderProgram;
	class cVertexBuffer;
	class cMesh;
	class cTexture;
	//class cRenderTexture;

	class cContext
	{
	private:

		//Vars
		std::weak_ptr<cContext> m_Self;

	public:

		static std::shared_ptr<cContext> Init(); //Initialise
		std::shared_ptr<cShaderProgram> createShader(std::string _path); //Create a shader
		std::shared_ptr<cVertexBuffer> createBuffer(); //Create buffer
		std::shared_ptr<cMesh> createMesh(); //Create Mesh

	};
}

#endif