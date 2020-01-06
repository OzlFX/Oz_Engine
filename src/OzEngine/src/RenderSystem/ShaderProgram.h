#ifndef _CSHADERPROGRAM_H_
#define _CSHADERPROGRAM_H_

/* This class should never be modified by the user */

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <string>
#include <vector>

#include <OzEngine/src/NonCopyable.h>
#include <OzEngine/src/Resource.h>

namespace Oz
{
	class cVertexArray;
	class cMesh;
	class cRenderTexture;

	struct sTextureSampler
	{
		GLint m_ID;
		std::shared_ptr<cTexture> m_Texture;
	};

	class cShaderProgram : private cNonCopyable
	{
		friend class cCore;

	private:

		//Vars
		GLuint m_ID;
		std::vector<sTextureSampler> m_TexSampler;
		glm::vec4 m_Viewport;

		std::weak_ptr<cMesh> m_Mesh; //Reference to mesh to draw it

		std::weak_ptr<cShaderProgram> m_Self;

		std::string m_Path; //The path of the file to use in the program

		std::shared_ptr<cShaderProgram> Create(); //Create a new shader program
		void Load(std::string _path); //Load the shader file
		void Load(std::string _vert, std::string _frag); //Load frag and vert files

	public:

		void Draw(std::weak_ptr<cVertexArray> _vertArray); //Draw vertex array
		void Draw(std::shared_ptr<cMesh> _mesh); //Draw Mesh
		//void Draw(std::shared_ptr<cRenderTexture> _rendTexture); //Draw the render texture
		void Draw(std::shared_ptr<cRenderTexture> _rendTexture, std::shared_ptr<cMesh> _mesh); //Draw Mesh and render texture

		//Set Uniform overloads
		void setUniform(const std::string _uniform, glm::vec4 _value);
		void setUniform(const std::string _uniform, float _value);
		void setUniform(const std::string _uniform, glm::mat4 _value);
		void setUniform(const std::string _uniform, std::weak_ptr<cTexture> _texture);

		void setViewport(glm::vec4 _viewport);

		GLuint getID(); //Get the shader ID

		~cShaderProgram();
	};
}

#endif