#include "Components/ComponentIncludes.h"
#include "SoundSystem.h"
#include "Sound.h"
#include "Camera.h"

namespace Oz
{
	void cSoundSystem::Play()
	{
		alListener3f(AL_POSITION, 
			getCore()->getMainCamera()->getTransform()->getPos().x, 
			getCore()->getMainCamera()->getTransform()->getPos().y, 
			getCore()->getMainCamera()->getTransform()->getPos().z);

		alSource3f(m_SourceID, AL_POSITION, 
			getGameObject()->getTransform()->getPos().x, 
			getGameObject()->getTransform()->getPos().y, 
			getGameObject()->getTransform()->getPos().z);

		try
		{
			if (!m_Sound)
			{
				throw Oz::Exception("Sound cannot be played, no sound source exists!");
			}
		}
		catch (Oz::Exception& excp)
		{
			std::cout << "Oz Engine Error: " << excp.what() << std::endl;
			return;
		}

		alSourcei(m_SourceID, AL_BUFFER, m_Sound->getID());
		alSourcePlay(m_SourceID);
	}

	void cSoundSystem::onUpdate()
	{
		if (m_PlayState)
		{
			Play();
			m_PlayState = false;
		}
	}

	void cSoundSystem::onInit(std::shared_ptr<cSound> _sound)
	{
		m_Sound = _sound;
	}
}