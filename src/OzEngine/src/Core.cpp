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

		core->m_WinWidth = _winW;
		core->m_WinHeight = _winH;

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

		core->m_InputHandler = std::make_shared<cInputHandler>();
		core->m_Time = std::make_shared<cEnvironment>();

		core->m_Resources = std::make_shared<cResources>();

		core->m_ModelShader = core->loadShader("../src/Resources/Shaders/ModelShader.glsl");

		return core;
	}

	std::shared_ptr<cInputHandler> cCore::getInputHandler()
	{
		return m_InputHandler;
	}

	std::shared_ptr<cShaderProgram> cCore::loadShader(std::string _path)
	{
		std::shared_ptr<cShaderProgram> shader = shader->Create(); //Create the resource
		shader->Load(_path); //Load a resource		

		m_Shaders.push_back(shader); //add new resource to the list
		return shader;
	}

	std::shared_ptr<cShaderProgram> cCore::loadShader(std::string _vert, std::string _frag)
	{
		std::shared_ptr<cShaderProgram> shader = shader->Create(); //Create the resource
		shader->Load(_vert, _frag); //Load a resource		

		m_Shaders.push_back(shader); //add new resource to the list
		return shader;
	}

	std::shared_ptr<cShaderProgram> cCore::loadShader(std::string _vert, std::string _frag, std::string _geom)
	{
		std::shared_ptr<cShaderProgram> shader = shader->Create(); //Create the resource
		shader->Load(_vert, _frag, _geom); //Load a resource		

		m_Shaders.push_back(shader); //add new resource to the list
		return shader;
	}

	std::shared_ptr<cShaderProgram> cCore::loadPostShader(std::string _path)
	{
		std::shared_ptr<cShaderProgram> shader = shader->Create(); //Create the resource
		shader->Load(_path); //Load a resource		

		m_PostShaders.push_back(shader); //add new resource to the list
		return shader;
	}

	std::shared_ptr<cShaderProgram> cCore::loadPostShader(std::string _vert, std::string _frag)
	{
		std::shared_ptr<cShaderProgram> shader = shader->Create(); //Create the resource
		shader->Load(_vert, _frag); //Load a resource		

		m_PostShaders.push_back(shader); //add new resource to the list
		return shader;
	}

	std::shared_ptr<cShaderProgram> cCore::loadPostShader(std::string _vert, std::string _frag, std::string _geom)
	{
		std::shared_ptr<cShaderProgram> shader = shader->Create(); //Create the resource
		shader->Load(_vert, _frag, _geom); //Load a resource		

		m_PostShaders.push_back(shader); //add new resource to the list
		return shader;
	}

	//Main Run function
	void cCore::Run()
	{
		m_Running = true;

		while (m_Running)
		{
			m_Time->calcFrames();

			m_InputHandler->Update();
			m_Running = !m_InputHandler->quitCommand();

			SDL_GetWindowSize(m_Window, &m_WinWidth, &m_WinHeight);
			
			if (m_InputHandler->getMouseBind()) SDL_WarpMouseInWindow(m_Window, m_WinWidth / 2, m_WinHeight / 2);

			glEnable(GL_CULL_FACE);
			glEnable(GL_DEPTH_TEST);

			glViewport(0, 0, m_WinWidth, m_WinHeight);

			//Clear gl
			glClearColor(0.03f, 0.03f, 0.03f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			for (std::list<std::shared_ptr<cShaderProgram>>::iterator it = m_Shaders.begin(); it != m_Shaders.end(); it++)
			{
				(*it)->setUniform("in_Projection", glm::perspective(glm::radians(45.0f), (float)m_WinWidth / (float)m_WinHeight, 0.1f, 100.0f));
			}

			//Update all objects in the list
			for (std::list<std::shared_ptr<cGameObject>>::iterator it = m_GameObjects.begin(); it != m_GameObjects.end(); it++)
			{
				(*it)->Update();
			}

			//Display all objects in the list
			for (std::list<std::shared_ptr<cGameObject>>::iterator it = m_GameObjects.begin(); it != m_GameObjects.end(); it++)
			{
				(*it)->Display();
			}
			
			//glDisable(GL_CULL_FACE);
			glDisable(GL_DEPTH_TEST);

			SDL_GL_SwapWindow(m_Window);

			m_Time->capFPS(144.0f);
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
		m_GameObject->m_Self = m_GameObject;
		m_GameObject->m_Core = m_Self;
		m_GameObjects.push_back(m_GameObject); //Add new game object to the list
		
		return m_GameObject;
	}

	std::shared_ptr<cGameObject> cCore::addLight(glm::vec3 _pos, glm::vec3 _rotation, glm::vec3 _scale, glm::vec3 _colour, float _intensity)
	{
		std::shared_ptr<cGameObject> m_Light = std::make_shared<cGameObject>(); //Make new light
		m_Light->m_Self = m_Light;
		m_Light->m_Core = m_Self;
		m_Light->addComponent<cTransform>(_pos, _rotation, _scale);
		m_Light->addComponent<cLight>(_colour, _intensity); //Set the light's values;

		m_Lights.push_back(m_Light);
		return m_Light;
	}

	std::list<std::shared_ptr<cGameObject>> cCore::getLights()
	{
		return m_Lights;
	}

	//Get resource
	std::shared_ptr<cResources> cCore::getResource()
	{
		return m_Resources;
	}

	void cCore::setMainCamera(std::shared_ptr<cCamera> _mainCamera)
	{
		m_MainCamera = _mainCamera;
	}

	std::shared_ptr<cCamera> cCore::getMainCamera()
	{
		return m_MainCamera;
	}

	/*std::shared_ptr<cShaderProgram> cCore::getShader(const std::shared_ptr<cShaderProgram> _shader)
	{
		for (std::list<std::shared_ptr<cShaderProgram>>::iterator it = m_Shaders.begin(); it != m_Shaders.end(); it++)
		{
			if ((*it) == _shader)
			{
				return (*it);
			}
			else
			{
				throw Oz::Exception("Cannot find specified shader!");
			}
		}
	}*/

	std::shared_ptr<cShaderProgram> cCore::getShader()
	{
		return m_ModelShader;
	}

	std::list<std::shared_ptr<cShaderProgram>> cCore::getShaders() const
	{
		return m_Shaders;
	}

	void cCore::removeShader(std::shared_ptr<cShaderProgram> _shader)
	{
		m_Shaders.remove(_shader); //Remove the shader
	}

	//Destructor
	cCore::~cCore()
	{
		//Delete the context
		//SDL_GL_DeleteContext(glContext);
		//Destroy the window
		SDL_DestroyWindow(m_Window);
		//Quit SDL
		SDL_Quit();
	}
}