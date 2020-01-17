#ifndef _CSOUNDSYSTEM_H_
#define _CSOUNDSYSTEM_H_

//Includes
#include "Components.h"

#include <memory>
#include <vector>
#include <AL/al.h>

namespace Oz
{
	class cSound;

	/* Plays a specified sound file in 3D space */
	class cSoundSystem : public cComponent
	{
	private:

		ALuint m_SourceID;
		std::shared_ptr<cSound> m_Sound;
		bool m_PlayState;

	public:

		void onInit(std::shared_ptr<cSound> _sound); //Set the sound file
		void Play(); //Play the sound
		void onUpdate(); //Check if the system should play the sound and run play
		void setPlayState(bool _playState) { m_PlayState = _playState; }

	};
}

#endif