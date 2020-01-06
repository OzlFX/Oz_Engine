#include "Sound.h"
#include "stb_vorbis.h"

namespace Oz
{
	std::shared_ptr<cSound> cSound::Create()
	{
		std::shared_ptr<cSound> sound = std::make_shared<cSound>();
		sound->m_Self = sound;

		return sound;
	}

	void cSound::Load(std::string _path)
	{
		m_BufferID = 0;
		alGenBuffers(1, &m_BufferID);

		ALenum format = 0;
		ALsizei freq = 0;
		std::vector<char> bufferData;
		Load(_path, bufferData, format, freq);

		alBufferData(m_BufferID, format, &bufferData.at(0), static_cast<ALsizei>(bufferData.size()), freq);
	}

	void cSound::Load(const std::string & _fileName, std::vector<char>& _buffer, ALenum & _format, ALsizei & _freq)
	{
		int channels = 0;
		int sampleRate = 0;
		short* output = NULL;

		size_t samples = stb_vorbis_decode_filename(
			_fileName.c_str(), &channels, &sampleRate, &output);

		if (samples == -1)
		{
			throw std::exception();
		}

		// Record the sample rate required by OpenAL
		_freq = sampleRate;

		// Record the format required by OpenAL
		if (channels == 1)
		{
			_format = AL_FORMAT_MONO16;
		}
		else
		{
			_format = AL_FORMAT_STEREO16;

			// Force format to be mono (Useful for positional audio)
			// format = AL_FORMAT_MONO16;
			// freq *= 2;
		}

		// Allocate enough space based on short (two chars) multipled by the number of
		// channels and length of clip
		_buffer.resize(sizeof(*output) * channels * samples);
		memcpy(&_buffer.at(0), output, _buffer.size());

		// Clean up the read data
		free(output);
	}

	ALuint cSound::getID()
	{
		return m_BufferID;
	}

	cSound::~cSound()
	{

	}
}