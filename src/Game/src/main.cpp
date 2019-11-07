#include <OzEngine/src/OzEngine.h>

int main()
{
	std::shared_ptr<Oz::cCore> Program = Oz::cCore::Initialize("Oz Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1220, 880, SDL_WINDOW_OPENGL); //std::make_unique<Oz::cCore>();
	std::shared_ptr<Oz::cGameObject> gameObject = Program->addGameObject(); //Add Game Object to the core

	///Add components to the gameobjects here:
	/// std::shared_ptr object = gameObject->addComponent componentname;
	
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