#ifndef ALOGGSAMPLE_H
#define ALOGGSAMPLE_H

#include "ALBuffer.hpp"
#include "ALSoundBase.hpp"
#include "ALUtil.hpp"
#include "utils/Log.hpp"

namespace audio
{
namespace newapi
{

/// Class represent load ogg files and decode ogg files.
class OggSample : public AudioSampleBase, public ALBuffer
{
public:

    OggSample();
    OggSample(const std::string &path);
    virtual ~OggSample();

    float duration() const { return m_duration; }
    int numberOfChannel() const   { return m_channels;}

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
