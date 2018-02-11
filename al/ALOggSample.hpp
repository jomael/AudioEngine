#ifndef AL_OGG_SAMPLE_H
#define AL_OGG_SAMPLE_H

#include "ALBuffer.hpp"
#include "ALSoundBase.hpp"
#include "ALUtil.hpp"
#include "utils/Log.hpp"

namespace audio
{
namespace al
{

/// Class represent load ogg files and decode ogg files.
class OggSample : public ALBuffer, public AudioSampleBase
{
public:

    OggSample();
    OggSample(const std::string &path);
    virtual ~OggSample();

    float duration() const { return m_duration; }
    int numberOfChannel() const   { return m_channels;}
    ALuint getBuffer() const { return m_buffer;}
private:

    /// Number of channels in ogg file.
    int m_channels;

    /// Sample frequency ogg file. Usually 44100hz.
    unsigned int m_sampleRate;

    /// Total time ogg file in ms.
    float m_duration;

    /// Return code from stb_vorbis.
    int m_error;

};

} // namespace audio::al
} // namespace al

#endif
