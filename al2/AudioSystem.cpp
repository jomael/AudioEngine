#include "AudioSystem.hpp"

#define STB_VORBIS_HEADER_ONLY
// Stb vorbis implementation
#include "stb_vorbis.h"

namespace audio
{
namespace newapi
{

AudioSystem::AudioSystem()
{
    LOG("Constructor");
    alBackend = new audio::newapi::OpenALBackend();

    alGenBuffers(1, &m_buffer);
    alGenSources(1, &m_source);
}

AudioSystem::~AudioSystem()
{
    LOG("Destructor");

    alDeleteBuffers(1, &m_buffer);
    alDeleteSources(1, &m_source);

    delete  alBackend;
}

ALuint AudioSystem::getFormatNumChannels(ALuint channels)
{
    ALuint format = 0;
    switch(channels) {
    case 1: format = AL_FORMAT_MONO16; break;
    case 2: format = AL_FORMAT_STEREO16; break;
    case 4: format = AL_FORMAT_QUAD16; break;
    case 6: format = AL_FORMAT_51CHN16; break;
    case 7: format = AL_FORMAT_61CHN16; break;
    case 8: format = AL_FORMAT_71CHN16; break;
    default : format = 0; break;
    }

    if(format == -1) {
        format = 0;
    }

    return format;
}

void AudioSystem::TestAudio(const std::string &path)
{
    // Size of kilobyte for convert.
    const float SIZE_KB = 1024.0;

    stb_vorbis *vorbis = stb_vorbis_open_filename(path.c_str(), &m_error, nullptr);

    if(!vorbis)
    {
        LOG("Bad initialize stb_vorbis!");
    }

    // Information about format ogg sound.
    stb_vorbis_info info = stb_vorbis_get_info(vorbis);
    m_sampleRate = info.sample_rate;
    m_duration = stb_vorbis_stream_length_in_seconds(vorbis);
    stb_vorbis_close(vorbis);

    short *data = NULL;
    int samples, sample_rate;
    samples = stb_vorbis_decode_filename(path.c_str(), &m_channels, &sample_rate, &data);

    ALuint format = getFormatNumChannels(m_channels);

    std::clog << "---Ogg Audio info--- "    << "\n"
              << "Sampling rate : " << sample_rate / 1000.0 << " kHz " << "\n"
              << "Channel       : " << m_channels << " Channel(s) " << "\n"
                 // << "Size stream   : " << m_streamSize / (SIZE_KB * SIZE_KB) << " MB" << "\n"
              << "Duration      : " << m_duration << " ms " << "\n\n";

    alBufferData(m_buffer, format, data, sizeof(short) * samples * m_channels, m_sampleRate);
}

void AudioSystem::TestPlayAudio()
{
    alSourcei(m_source, AL_BUFFER, m_buffer);
    int status = alGetError();
    if (status != AL_NO_ERROR)
    {
        LOG("OpenAL error");
    }

    alSourcePlay(m_source);
    int status2 = alGetError();
    if (status2 != AL_NO_ERROR)
    {
        LOG("OpenAL error play");
    }
}

} // namespace audio::al
} // namespace al
