#include "ALSource.hpp"

namespace audio
{
namespace newapi
{

AudioSource::AudioSource() :
    m_position(0.0f, 0.0f, 0.0f),
    m_velocity(0.0f, 0.0f, 0.0f),
    m_direction(0.0f, 0.0f, 0.0f),
    m_loop(false),
    m_gain(0.0f),
    m_min_gain(0.0f),
    m_max_gain(1.0f),
    m_min_distance(0.0f),
    m_max_distance(0.3f),
    m_source(0)
{
    alGenSources(1, &m_source);
    LOG("Generated source");
}

AudioSource::~AudioSource()
{
    alDeleteSources(1, &m_source);
    LOG("Deleted source");
}

void AudioSource::loadFromFile(const std::string &path)
{
    m_sample = createSample(path);
}


void AudioSource::setVelocity(const glm::vec3 &velocity)
{
    m_velocity = velocity;
    alSource3f(m_source, AL_VELOCITY, m_velocity.x, m_velocity.y, m_velocity.z);
}

void AudioSource::setVelocity(const float &x, const float &y, const float &z)
{
    m_velocity = glm::vec3(x, y, z);
    alSource3f(m_source, AL_VELOCITY, m_velocity.x, m_velocity.y, m_velocity.z);
}

void AudioSource::setDirection(const glm::vec3 &direction)
{
    m_direction = direction;
    alSource3f(m_source, AL_DIRECTION, m_direction.x, m_direction.y, m_direction.z);
}

void AudioSource::setDirection(const float &x, const float &y, const float &z)
{
    m_direction = glm::vec3(x, y, z);
    alSource3f(m_source, AL_DIRECTION, m_direction.x, m_direction.y, m_direction.z);
}

void AudioSource::enableLoop(bool loop)
{
    m_loop = loop;
    alSourcei(m_source, AL_LOOPING, loop);
}

void AudioSource::setGain(float gain)
{
    if(gain < AL_NONE)
    {
        LOG("Warning: The gain must be set greater than 0 ");
        return;
    }

    m_gain = gain;

    alSourcef(m_source, AL_GAIN, m_gain);
}

void AudioSource::setMinMaxGain(float min, float max)
{
    if(m_min_gain < AL_NONE || m_max_gain > 1.0f) {
        return;
    }

    m_min_gain = min;
    m_max_gain = max;

    alSourcef(m_source, AL_MIN_GAIN, min);
    alSourcef(m_source, AL_MAX_GAIN, max);
}

void AudioSource::setMinMaxDistance(const float &min, const float &max)
{
    m_min_distance = min;
    m_max_distance = max;

    alSourcef(m_source, AL_REFERENCE_DISTANCE, m_min_distance);
    alSourcef(m_source, AL_REFERENCE_DISTANCE, m_max_distance);
}

void AudioSource::enableRelativeListener(bool relative)
{
    alSourcei(m_source, AL_SOURCE_RELATIVE, relative);
}

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

void AudioSource::setSpeedOfSound(float speed)
{
    alSpeedOfSound(speed);
}

void AudioSource::setDopplerFactor(float strength)
{
    alSourcef(m_source, AL_DOPPLER_FACTOR, strength);
}

void AudioSource::setPitch(float pitch)
{
    m_pitch = pitch;
    alSourcef(m_source, AL_PITCH, m_pitch);
}

ALuint AudioSource::getSource()
{
    return m_source;
}

ALuint AudioSource::getSourceState()
{
    ALint source_state;
    alGetSourceiv(m_source, AL_SOURCE_STATE, &source_state);

    switch(source_state)
    {
        case(AL_INITIAL):
          return AL_INITIAL;
        case(AL_PLAYING):
          return AL_PLAYING;
        case(AL_PAUSED):
          return AL_PAUSED;
        case(AL_STOPPED):
          return AL_STOPPED;
        default:
            LOG("Warning: Unknown source state!");
    }
}

//void AudioSource::generateSource()
//{
//    alGenSources(1, &m_source);
//}

ALuint AudioSource::getSampleBuffer()
{
    return m_sample->getBuffer();
}

} // namespace audio::al
} // namespace al
