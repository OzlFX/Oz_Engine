#include "ShaderProgram.h"
#include "VertexArray.h"
#include "OzEngine/src/Exception.h"

#include <glm/ext.hpp>

#include <fstream>
#include <iostream>

namespace Oz
{
	cShaderProgram::cShaderProgram(std::string _vert, std::string _frag)
	{
		std::ifstream file(_vert.c_str());
		std::string vert;

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
			vert += line + "\n";
		}

		file.close(); //Close current file
		file.open(_frag.c_str()); //Open new file

		std::string frag;

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
			frag += line + "\n";
		}

		const GLchar *vs = vert.c_str(); //Convert vertex string into GLchar for the GPU to use

		GLuint vertexShaderId = glCreateShader(GL_VERTEX_SHADER); //Create the vertex shader
		glShaderSource(vertexShaderId, 1, &vs, NULL); //Set the shader source and get the vertex shader file contents
		glCompileShader(vertexShaderId); //Compile the shader
		GLint success = 0;
		glGetShaderiv(vertexShaderId, GL_COMPILE_STATUS, &success);

		//Check if compile was successful
		if (!success)
		{
			throw Oz::Exception("Shader not compiled correctly");
		}

		const GLchar *fs = frag.c_str(); //Convert fragment string into GLchar for the GPU to use

		GLuint fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER); //Create the fragment shader
		glShaderSource(fragmentShaderId, 1, &fs, NULL); //Set the shader source and get the fragment shader file contents
		glCompileShader(fragmentShaderId); //Compile the shader
		glGetShaderiv(fragmentShaderId, GL_COMPILE_STATUS, &success);

		//Check if compile was successful
		if (!success)
		{
			throw Oz::Exception("Shader not compiled correctly");
		}

		m_ID = glCreateProgram(); //Create the shader program
		glAttachShader(m_ID, vertexShaderId); //Attach the vertex shader to the shader program
		glAttachShader(m_ID, fragmentShaderId); //Attach the fragment shader to the shader program

		//Bind the shaders
		glBindAttribLocation(m_ID, 0, "in_Position");
		glBindAttribLocation(m_ID, 1, "in_Color");

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

	//Draw
	void cShaderProgram::Draw(std::weak_ptr<VertexArray> _vertArray)
	{
		glUseProgram(m_ID); //Use the current shader program
		glBindVertexArray(_vertArray.lock()->getID());

		glDrawArrays(GL_TRIANGLES, 0, _vertArray.lock()->getVertexCount());

		glBindVertexArray(0);
		glUseProgram(0);
	}

	/*Set Uniform overloads */

	void cShaderProgram::setUniform(std::string _uniform, glm::vec4 _value)
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

	void cShaderProgram::setUniform(std::string _uniform, float _value)
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

	void cShaderProgram::setUniform(std::string _uniform, glm::mat4 _value)
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

	GLuint cShaderProgram::getID()
	{
		return m_ID;
	}

	cShaderProgram::~cShaderProgram()
	{

	}
}