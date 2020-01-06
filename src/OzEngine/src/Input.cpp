#include "Input.h"

namespace Oz
{
	bool cInputHandler::getKey(int _key)
	{
		const Uint8 *state = SDL_GetKeyboardState(NULL);

		while (SDL_PollEvent(&m_Event))
		{
			if (state[_key])
			{
				m_Keys.push_back(_key);

				return true;
			}
			else
			{
				return false;
			}
		}
	}

	bool cInputHandler::getKeyPressed(int _key)
	{
		while (SDL_PollEvent(&m_Event))
		{
			if (m_Event.type == SDL_KEYDOWN)
			{
				if (m_Event.key.keysym.sym == _key)
				{
					m_PressedKeys.push_back(_key);

					return true;
				}
				else
				{
					return false;
				}
			}
			else
			{
				return false;
			}
		}
	}

	bool cInputHandler::getKeyReleased(int _key)
	{
		while (SDL_PollEvent(&m_Event))
		{
			if (m_Event.type == SDL_KEYUP)
			{
				if (m_Event.key.keysym.sym == _key)
				{
					m_ReleasedKeys.push_back(_key);

					return true;
				}
				else
				{
					return false;
				}
			}
			else
			{
				return false;
			}
		}
	}

	bool cInputHandler::getMouseButtonPressed(int _button)
	{
		while (SDL_PollEvent(&m_Event))
		{
			if (m_Event.type == SDL_MOUSEBUTTONDOWN)
			{
				if (m_Event.button.button == _button)
				{
					m_ReleasedKeys.push_back(_button);

					return true;
				}
				else
				{
					return false;
				}
			}
			else
			{
				return false;
			}
		}
	}

	bool cInputHandler::getMouseButtonReleased(int _button)
	{
		while (SDL_PollEvent(&m_Event))
		{
			if (m_Event.type == SDL_MOUSEBUTTONUP)
			{
				if (m_Event.button.button == _button)
				{
					m_ReleasedKeys.push_back(_button);

					return true;
				}
				else
				{
					return false;
				}
			}
			else
			{
				return false;
			}
		}
	}

	bool cInputHandler::getMouseMovement()
	{
		if (m_Event.type == SDL_MOUSEMOTION)
		{
			return true;
		}

		return false;
	}

	glm::vec2 cInputHandler::getMousePos()
	{
		return glm::vec2(m_Event.motion.x, m_Event.motion.y);
	}

	void cInputHandler::Clear()
	{
		m_Keys.clear();
		m_PressedKeys.clear();
		m_ReleasedKeys.clear();
	}
}