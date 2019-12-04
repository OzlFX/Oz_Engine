#include "OzEngine.h"

namespace Oz
{
	//Constructor
	cCore::cCore()
	{

	}

	std::shared_ptr<cCore> cCore::Initialize(const char* _windowTitle, int _posX, int _posY, int _winW, int _winH, Uint32 _winFlags)
	{
		std::shared_ptr<cCore> core = std::make_shared<cCore>();
		core->m_Running = false;
		core->m_Self = core;

		//Initialise SDL Video
		if (SDL_Init(SDL_INIT_VIDEO) < 0)
		{
			//if SDL fails to initialises, an error is returned to the console and throws an exception
#if _DEBUG
			std::cout << "ERROR: " << SDL_GetError() << std::endl << "unable to initialize SDL!" << std::endl;
#endif
			throw std::exception();
		}

		core->m_Window = SDL_CreateWindow(_windowTitle, _posX, _posY, _winW, _winH, _winFlags); //Create the window for opengl

		//Checks to see if the window has been created and initialised
		if (core->m_Window == NULL)
		{
			//if the window doesnt exist, an error is returned to the console and closes the game
#if _DEBUG
			std::cout << "ERROR: " << SDL_GetError() << std::endl << "unable to create Window!" << std::endl;
#endif
			throw std::exception();
		}

		SDL_GLContext glContext = SDL_GL_CreateContext(core->m_Window);

		if (!glContext)
		{
			throw Oz::Exception("Failed to create OpenGL context");
		}

		//Init Context
		core->m_Context = cContext::Init();

		return core;
	}

	//Main Run function
	void cCore::Run()
	{
		m_Running = true;

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

		///Maybe???
		if (m_GameObject->getComponent<cMeshRenderer>())
		{
			m_Resources->Create<cMesh>() = m_Context->createMesh();
			m_Resources->Create<cShaderProgram>() = m_Context->createShader();
			m_Resources->Create<cMaterial>() = m_Context->createMaterial();
		}

		return m_GameObject;
	}

	//Destructor
	cCore::~cCore()
	{
		//Destroy the window
		SDL_DestroyWindow(m_Window);
		//Quit SDL
		SDL_Quit();
	}
}