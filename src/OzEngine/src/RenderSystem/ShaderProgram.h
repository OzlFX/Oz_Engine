#ifndef _CSHADERPROGRAM_H_
#define _CSHADERPROGRAM_H_

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <string>
#include <vector>

#include <OzEngine/src/NonCopyable.h>
#include <OzEngine/src/Resource.h>

namespace Oz
{
	class cContext;
	class cVertexArray;
	class cMesh;

	struct sTextureSampler
	{
		GLint m_ID;
		std::shared_ptr<cTexture> m_Texture;
	};

	class cShaderProgram : private cNonCopyable, public cResource
	{
		//friend class cResources;
		friend class cContext;

	private:

		//Vars
		GLuint m_ID;
		std::vector<sTextureSampler> m_TexSampler;
		glm::vec4 m_Viewport;

		std::weak_ptr<cMesh> m_Mesh; //Reference to mesh to draw it

		std::weak_ptr<cShaderProgram> m_Self;

		std::shared_ptr<cContext> m_Context; //Allow context access to create a shader

		std::string m_Path; //The path of the file to use in the program

	public:
		cShaderProgram();

		std::shared_ptr<cShaderProgram> Create(); //Create a new shader program
		void Load(std::string _path); //Load the shader file

		void Draw(std::weak_ptr<cVertexArray> _vertArray); //Draw vertex array
		void Draw(std::shared_ptr<cMesh> _mesh); //Draw Mesh

		//Set Uniform overloads
		void setUniform(const std::string _uniform, glm::vec4 _value);
		void setUniform(const std::string _uniform, float _value);
		void setUniform(const std::string _uniform, glm::mat4 _value);
		void setUniform(const std::string _uniform, std::weak_ptr<cTexture> _texture);

		GLuint getID(); //Get the shader ID

		~cShaderProgram();
	};
}

#endif