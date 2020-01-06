#ifndef _CSOUND_H_
#define _CSOUND_H_

#include <OzEngine/src/NonCopyable.h>

#include "Resource.h"

#include <vector>
#include <AL/al.h>

namespace Oz
{
	class cSound : private cNonCopyable, public cResource
	{
		friend class cResources;

	private:

		//Vars
		ALuint m_BufferID;

		std::weak_ptr<cSound> m_Self;

		//Functions
		std::shared_ptr<cSound> Create(); //Create the texture
		void Load(std::string _path); //Load the texture
		void Load(const std::string & _fileName, std::vector<char>& _buffer, ALenum & _format, ALsizei & _freq); //Load the texture

	public:

		ALuint getID();
		
		~cSound();
	};
}

#endif