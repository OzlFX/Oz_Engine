#include "Program.h"

cProgram::cProgram()
{
	m_Program = Oz::cCore::Initialize("Oz Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1220, 880, SDL_WINDOW_OPENGL); //Create the program to run

	/* Add shader files to the program as follows:
	/* std::shared_ptr<Oz::cShaderProgram> shader = Program->loadShader("../src/Resources/Shaders/ModelShader.glsl");
	/* 
	/* using vert and frag shader files as follows also will work: ("../src/Resources/Shaders/simple.vert", "../src/Resources/Shaders/simple.frag");
	/* #NOTE: Model loader shader already pre-loaded into the game engine# */

	std::shared_ptr<Oz::cShaderProgram> lightKeyShader = m_Program->loadPostShader("../src/Resources/Shaders/lightkeypass.vert", "../src/Resources/Shaders/lightkeypass.frag");
	std::shared_ptr<Oz::cShaderProgram> blurShader = m_Program->loadPostShader("../src/Resources/Shaders/blur.vert", "../src/Resources/Shaders/blur.frag");
	std::shared_ptr<Oz::cShaderProgram> mergeShader = m_Program->loadPostShader("../src/Resources/Shaders/mergepass.vert", "../src/Resources/Shaders/mergepass.frag");
	std::shared_ptr<Oz::cShaderProgram> nullShader = m_Program->loadPostShader("../src/Resources/Shaders/nullpass.vert", "../src/Resources/Shaders/nullpass.frag");

	std::shared_ptr<Oz::cGameObject> world = m_Program->addGameObject(); //Add the world to the core
	std::shared_ptr<Oz::cGameObject> gameObject = m_Program->addGameObject(); //Add Game Object to the core
	std::shared_ptr<Oz::cGameObject> player = m_Program->addGameObject(); //Add player to the core

	/* Add lights here with Program->addLight()
	/* Make sure you parse in position, rotation and scale in that order :) */
	std::shared_ptr<Oz::cGameObject> light = m_Program->addLight(glm::vec3(1.0f, 6.0f, 8.0f), glm::vec3(0.0f), glm::vec3(1.0f), glm::vec3(1.0f), 1.0f);

	/* Add components to the gameobjects as follows:
	/* std::shared_ptr<Oz::cGameObject> object = Program->addGameObject();
	/* std::shared_ptr<Oz::[ComponentType]> componentname = object->addComponent<Oz::[ComponentType]>; */

	std::shared_ptr<Oz::cTransform> wtr = world->addComponent<Oz::cTransform>(glm::vec3(0.0f, -14.1f, -40.0f), glm::vec3(-90.0f, 0.0f, 20.0f), glm::vec3(50.0f));
	std::shared_ptr<Oz::cTransform> tr = gameObject->addComponent<Oz::cTransform>(glm::vec3(0.0f, -8.2f, -40.0f), glm::vec3(0.0f, 90.0f, 0.0f), glm::vec3(1.0f));

	std::shared_ptr<Oz::cTransform> Ptr = player->addComponent<Oz::cTransform>(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f));
	std::shared_ptr<Oz::cCamera> camera = player->addComponent<Oz::cCamera>();
	std::shared_ptr<Oz::cPlayerController> PC = player->addComponent<Oz::cPlayerController>(0.3f, true);
	std::shared_ptr<Oz::cBoxCollider> collider = player->addComponent<Oz::cBoxCollider>(glm::vec3(1.0f));

	m_Program->setMainCamera(camera);
	//gameObject->getComponent<Oz::cTransform>()->lookAt(glm::vec3 (2.0f, 0.0f, 1.0f));

	std::shared_ptr<Oz::cMeshRenderer> wmr = world->addComponent<Oz::cMeshRenderer>();
	std::shared_ptr<Oz::cMeshRenderer> mr = gameObject->addComponent<Oz::cMeshRenderer>();
	std::shared_ptr<Oz::cBoxCollider> GOcollider = gameObject->addComponent<Oz::cBoxCollider>(glm::vec3(1.0f));
	//std::shared_ptr<Oz::cMeshRenderer> hehe = player->addComponent<Oz::cMeshRenderer>();

	std::shared_ptr<Oz::cMesh> worldMesh = m_Program->getResource()->Load<Oz::cMesh>("../src/Resources/Models/re_hall_baked.obj"); //Load obj file
	std::shared_ptr<Oz::cTexture> worldTexture = m_Program->getResource()->Load<Oz::cTexture>("../src/Resources/Textures/re_hall_diffuse.png"); //Load the texture

	std::shared_ptr<Oz::cMesh> mesh = m_Program->getResource()->Load<Oz::cMesh>("../src/Resources/Models/sharprockfree.obj"); //Load obj file
	//std::shared_ptr<Oz::cTexture> texture = Program->getResource()->Load<Oz::cTexture>("../src/Resources/Textures/Whiskers_diffuse.png"); //Load the texture
	std::shared_ptr<Oz::cMaterial> material = m_Program->getResource()->Load<Oz::cMaterial>("../src/Resources/Materials/Test.m4t"); //Load a material

	wmr->setMesh(worldMesh);
	wmr->setTexture(worldTexture);

	mr->setMesh(mesh);
	mr->setMaterial(material);
	//mr->setTexture(texture);

	//hehe->setMesh(mesh);
	//hehe->setTexture(texture);

	//std::shared_ptr<Oz::cMaterial> material = Program->getResource()->Load<Oz::cMaterial>("../src/Resources/Materials/Test.m4t"); //Load the shader
	//std::shared_ptr<Oz::cRenderTexture> rt = Program->getResource()->Load<Oz::cRenderTexture>();

	//mr->setMaterial(material);
}

void cProgram::Run()
{
	try
	{
		m_Program->Run(); //Start and run the program
	}
	catch (Oz::Exception& exception)
	{
		std::cout << "OzEngine Exception: " << exception.what() << std::endl;
	}
	catch (std::exception& exception)
	{
		std::cout << "Exception: " << exception.what() << std::endl;
	}
	catch (...)
	{
		std::cout << "An unknown object was thrown, duck!" << std::endl;
	}
}

cProgram::~cProgram()
{

}