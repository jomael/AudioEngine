#include "ALSource.hpp"

namespace audio
{
namespace newapi
{

AudioSource::AudioSource() : m_source(0)
{
    alGenSources(1, &m_source);
    LOG("Generated source");
}

AudioSource::~AudioSource()
{
    alDeleteSources(1, &m_source);
    LOG("Deleted source");
}

void AudioSource::create(const std::string &path)
{
    m_sample = createSample(path);
}
/*
void AudioSource::setDistanceModel(ALenum model)
{
    switch(model)
    {
    case AL_NONE:
        alDistanceModel(AL_NONE);
        break;
    case AL_EXPONENT_DISTANCE:
        alDistanceModel(AL_EXPONENT_DISTANCE);
        break;
    case AL_EXPONENT_DISTANCE_CLAMPED:
        alDistanceModel(AL_EXPONENT_DISTANCE_CLAMPED);
        break;
    case AL_INVERSE_DISTANCE:
        alDistanceModel(AL_INVERSE_DISTANCE);
        break;
    case AL_INVERSE_DISTANCE_CLAMPED:
        alDistanceModel(AL_INVERSE_DISTANCE_CLAMPED);
        break;
    case AL_LINEAR_DISTANCE:
        alDistanceModel(AL_LINEAR_DISTANCE);
        break;
    case AL_LINEAR_DISTANCE_CLAMPED:
        alDistanceModel(AL_LINEAR_DISTANCE_CLAMPED);
        break;
    default:
        LOG("Warning: Unknown distance model!");
    }
}

void AudioSource::setPitch(float pitch)
{
    m_pitch = pitch;
    alSourcef(m_source, AL_PITCH, m_pitch);
}
*/
ALuint AudioSource::getSource()
{
    return m_source;
}

ALuint AudioSource::getSampleBuffer()
{
    return m_sample->getBuffer();
}

} // namespace audio::al
} // namespace al
