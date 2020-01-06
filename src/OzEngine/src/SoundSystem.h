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

	class cSoundSystem : public cComponent
	{
	private:

		ALuint m_SourceID;
		std::shared_ptr<cSound> m_Sound;

	public:

		void Play();
		void onUpdate();
		void setSound(std::shared_ptr<cSound> _sound);

	};
}

#endif