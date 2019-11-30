#ifndef _CSHADERPROGRAM_H_
#define _CSHADERPROGRAM_H_

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <string>

#include <OzEngine/src/NonCopyable.h>
#include <OzEngine/src/Resource.h>

namespace Oz
{
	class cContext;
	class cVertexArray;
	class cMesh;

	class cShaderProgram : private cNonCopyable, public cResource
	{
		//friend class cResources;
		friend class cContext;

	private:

		GLuint m_ID;
		std::weak_ptr<cMesh> m_Mesh;

		std::shared_ptr<cContext> m_Context;

	public:
		cShaderProgram(std::string _path);

		void Draw(std::weak_ptr<cVertexArray> _vertArray); //Draw vertex array
		void Draw(std::shared_ptr<cMesh> _mesh); //Draw Mesh

		//Set Uniform overloads
		void setUniform(const std::string _uniform, glm::vec4 _value);
		void setUniform(const std::string _uniform, float _value);
		void setUniform(const std::string _uniform, glm::mat4 _value);

		GLuint getID(); //Get the shader ID

		~cShaderProgram();
	};
}

#endif