#include <memory>
#include <vector>
#include <string>

namespace Oz
{
	class cMaterial
	{
		class cShaderProgram;
		class cMaterialAttribute;

	private:

		std::weak_ptr<cShaderProgram> m_Shader;
		std::vector<cMaterialAttribute> m_Attrib;

	public:

		void setShader(std::weak_ptr<cShaderProgram> _shader); //Set the shader

		void setValue(std::string _name, std::weak_ptr<cTexture> _value); //Set the value with a texture
		void setValue(std::string _name, float _value); //Set the value with a float

		std::shared_ptr<cShaderProgram> getShader(); //Get the shader
	};
}