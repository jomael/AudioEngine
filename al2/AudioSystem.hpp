#ifndef AUDIOSYSTEM_HPP
#define AUDIOSYSTEM_HPP

#include <memory>

#include "OpenALBackend.hpp"

namespace audio
{
namespace newapi
{

class AudioSystem
{
public:
    AudioSystem();
    virtual ~AudioSystem();

    void TestAudio(const std::string &path);
    void TestPlayAudio();

    ALuint getFormatNumChannels(ALuint channels);

private:

    audio::newapi::OpenALBackend *alBackend;

    ////////////////////////////////////////////
    /// Number of channels in ogg file.
    int m_channels;

    /// Sample frequency ogg file. Usually 44100hz.
    unsigned int m_sampleRate;

    /// Total time ogg file in ms.
    float m_duration;

    /// Return code from stb_vorbis.
    int m_error;


    /////////////////////////////////////////////
    // Buffer , Source

    ALuint m_buffer;
    ALuint m_source;
};

} // namespace audio::al
} // namespace al

#endif
