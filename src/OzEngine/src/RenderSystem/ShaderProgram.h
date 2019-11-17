#ifndef _CSHADERPROGRAM_H_
#define _CSHADERPROGRAM_H_

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <string>

#include <OzEngine/src/NonCopyable.h>
#include <OzEngine/src/Resource.h>

namespace Oz
{
	class VertexArray;

	class cShaderProgram : private cNonCopyable, public cResource
	{
	private:

		GLuint m_ID;

	public:
		cShaderProgram(std::string _vert, std::string _frag);

		void Draw(std::weak_ptr<VertexArray> _vertArray); //Draw

		//Set Uniform overloads
		void setUniform(std::string _uniform, glm::vec4 _value);
		void setUniform(std::string _uniform, float _value);
		void setUniform(std::string _uniform, glm::mat4 _value);

		GLuint getID(); //Get the shader ID

		~cShaderProgram();
	};
}

#endif