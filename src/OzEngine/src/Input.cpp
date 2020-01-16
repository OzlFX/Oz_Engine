#include "Input.h"

namespace Oz
{
	void cInputHandler::Update()
	{
		m_PressedKeys.clear();
		m_ReleasedKeys.clear();

		if (m_BindMouse)
		{
			SDL_ShowCursor(SDL_DISABLE);
			SDL_SetRelativeMouseMode(SDL_TRUE);
		}

		while (SDL_PollEvent(&m_Event))
		{
			if (m_Event.type == SDL_QUIT)
			{
				m_QuitCommand = true;
			}

			//for (std::list<int>::iterator it = m_Keys.begin(); it != m_Keys.end(); it++)
			//{
			//	m_State[*it];
			//}
		}
	}

	bool cInputHandler::getKey(int _key)
	{
		if (m_State[_key])
		{
			m_Keys.push_back(_key);
			m_PressedKeys.push_back(_key);

			return true;
		}
		else
		{
			m_Keys.remove(_key);
			m_ReleasedKeys.push_back(_key);
			return false;
		}
	}

	bool cInputHandler::getKeyPressed(int _key)
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

	bool cInputHandler::getKeyReleased(int _key)
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

	bool cInputHandler::getMouseButtonPressed(int _button)
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

	bool cInputHandler::getMouseButtonReleased(int _button)
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

	void cInputHandler::clearHeld()
	{
		m_Keys.clear();
	}

	void cInputHandler::clearPressed()
	{
		m_PressedKeys.clear();
	}

	void cInputHandler::clearReleased()
	{
		m_ReleasedKeys.clear();
	}

	bool cInputHandler::quitCommand()
	{
		return m_QuitCommand;
	}

	cInputHandler::~cInputHandler()
	{
		m_Keys.clear();
		m_PressedKeys.clear();
		m_ReleasedKeys.clear();
	}
}