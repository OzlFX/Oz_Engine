#ifndef _CCORE_H_
#define _CCORE_H_

//Includes
#include <iostream>
#include <memory>
#include <list>
#include <SDL2/SDL.h>

#include <glm/glm.hpp>

#include "NonCopyable.h"

namespace Oz
{
	class cGameObject;
	class cResources;
	class cMaterial;
	class cMesh;
	class cShaderProgram;
	class cContext;
	class cCamera;

	class cCore : private cNonCopyable
	{
	private:

		//Vars
		bool m_Running = false;
		SDL_Window* m_Window;

		std::weak_ptr<cCore> m_Self;

		std::shared_ptr<cContext> m_Context; //Context
		std::shared_ptr<cResources> m_Resources; //Resources
		std::shared_ptr<cShaderProgram> m_ModelShader; //Model Shader

		std::shared_ptr<cCamera> m_MainCamera; //Main Camera for the program

		std::list<std::shared_ptr<cGameObject>> m_GameObjects; //List of game objects
		std::list<std::shared_ptr<cMaterial>> m_Materials; //List of materials
		std::list<std::shared_ptr<cShaderProgram>> m_Shaders;

		int m_WinWidth, m_WinHeight; //Width and height of the window

		//Functions
		void Close(); //Main close function for the game engine

	public:
		cCore(); //Constructor

		static std::shared_ptr<cCore> Initialize(const char* _windowTitle, int _posX, int _posY, int _winW, int _winH, Uint32 _winFlags);

		void Run(); //Main run function for the game engine

		//Load shader
		std::shared_ptr<cShaderProgram> loadShader(std::string _path);
		std::shared_ptr<cShaderProgram> loadShader(std::string _vert, std::string _frag);

		std::shared_ptr<cGameObject> addGameObject(); //Add game objects
		std::shared_ptr<cMaterial> addMaterial(std::string _path); //Add material

		void createMaterial(std::string _name, std::string _texture, std::string _shader,
			glm::vec3 _ambient, glm::vec3 _diffuse, glm::vec3 _specular, float _shininess);

		std::shared_ptr<cShaderProgram> getShader();
		std::list<std::shared_ptr<cShaderProgram>> getShaders() const;
		
		void addShader(std::shared_ptr<cShaderProgram> _shader); //Add a new shader to render 
		void removeShader(std::shared_ptr<cShaderProgram> _shader); //Remove the desired shader

		std::shared_ptr<cResources> getResource(); //Get resource

		void setMainCamera(std::shared_ptr<cCamera> _mainCamera); //Set the main camera
		std::shared_ptr<cCamera> getMainCamera(); //Get the main camera

		//Get the window's size as a vec2. X is width and Y is height
		const glm::vec2 getWinSize()
		{
			return glm::vec2((float)m_WinWidth, (float)m_WinHeight);
		}

		SDL_Window* getWindow()
		{
			return m_Window;
		}

		~cCore(); //Destructor
	};
}

#endif