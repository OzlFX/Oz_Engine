#include "ShaderProgram.h"
#include "VertexArray.h"
#include "OzEngine/src/Context.h"
#include "OzEngine/src/Mesh.h"
#include "OzEngine/src/Exception.h"
#include "OzEngine/src/Texture.h"
#include "OzEngine/src/RenderTexture.h"

#include <glm/ext.hpp>

#include <fstream>
#include <iostream>

namespace Oz
{
	//Create the shader
	std::shared_ptr<cShaderProgram> cShaderProgram::Create()
	{
		std::shared_ptr<cShaderProgram> shader = std::make_shared<cShaderProgram>();
		shader->m_Self = shader;

		return shader;
	}

	//Load the shader
	void cShaderProgram::Load(std::string _path)
	{
		std::ifstream file(_path.c_str());

		//Check to see if the file is open
		if (!file.is_open())
		{
			throw Oz::Exception("Cannot find file");
		}

		//Copy contents of the file into the string
		while (!file.eof())
		{
			std::string line;
			std::getline(file, line);
			m_Path += line + "\n";
		}

		const GLchar *src = NULL;

		std::string vert = "";
		vert += "#version 120\n";
		vert += "#define VERTEX\n";
		vert += m_Path;

		src = vert.c_str(); //Convert vertex string into GLchar for the GPU to use

		GLuint vertexShaderId = glCreateShader(GL_VERTEX_SHADER); //Create the vertex shader
		glShaderSource(vertexShaderId, 1, &src, NULL); //Set the shader source and get the vertex shader file contents
		glCompileShader(vertexShaderId); //Compile the shader
		GLint success = 0;
		glGetShaderiv(vertexShaderId, GL_COMPILE_STATUS, &success);

		//Check if compile was successful
		if (!success)
		{
			int length = 0;
			glGetShaderiv(vertexShaderId, GL_INFO_LOG_LENGTH, &length);

			std::vector<char> infoLog(length);
			glGetShaderInfoLog(vertexShaderId, length, NULL, &infoLog.at(0));

			glDeleteShader(vertexShaderId);

			std::string msg = &infoLog.at(0);
			throw Oz::Exception(msg);
		}

		std::string frag = "";
		frag += "#version 120\n";
		frag += "#define FRAGMENT\n";
		frag += m_Path;

		src = frag.c_str(); //Convert fragment string into GLchar for the GPU to use

		GLuint fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER); //Create the fragment shader
		glShaderSource(fragmentShaderId, 1, &src, NULL); //Set the shader source and get the fragment shader file contents
		glCompileShader(fragmentShaderId); //Compile the shader
		glGetShaderiv(fragmentShaderId, GL_COMPILE_STATUS, &success);

		//Check if compile was successful
		if (!success)
		{
			int length = 0;
			glGetShaderiv(fragmentShaderId, GL_INFO_LOG_LENGTH, &length);

			std::vector<GLchar> infoLog(length);
			glGetShaderInfoLog(fragmentShaderId, length, &length, &infoLog.at(0));

			glDeleteShader(fragmentShaderId);

			std::string msg = &infoLog.at(0);
			throw Oz::Exception(msg);
		}

		m_ID = glCreateProgram(); //Create the shader program
		glAttachShader(m_ID, vertexShaderId); //Attach the vertex shader to the shader program
		glAttachShader(m_ID, fragmentShaderId); //Attach the fragment shader to the shader program

		//Bind the shaders
		glBindAttribLocation(m_ID, 0, "in_Position");
		glBindAttribLocation(m_ID, 1, "in_Color");
		glBindAttribLocation(m_ID, 2, "in_TexCoord");
		glBindAttribLocation(m_ID, 3, "in_Normal");

		glLinkProgram(m_ID);
		glGetProgramiv(m_ID, GL_LINK_STATUS, &success);

		//Checks for errors
		if (glGetError() != GL_NO_ERROR)
		{
			throw Oz::Exception("Cannot bind the shaders!");
		}

		glDetachShader(m_ID, vertexShaderId); //Detach the vertex shader
		glDeleteShader(vertexShaderId); //Delete the vertex shader
		glDetachShader(m_ID, fragmentShaderId); //Detach the fragment shader
		glDeleteShader(fragmentShaderId); //Delete the fragment shader
	}

	void cShaderProgram::Load(std::string _vert, std::string _frag)
	{
		std::string vertShader;
		std::string fragShader;

		std::ifstream file(_vert);

		if (!file.is_open()) {
			throw std::exception();
		}
		else {
			while (!file.eof()) {
				std::string line;
				std::getline(file, line);
				vertShader += line + "\n";
			}
		}
		file.close();

		file.open(_frag);

		if (!file.is_open()) {
			throw std::exception();
		}
		else {
			while (!file.eof()) {
				std::string line;
				std::getline(file, line);
				fragShader += line + "\n";
			}
		}
		file.close();

		const char *vertex = vertShader.c_str();
		const char *fragment = fragShader.c_str();

		GLuint vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexShaderId, 1, &vertex, NULL);
		glCompileShader(vertexShaderId);
		GLint success = 0;
		glGetShaderiv(vertexShaderId, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			throw std::exception();
		}

		GLuint fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShaderId, 1, &fragment, NULL);
		glCompileShader(fragmentShaderId);
		glGetShaderiv(fragmentShaderId, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			throw std::exception();
		}

		m_ID = glCreateProgram();
		glAttachShader(m_ID, vertexShaderId);
		glAttachShader(m_ID, fragmentShaderId);
		// Ensure the VAO "position" attribute stream gets set as the first position
		// during the link.
		glBindAttribLocation(m_ID, 0, "in_Position");
		glBindAttribLocation(m_ID, 1, "in_Color");
		glBindAttribLocation(m_ID, 2, "in_TexCoord");
		glBindAttribLocation(m_ID, 3, "in_Normal");

		if (glGetError() != GL_NO_ERROR) {
			throw std::exception();
		}
		// Perform the link and check for failure
		glLinkProgram(m_ID);
		glGetProgramiv(m_ID, GL_LINK_STATUS, &success);
		if (!success)
		{
			throw std::exception();
		}
		// Detach and destroy the shader objects. These are no longer needed
		// because we now have a complete shader program.
		glDetachShader(m_ID, vertexShaderId);
		glDeleteShader(vertexShaderId);
		glDetachShader(m_ID, fragmentShaderId);
		glDeleteShader(fragmentShaderId);
	}

	//Draw vertex array
	void cShaderProgram::Draw(std::weak_ptr<cVertexArray> _vertArray)
	{
		glUseProgram(m_ID); //Use the current shader program
		glBindVertexArray(_vertArray.lock()->getID());

		glDrawArrays(GL_TRIANGLES, 0, _vertArray.lock()->getVertexCount());

		glBindVertexArray(0);
		glUseProgram(0);
	}

	//Draw Mesh
	void cShaderProgram::Draw(std::shared_ptr<cMesh> _mesh)
	{
		glViewport(m_Viewport.x, m_Viewport.y, m_Viewport.z, m_Viewport.w); //Set the viewport
		glUseProgram(m_ID); //Use the current shader program
		glBindVertexArray(_mesh->m_Model->getID());

		for (size_t i = 0; i < m_TexSampler.size(); i++)
		{
			glActiveTexture(GL_TEXTURE0 + i);

			if (m_TexSampler.at(i).m_Texture)
			{
				glBindTexture(GL_TEXTURE_2D, m_TexSampler.at(i).m_Texture->getID());
			}
			else
			{
				glBindTexture(GL_TEXTURE_2D, 0);
			}
		}

		glDrawArrays(GL_TRIANGLES, 0, _mesh->m_Model->getVertexCount());

		for (size_t i = 0; i < m_TexSampler.size(); i++)
		{
			glActiveTexture(GL_TEXTURE0 + i);
			glBindTexture(GL_TEXTURE_2D, 0);
		}

		glBindVertexArray(0);
		glUseProgram(0);
	}

	//Draw Mesh and render texture
	void cShaderProgram::Draw(std::shared_ptr<cRenderTexture> _rendTexture, std::shared_ptr<cMesh> _mesh)
	{
		glBindFramebuffer(GL_FRAMEBUFFER, _rendTexture->getFbID());
		glm::vec4 lastViewport = m_Viewport;
		m_Viewport = glm::vec4(0, 0, _rendTexture->getSize().x, _rendTexture->getSize().y);
		Draw(_mesh);
		m_Viewport = lastViewport;
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	/*Set Uniform overloads */

	void cShaderProgram::setUniform(const std::string _uniform, glm::vec4 _value)
	{
		GLint uniformId = glGetUniformLocation(m_ID, _uniform.c_str());

		if (uniformId == -1)
		{
			throw std::exception();
		}

		glUseProgram(m_ID);
		glUniform4f(uniformId, _value.x, _value.y, _value.z, _value.w);
		glUseProgram(0);
	}

	void cShaderProgram::setUniform(const std::string _uniform, float _value)
	{
		GLint uniformId = glGetUniformLocation(m_ID, _uniform.c_str());

		if (uniformId == -1)
		{
			throw std::exception();
		}

		glUseProgram(m_ID);
		glUniform1f(uniformId, _value);
		glUseProgram(0);
	}

	void cShaderProgram::setUniform(const std::string _uniform, glm::mat4 _value)
	{
		GLint uniformId = glGetUniformLocation(m_ID, _uniform.c_str());

		if (uniformId == -1)
		{
			throw std::exception();
		}

		glUseProgram(m_ID);
		glUniformMatrix4fv(uniformId, 1, GL_FALSE, glm::value_ptr(_value));
		glUseProgram(0);
	}

	void cShaderProgram::setUniform(const std::string _uniform, std::weak_ptr<cTexture> _texture)
	{
		GLint uniformId = glGetUniformLocation(m_ID, _uniform.c_str());

		if (uniformId == -1)
		{
			return;
		}

		for (size_t i = 0; i < m_TexSampler.size(); i++)
		{
			if (m_TexSampler.at(i).m_ID == uniformId)
			{
				m_TexSampler.at(i).m_Texture = _texture.lock();

				glUseProgram(m_ID);
				glUniform1i(uniformId, i);
				glUseProgram(0);
				return;
			}
		}

		sTextureSampler texSampler;
		texSampler.m_ID = uniformId;
		texSampler.m_Texture = _texture.lock();
		m_TexSampler.push_back(texSampler);

		glUseProgram(m_ID);
		glUniform1i(uniformId, m_TexSampler.size() - 1);
		glUseProgram(0);
	}

	GLuint cShaderProgram::getID()
	{
		return m_ID;
	}

	void cShaderProgram::setViewport(glm::vec4 _viewport)
	{
		m_Viewport = _viewport; //Set the viewport
	}

	cShaderProgram::~cShaderProgram()
	{
		glDeleteProgram(m_ID);
	}
}