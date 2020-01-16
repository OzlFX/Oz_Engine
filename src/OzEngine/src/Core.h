#ifndef _CCORE_H_
#define _CCORE_H_

//Includes
#include <iostream>
#include <memory>
#include <list>
#include <vector>
#include <SDL2/SDL.h>

#include <glm/glm.hpp>

#include "NonCopyable.h"

namespace Oz
{
	class cGameObject;
	class cResources;
	class cShaderProgram;
	class cContext;
	class cCamera;
	class cInputHandler;
	class cEnvironment;

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
		std::shared_ptr<cInputHandler> m_InputHandler; //Input handler for the program
		std::shared_ptr<cEnvironment> m_Time; //Handler for the time within the program

		std::list<std::shared_ptr<cGameObject>> m_GameObjects; //List of game objects

		std::list<std::shared_ptr<cShaderProgram>> m_Shaders; //List of shaders
		std::list<std::shared_ptr<cShaderProgram>> m_PostShaders; //List of post processing shaders

		std::list<std::shared_ptr<cGameObject>> m_Lights;

		int m_WinWidth, m_WinHeight; //Width and height of the window

		//Functions
		void Close(); //Main close function for the game engine

	public:
		cCore(); //Constructor

		static std::shared_ptr<cCore> Initialize(const char* _windowTitle, int _posX, int _posY, int _winW, int _winH, Uint32 _winFlags);

		void Run(); //Main run function for the game engine

		//Load shaders
		std::shared_ptr<cShaderProgram> loadShader(std::string _path);
		std::shared_ptr<cShaderProgram> loadShader(std::string _vert, std::string _frag);
		std::shared_ptr<cShaderProgram> loadShader(std::string _vert, std::string _frag, std::string _geom);

		//Load post processing shaders
		std::shared_ptr<cShaderProgram> loadPostShader(std::string _path);
		std::shared_ptr<cShaderProgram> loadPostShader(std::string _vert, std::string _frag);
		std::shared_ptr<cShaderProgram> loadPostShader(std::string _vert, std::string _frag, std::string _geom);

		std::shared_ptr<cGameObject> addGameObject(); //Add game objects
		
		//Add light by using a position, rotation, scale and light type; rest is taken care of ;)
		std::shared_ptr<cGameObject> addLight(glm::vec3 _pos, glm::vec3 _rotation, glm::vec3 _scale, glm::vec3 _colour, float _intensity);
		
		template <typename T>
		void getGameObjects(std::vector<std::shared_ptr<cGameObject>> &_gameObjects)
		{
			std::shared_ptr<T> component;
			for (std::list<std::shared_ptr<cGameObject>>::iterator it = m_GameObjects.begin(); it != m_GameObjects.end(); ++it)
			{
				std::list<std::shared_ptr<cComponent>> components = (*it)->getComponents();
				for (std::list<std::shared_ptr<cComponent>>::iterator jit = components.begin(); jit != components.end(); ++jit)
				{
					component = std::dynamic_pointer_cast<T>(*jit);
					if (component)
					{
						_gameObjects.push_back(*it);
						component = NULL;
					}
				}
			}
		}

		std::list<std::shared_ptr<cGameObject>> getLights();

		std::shared_ptr<cShaderProgram> getShader();
		std::list<std::shared_ptr<cShaderProgram>> getShaders() const;
 
		void removeShader(std::shared_ptr<cShaderProgram> _shader); //Remove the desired shader

		std::shared_ptr<cResources> getResource(); //Get resource

		std::shared_ptr<cInputHandler> getInputHandler(); //Get the program's input handler

		void setMainCamera(std::shared_ptr<cCamera> _mainCamera); //Set the main camera
		std::shared_ptr<cCamera> getMainCamera(); //Get the main camera

		//Get the window's size as a vec2. X is width and Y is height
		glm::vec2 getWinSize() const
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