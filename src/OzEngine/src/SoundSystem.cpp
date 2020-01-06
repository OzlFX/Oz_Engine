#include "Components/ComponentIncludes.h"
#include "SoundSystem.h"
#include "Sound.h"

namespace Oz
{
	void cSoundSystem::Play()
	{
		alSource3f(m_SourceID, AL_POSITION, 0.0f, 0.0f, 0.0f);
		alSourcei(m_SourceID, AL_BUFFER, m_Sound->getID());
		alSourcePlay(m_SourceID);
	}

	void cSoundSystem::onUpdate()
	{
		ALint state = 0;
		alGetSourcei(m_SourceID, AL_SOURCE_STATE, &state);

		if (state == AL_STOPPED)
		{
			//break;
		}

		//Sleep(1000);
	}

	void cSoundSystem::setSound(std::shared_ptr<cSound> _sound)
	{
		m_Sound = _sound;
	}
}