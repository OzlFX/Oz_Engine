#ifndef _CPLAYERCONTROLLER_H_
#define _CPLAYERCONTROLLER_H_

//Includes
#include "Components.h"

#include <memory>

namespace Oz
{
	class cInputHandler;

	/* Player controller component handles basic player inputs, allowing for movement
	/* and rotation */
	class cPlayerController : public cComponent
	{
	private:

		std::shared_ptr<cInputHandler> m_Input;

		float m_MovementSpeed, m_RotationSpeed;
		glm::vec3 m_Move;

	public:

		void onInit(float _moveSpeed, bool _mouseControl); //initialise the movement speed and whether the mouse is bound to the window
		void onUpdate(); //Updates the player's movement each frame

		void Move(); //Moves the player
		void Rotate(); //Rotates the player

	};
}

#endif