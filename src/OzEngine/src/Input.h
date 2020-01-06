#ifndef _CINPUT_H_
#define _CINPUT_H_

#include <vector>
#include <SDL2/SDL.h>
#include <glm/glm.hpp>

namespace Oz
{
	/* Input handler takes an SDL keycode and checks it */

	class cInputHandler
	{
	private:

		SDL_Event m_Event = { 0 }; //Event variable to handle key checks

		std::vector<int> m_Keys;
		std::vector<int> m_PressedKeys;
		std::vector<int> m_ReleasedKeys;

	public:

		bool getKey(int _key); //Check if a key is held down
		bool getKeyPressed(int _key); //Check if a key was pressed
		bool getKeyReleased(int _key); //Check if a key was released

		bool getMouseButtonPressed(int _button); //Check if a mouse button was pressed
		bool getMouseButtonReleased(int _button); //Check if a mouse button was released
		bool getMouseMovement(); //Check if the mouse has moved

		glm::vec2 getMousePos(); //Get the current mouse position

		void Clear();
	};
}

#endif