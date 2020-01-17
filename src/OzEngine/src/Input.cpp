#include "Input.h"

namespace Oz
{
	void cInputHandler::Update(SDL_Event* _event)
	{
		m_PressedKeys.clear();
		m_ReleasedKeys.clear();
		m_Keys.clear();

		m_Event = _event;

		if (m_BindMouse)
		{
			SDL_ShowCursor(SDL_DISABLE);
			SDL_SetRelativeMouseMode(SDL_TRUE);
		}
		else
		{
			SDL_ShowCursor(SDL_ENABLE);
			SDL_SetRelativeMouseMode(SDL_FALSE);
		}

		while (SDL_PollEvent(_event))
		{
			switch (_event->type)
			{
			case SDL_QUIT:
				m_QuitCommand = true;
				break;
			case SDL_KEYDOWN:
				m_PressedKeys.push_back(_event->key.keysym.sym);
				if (std::find(m_Keys.begin(), m_Keys.end(), _event->key.keysym.sym) != m_Keys.end()) {
					//Do nothing
					/* I would put something here but since its being ignored, just imagine Im singing :) */
				}
				else
					m_Keys.push_back(_event->key.keysym.sym);
				break;
			case SDL_KEYUP:
				m_ReleasedKeys.push_back(_event->key.keysym.sym);
				for (int i = 0; i < m_Keys.size(); i++)
				{
					if (m_Keys.at(i) == _event->key.keysym.sym)
						m_Keys.erase(m_Keys.begin() + i);
				}
				break;
			case SDL_MOUSEBUTTONDOWN:
				m_PressedKeys.push_back(_event->key.keysym.sym);
				if (std::find(m_Keys.begin(), m_Keys.end(), _event->key.keysym.sym) != m_Keys.end()) {
					//Do nothing
					/* I would put something here but since its being ignored, just imagine Im singing :) */
				}
				else
					m_Keys.push_back(_event->key.keysym.sym);
				break;
			case SDL_MOUSEBUTTONUP:
				m_ReleasedKeys.push_back(_event->key.keysym.sym);
				for (int i = 0; i < m_Keys.size(); i++)
				{
					if (m_Keys.at(i) == _event->key.keysym.sym)
						m_Keys.erase(m_Keys.begin() + i);
				}
				break;
			}

			if (_event->key.keysym.sym == SDLK_ESCAPE)
			{
				m_BindMouse = false;
			}

		}
	}

	bool cInputHandler::getKey(int _key)
	{
		for (int i = 0; i < m_PressedKeys.size(); ++i)
		{
			if (m_Keys.at(i) == _key)
			{
				return true;
			}
		}
		return false;
	}

	bool cInputHandler::getKeyPressed(int _key)
	{
		for (int i = 0; i < m_PressedKeys.size(); ++i)
		{
			if (m_PressedKeys.at(i) == _key)
			{
				return true;
			}
		}
		return false;
	}

	bool cInputHandler::getKeyReleased(int _key)
	{
		for (int i = 0; i < m_ReleasedKeys.size(); ++i)
		{
			if (m_ReleasedKeys.at(i) == _key)
			{
				return true;
			}
		}
		return false;
	}

	bool cInputHandler::getMouseButtonPressed(int _button)
	{
		for (int i = 0; i < m_PressedKeys.size(); ++i)
		{
			if (m_PressedKeys.at(i) == _button)
			{
				return true;
			}
		}
		return false;
	}

	bool cInputHandler::getMouseButtonReleased(int _button)
	{
		for (int i = 0; i < m_ReleasedKeys.size(); ++i)
		{
			if (m_ReleasedKeys.at(i) == _button)
			{
				return true;
			}
		}
		return false;
	}

	bool cInputHandler::getMouseMovement()
	{
		if (m_Event->type == SDL_MOUSEMOTION)
		{
			return true;
		}

		return false;
	}

	glm::vec2 cInputHandler::getMousePos()
	{
		return glm::vec2(m_Event->motion.xrel, m_Event->motion.yrel);
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