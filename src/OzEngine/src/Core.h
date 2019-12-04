#ifndef _CCORE_H_
#define _CCORE_H_

//Includes
#include <iostream>
#include <memory>
#include <list>
#include <SDL2/SDL.h>

#include "NonCopyable.h"

namespace Oz
{
	class cGameObject;
	class cResources;
	class cMaterial;
	class cContext;

	class cCore : private cNonCopyable
	{
	private:

		//Vars
		bool m_Running = false;
		SDL_Window* m_Window;

		std::weak_ptr<cCore> m_Self;

		std::shared_ptr<cContext> m_Context;
		std::shared_ptr<cResources> m_Resources; //Resources

		std::list<std::shared_ptr<cGameObject>> m_GameObjects; //List of game objects

		//Functions
		void Close(); //Main close function for the game engine

	public:
		cCore(); //Constructor

		static std::shared_ptr<cCore> Initialize(const char* _windowTitle, int _posX, int _posY, int _winW, int _winH, Uint32 _winFlags);

		void Run(); //Main run function for the game engine

		std::shared_ptr<cGameObject> addGameObject();
		
		std::shared_ptr<cResources> getResource()
		{
			return m_Self.lock()->m_Resources;
		}

		~cCore(); //Destructor
	};
}

#endif