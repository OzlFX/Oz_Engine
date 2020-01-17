#include "Components/ComponentIncludes.h"
#include "PlayerController.h"
#include "Input.h"
#include "Camera.h"
#include "Environment.h"

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
		Rotate();
	}

	void cPlayerController::Move()
	{
		//Move Forwards
		if (m_Input->getKey(SDLK_w))
		{
			getGameObject()->getTransform()->setPos(getGameObject()->getTransform()->getPos() - 
				(getGameObject()->getTransform()->getForward() * m_MovementSpeed));
		}

		//Move Left
		if (m_Input->getKey(SDLK_a))
		{
			getGameObject()->getTransform()->setPos(getGameObject()->getTransform()->getPos() +
				(getGameObject()->getTransform()->getRight() * m_MovementSpeed));
		}

		//Move Right
		if (m_Input->getKey(SDLK_d))
		{
			getGameObject()->getTransform()->setPos(getGameObject()->getTransform()->getPos() -
				(getGameObject()->getTransform()->getRight() * m_MovementSpeed));
		}

		//Move Backwards
		if (m_Input->getKey(SDLK_s))
		{
			getGameObject()->getTransform()->setPos(getGameObject()->getTransform()->getPos() +
				(getGameObject()->getTransform()->getForward() * m_MovementSpeed));
		}
	}

	void cPlayerController::Rotate()
	{
		if (m_Input->m_BindMouse)
		{
			getCore()->getMainCamera()->Rotate();
		}
	}
}