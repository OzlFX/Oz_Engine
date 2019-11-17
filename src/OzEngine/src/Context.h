#include <memory>
#include <string>

namespace Oz
{
	class cContext
	{
		class cShaderProgram;
		class cVertexBuffer;

	private:

		std::shared_ptr<cShaderProgram> m_Shader;
		std::shared_ptr<cVertexBuffer> m_VertexBuffer;

	public:

		void Init(); //Initialise
		void createShader(std::string _vert, std::string _frag); //Create a shader
		void createBuffer(); //Create buffer

	};
}