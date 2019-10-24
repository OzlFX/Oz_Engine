#ifndef _CORE_H_
#define _CORE_H_

//Includes
#include <iostream>
#include <memory>
#include <list>
#include <SDL2/SDL.h>

namespace Oz
{
	class cGameObject;

	class cCore
	{
	private:

		//Vars
		bool m_Running = false;
		SDL_Window* m_Window;

		std::weak_ptr<cCore> m_Self;

		std::list<std::shared_ptr<cGameObject>> m_GameObjects; //List of game objects

		//Functions
		bool Init(); //Initization function
		std::shared_ptr<cCore> Initialize();
		SDL_Window* createWindow(); //Create Window

	public:
		cCore(); //Constructor

		void Run(); //Main run function for the game engine
		void Close(); //Main close function for the game engine

		std::shared_ptr<cGameObject> addGameObject();

		~cCore(); //Destructor
	};
}
#endif // !_CORE_H_