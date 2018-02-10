#ifndef ALSOURCE_HPP
#define ALSOURCE_HPP

#include <glm/glm.hpp>
#include <AL/al.h>
#include <AL/alc.h>
#include <memory>
#include "ALUtil.hpp"
#include "utils/Log.hpp"

namespace audio
{
namespace newapi
{

class AudioSource
{
public:

    AudioSource();
    virtual ~AudioSource();

    /// Load from file sound
    void create(const std::string &path);

    /// Distance model for environment
    /// Default value is AL_INVERSE_DISTANCE
    //void setDistanceModel(ALenum model);

    /// Pitch multiplier
    //void setPitch(float pitch);

    /// Return id source
    ALuint getSource();

    /// Return sample id from source generator
    ALuint getSampleBuffer();

private:

    /// Minimum distance source
    //float m_min_distance;

    /// Maximum distance source
    //float m_max_distance;

    /// Pitch source
    //float m_pitch;

    /// Id source
    ALuint m_source;

    /// Decoded sample for next processing
    std::unique_ptr<AudioSampleBase> m_sample;
};

} // namespace audio::al
} // namespace al

#endif
