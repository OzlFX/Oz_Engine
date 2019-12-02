#include <OzEngine/src/OzEngine.h>

int main()
{
	std::shared_ptr<Oz::cCore> Program = Oz::cCore::Initialize("Oz Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1220, 880, SDL_WINDOW_OPENGL); //Create the program to run
	std::shared_ptr<Oz::cGameObject> gameObject = Program->addGameObject(); //Add Game Object to the core
	///Add components to the gameobjects here:
	/// std::shared_ptr object = gameObject->addComponent componentname;
	
	std::shared_ptr<Oz::cTransform> tr = gameObject->addComponent<Oz::cTransform>();
	//gameObject->getComponent<Oz::cTransform>()->lookAt(glm::vec3 (2.0f, 0.0f, 1.0f));
	//std::shared_ptr<Oz::cMesh> mesh = Program->addResource("../src/Resources/Models/curuthers.obj");

	std::shared_ptr<Oz::cMeshRenderer> mr = gameObject->addComponent<Oz::cMeshRenderer>();
	//std::shared_ptr<Oz::cMesh> mesh = Program->getResource()->Load<Oz::cMesh>("../src/Resources/Models/curuthers.obj"); //Load obj file
	//mr->setMesh(mesh);

	//std::shared_ptr<Oz::cMaterial> material = Program->getResource()->Load<Oz::cMaterial>("../src/Resources/Shaders/TestShader.glsl"); //Load the shader
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