#include "OzEngine.h"
#include <fstream>

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

		core->m_Resources = std::make_shared<cResources>();

		core->m_ModelShader = core->loadShader("../src/Resources/Shaders/ModelShader.glsl");

		return core;
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

			SDL_GetWindowSize(m_Window, &m_WinWidth, &m_WinHeight);

			//Clear gl
			glClearColor(0.03f, 0.03f, 0.03f, 0.6f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			//Update all objects in the list
			for (std::list<std::shared_ptr<cGameObject>>::iterator it = m_GameObjects.begin(); it != m_GameObjects.end(); it++)
			{
				(*it)->Update();
			}

			glEnable(GL_CULL_FACE);
			glEnable(GL_DEPTH_TEST);

			//Display all objects in the list
			for (std::list<std::shared_ptr<cGameObject>>::iterator it = m_GameObjects.begin(); it != m_GameObjects.end(); it++)
			{
				(*it)->Display();
			}
			
			//glDisable(GL_CULL_FACE);
			glDisable(GL_DEPTH_TEST);

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
		m_GameObject->m_Self = m_GameObject;
		m_GameObject->m_Core = m_Self;
		m_GameObjects.push_back(m_GameObject); //Add new game object to the list
		
		return m_GameObject;
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

	void cCore::createMaterial(std::string _name, std::string _texture, std::string _shader,
		glm::vec3 _ambient, glm::vec3 _diffuse, glm::vec3 _specular, float _shininess)
	{
		std::string ambient = std::to_string(_ambient.x) + " " + std::to_string(_ambient.y) + " " + std::to_string(_ambient.z);
		std::string diffuse = std::to_string(_diffuse.x) + " " + std::to_string(_diffuse.y) + " " + std::to_string(_diffuse.z);
		std::string specular = std::to_string(_specular.x) + " " + std::to_string(_specular.y) + " " + std::to_string(_specular.z);
		std::string shininess = std::to_string(_shininess);

		std::ofstream file("../src/Resources/Materials/" + _name + ".m4t", std::ios::out);
		file << "#Material" <<
			std::endl <<
			"string Name = " + _name 
			+ ";" <<
			std::endl <<
			"string Texture src = "
			+ _texture 
			+ ";" <<
			std::endl <<
			"string Shader src = "
			+ _shader 
			+ ";" <<
			std::endl <<
			"vec3 Ambient = "
			+ ambient 
			+ ";" <<
			std::endl <<
			"vec3 Diffuse = "
			+ diffuse 
			+ ";" <<
			std::endl <<
			"vec3 Specular = "
			+ specular 
			+ ";" <<
			std::endl <<
			"vec3 Shininess = "
			+ shininess
			+ ";";
		file.close();
	}

	//Add material
	std::shared_ptr<cMaterial> cCore::addMaterial(std::string _path)
	{
		std::shared_ptr<cMaterial> m_Material = m_Material->Create();
		m_Material->Load(_path);
		m_Materials.push_back(m_Material);

		return m_Material;
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

	void cCore::addShader(std::shared_ptr<cShaderProgram> _shader)
	{
		m_Shaders.push_back(_shader); //Add new shader to render from
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