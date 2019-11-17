//Includes
#include <iostream>
#include <memory>
#include <list>
#include <SDL2/SDL.h>

#include "NonCopyable.h"

namespace Oz
{
	class cGameObject;

	class cCore : private cNonCopyable
	{
	private:

		//Vars
		bool m_Running = false;
		SDL_Window* m_Window;

		std::weak_ptr<cCore> m_Self;

		std::list<std::shared_ptr<cGameObject>> m_GameObjects; //List of game objects

		//Functions


	public:
		cCore(); //Constructor

		static std::shared_ptr<cCore> Initialize(const char* _windowTitle, int _posX, int _posY, int _winW, int _winH, Uint32 _winFlags);

		void Run(); //Main run function for the game engine
		void Close(); //Main close function for the game engine

		std::shared_ptr<cGameObject> addGameObject();

		~cCore(); //Destructor
	};
}