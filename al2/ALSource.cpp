#include "ALSource.hpp"

namespace audio
{
namespace newapi
{

ALSource::ALSource() : m_source(0)
{
    alGenSources(1, &m_source);
    LOG("Generated source");
}

ALSource::~ALSource()
{
    alDeleteSources(1, &m_source);
    LOG("Deleted source");
}

void ALSource::createSource(const std::string &path)
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

*/
ALuint ALSource::getSource()
{
    return m_source;
}

ALuint ALSource::getSampleBuffer()
{
    return m_sample->getBuffer();
}

} // namespace audio::al
} // namespace al
