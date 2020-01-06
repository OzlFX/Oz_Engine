#include <OzEngine/src/OzEngine.h>

int main()
{
	std::shared_ptr<Oz::cCore> Program = Oz::cCore::Initialize("Oz Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1220, 880, SDL_WINDOW_OPENGL); //Create the program to run

	/* Add shader files to the program as follows:
	/* std::shared_ptr<Oz::cShaderProgram> shader = Program->getResource()->Load<Oz::cShaderProgram>("../src/Resources/Shaders/ModelShader.glsl");
	/* Program->addShader(shader);
	/* using vert and frag shader files as follows also will work: ("../src/Resources/Shaders/simple.vert", "../src/Resources/Shaders/simple.frag"); 
	/* #NOTE: Model loader shader already pre-loaded into the game engine# */

	std::shared_ptr<Oz::cGameObject> gameObject = Program->addGameObject(); //Add Game Object to the core
	std::shared_ptr<Oz::cGameObject> player = Program->addGameObject(); //Add player to the core

	/* Add components to the gameobjects as follows:
	/* std::shared_ptr<Oz::cGameObject> object = Program->addGameObject();
	/* std::shared_ptr<Oz::[ComponentType]> componentname = object->addComponent<Oz::[ComponentType]>; */
	
	std::shared_ptr<Oz::cTransform> tr = gameObject->addComponent<Oz::cTransform>();
	std::shared_ptr<Oz::cTransform> Ptr = player->addComponent<Oz::cTransform>();
	std::shared_ptr<Oz::cCamera> camera = player->addComponent<Oz::cCamera>();

	Program->setMainCamera(camera);
	//gameObject->getComponent<Oz::cTransform>()->lookAt(glm::vec3 (2.0f, 0.0f, 1.0f));
	
	std::shared_ptr<Oz::cMeshRenderer> mr = gameObject->addComponent<Oz::cMeshRenderer>();
	std::shared_ptr<Oz::cMeshRenderer> hehe = player->addComponent<Oz::cMeshRenderer>();

	std::shared_ptr<Oz::cMesh> mesh = Program->getResource()->Load<Oz::cMesh>("../src/Resources/Models/curuthers.obj"); //Load obj file
	std::shared_ptr<Oz::cTexture> texture = Program->getResource()->Load<Oz::cTexture>("../src/Resources/Textures/Whiskers_diffuse.png"); //Load the texture

	mr->setMesh(mesh);
	mr->setTexture(texture);
	
	hehe->setMesh(mesh);
	hehe->setTexture(texture);

	//std::shared_ptr<Oz::cMaterial> material = Program->getResource()->Load<Oz::cMaterial>("../src/Resources/Materials/Test.m4t"); //Load the shader
	//std::shared_ptr<Oz::cRenderTexture> rt = Program->getResource()->Load<Oz::cRenderTexture>();

	//mr->setMaterial(material);

	try
	{
		Program->Run(); //Start and run the program
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

	return 0;
}