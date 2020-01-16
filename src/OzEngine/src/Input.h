#ifndef _CINPUT_H_
#define _CINPUT_H_

#include <vector>
#include <list>
#include <SDL2/SDL.h>
#include <glm/glm.hpp>

namespace Oz
{
	/* Input handler takes an SDL keycode and checks it */
	class cInputHandler
	{

		friend class cPlayerController;

	private:

		bool m_QuitCommand;
		bool m_BindMouse;

		std::list<int> m_Keys;
		std::vector<int> m_PressedKeys;
		std::vector<int> m_ReleasedKeys;

		SDL_Event m_Event = { 0 }; //Event variable to handle key checks
		const Uint8 *m_State = SDL_GetKeyboardState(NULL);

	public:

		void Update();

		bool getKey(int _key); //Check if a key is held down
		bool getKeyPressed(int _key); //Check if a key was pressed
		bool getKeyReleased(int _key); //Check if a key was released

		bool getMouseButtonPressed(int _button); //Check if a mouse button was pressed
		bool getMouseButtonReleased(int _button); //Check if a mouse button was released
		bool getMouseMovement(); //Check if the mouse has moved

		bool getMouseBind() { return m_BindMouse; } //Get the current state of the mouse

		glm::vec2 getMousePos(); //Get the current mouse position

		void clearHeld();
		void clearPressed();
		void clearReleased();

		bool quitCommand();

		~cInputHandler();
	};
}

#endif