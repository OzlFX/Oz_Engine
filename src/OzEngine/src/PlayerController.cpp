#include "Components/ComponentIncludes.h"
#include "PlayerController.h"
#include "Input.h"
#include "Core.h"

namespace Oz
{
	void cPlayerController::onInit(float _moveSpeed, bool _mouseControl)
	{
		m_MovementSpeed = _moveSpeed;
		
		m_Input = getCore()->getInputHandler();
		m_Input->m_BindMouse = _mouseControl;
	}

	void cPlayerController::onUpdate()
	{
		Move();
	}

	void cPlayerController::Move()
	{
		//Move Forwards
		if (m_Input->getKey(SDL_SCANCODE_W))
		{
			m_Move = getGameObject()->getTransform()->getPos();
			m_Move += getGameObject()->getTransform()->getForward() * m_MovementSpeed;
			getGameObject()->getTransform()->setPos(m_Move);
		}

		//Move Left
		if (m_Input->getKey(SDL_SCANCODE_A))
		{
			m_Move = getGameObject()->getTransform()->getPos();
			m_Move -= getGameObject()->getTransform()->getRight() * m_MovementSpeed;
			getGameObject()->getTransform()->setPos(m_Move);
		}

		//Move Right
		if (m_Input->getKey(SDL_SCANCODE_S))
		{
			m_Move = getGameObject()->getTransform()->getPos();
			m_Move += getGameObject()->getTransform()->getRight() * m_MovementSpeed;
			getGameObject()->getTransform()->setPos(m_Move);
		}

		//Move Backwards
		if (m_Input->getKey(SDL_SCANCODE_D))
		{
			m_Move = getGameObject()->getTransform()->getPos();
			m_Move -= getGameObject()->getTransform()->getForward() * m_MovementSpeed;
			getGameObject()->getTransform()->setPos(m_Move);
		}
	}

	void cPlayerController::Rotate()
	{
		if (m_Input->m_BindMouse)
		{

		}
	}
}