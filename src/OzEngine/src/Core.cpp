#include "Core.h"
#include "GameObject.h"

#include <GL/glew.h>

namespace Oz
{
	//Constructor
	cCore::cCore()
	{

	}

	std::shared_ptr<cCore> cCore::Initialize()
	{
		std::shared_ptr<cCore> core = std::make_shared<cCore>();
		core->m_Running = false;
		core->m_Self = core;

		core->m_Window = createWindow(); //Create the window

		//Check to see if the window was created
		if (createWindow() == NULL)
		{
#if _DEBUG
			std::cout << "Closing program due to issue with the window, can't see through it!" << std::endl;
#endif
			m_Running = false; //Close the program if error occurs
		}

		//Checks if initialization was successful
		if (Init() != true)
		{
			throw std::exception();
		}

		return core;
	}

	bool cCore::Init()
	{
		//Initialise SDL Video
		if (SDL_Init(SDL_INIT_VIDEO) < 0)
		{
			//if SDL fails to initialises, an error is returned to the console and throws an exception
#if _DEBUG
			std::cout << "ERROR: " << SDL_GetError() << std::endl << "unable to initialize SDL!" << std::endl;
#endif
			return false;
		}

		//Initialise SDL Video
		if (glewInit() != GLEW_OK)
		{
			//if glew fails to initialises, an error is returned to the console and throws an exception
#if _DEBUG
			std::cout << "ERROR: unable to initialize glew!" << std::endl;
#endif
			return false;
		}

		return true;
	}

	SDL_Window* cCore::createWindow()
	{
		SDL_Window* _window = SDL_CreateWindow("Oz Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1220, 880, SDL_WINDOW_OPENGL); //Create the window for opengl

		//Checks to see if the window has been created and initialised
		if (_window == NULL)
		{
			//if the window doesnt exist, an error is returned to the console and closes the game
#if _DEBUG
			std::cout << "ERROR: " << SDL_GetError() << std::endl << "unable to create Window!" << std::endl;
#endif
			return NULL;
		}

		return _window;
	}

	//Main Run function
	void cCore::Run()
	{
		while (m_Running)
		{
			SDL_Event m_Event = { 0 };

			while (SDL_PollEvent(&m_Event))
			{
				if (m_Event.type == SDL_QUIT)
				{
					Close();
				}
			}

			//Update all objects in the list
			for (std::list<std::shared_ptr<cGameObject>>::iterator it = m_GameObjects.begin(); it != m_GameObjects.end(); it++)
			{
				(*it)->Update();
			}

			//Clear gl
			glClearColor(0.0f, 0.3f, 0.0f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			//Display all objects in the list
			for (std::list<std::shared_ptr<cGameObject>>::iterator it = m_GameObjects.begin(); it != m_GameObjects.end(); it++)
			{
				(*it)->Display();
			}

			SDL_GL_SwapWindow(m_Window);
		}
	}

	//Main Close function
	void cCore::Close()
	{
		m_Running = false;
	}

	//Add game objects
	std::shared_ptr<cGameObject> cCore::addGameObject()
	{
		std::shared_ptr<cGameObject> m_GameObject = std::make_shared<cGameObject>(); //Make a new game object
		m_GameObjects.push_back(m_GameObject); //Add new game object to the list
		m_GameObject->m_Self = m_GameObject;
		m_GameObject->m_Core = m_Self;
	}

	//Destructor
	cCore::~cCore()
	{
		//Clear gameobject list
		m_GameObjects.erase;
		//Destroy the window
		SDL_DestroyWindow(m_Window);
		//Quit SDL
		SDL_Quit();
	}
}