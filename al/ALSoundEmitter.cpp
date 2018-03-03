#include "ALSoundEmitter.hpp"

namespace audio
{
namespace al
{

AudioEmitter::AudioEmitter():
    m_position(0.0f, 0.0f, 0.0f),
    m_velocity(0.0f, 0.0f, 0.0f),
    m_direction(0.0f, 0.0f, 0.0f),
    m_minGain(0.0f),
    m_maxGain(0.3f),
    m_minDistance(0.0f),
    m_maxDistance(0.3f),
    m_idBuffer(0),
    m_idSource(0)
{
    LOG("Constructor");
}

AudioEmitter::~AudioEmitter()
{
    LOG("Destructor");
}

void AudioEmitter::create(const std::string &path)
{
    createSource(path);
    m_idBuffer = getSampleBuffer();
    m_idSource = getSource();

    alSourcei(m_idSource,
              AL_BUFFER, static_cast<ALint>(m_idBuffer));

    if(AL_NO_ERROR != alGetError())
    {
        LOG("OpenAL error");
    }
}

void AudioEmitter::setPosition(const glm::vec3 &position)
{
    m_position = position;
    alSource3f(m_idSource, AL_POSITION,
               m_position.x, m_position.y, m_position.z);
}

void AudioEmitter::setPosition(const float &x, const float &y, const float &z)
{
    m_position = glm::vec3(x, y, z);
    alSource3f(m_idSource, AL_POSITION,
               m_position.x, m_position.y, m_position.z);
}

void AudioEmitter::setVelocity(const glm::vec3 &velocity)
{
    m_velocity = velocity;
    alSource3f(m_idSource, AL_VELOCITY,
               m_velocity.x, m_velocity.y, m_velocity.z);
}

void AudioEmitter::setVelocity(const float &x, const float &y, const float &z)
{
    m_velocity = glm::vec3(x, y, z);
    alSource3f(m_idSource, AL_VELOCITY,
               m_velocity.x, m_velocity.y, m_velocity.z);
}

void AudioEmitter::setDirection(const glm::vec3 &direction)
{
    m_direction = direction;
    alSource3f(m_idSource, AL_DIRECTION,
               m_direction.x, m_direction.y, m_direction.z);
}

void AudioEmitter::setDirection(const float &x, const float &y, const float &z)
{
    m_direction = glm::vec3(x, y, z);
    alSource3f(m_idSource, AL_DIRECTION,
               m_direction.x, m_direction.y, m_direction.z);
}

void AudioEmitter::setVolume(float &volume)
{
    m_volume = volume;
}

void AudioEmitter::setGain(const float &gain)
{
    if(gain < 0.0f)
    {
        LOG("Warning: The gain must be set greater than 0 ");
        return;
    }

    m_gain = gain;

    alSourcef(m_idSource, AL_GAIN, m_gain);
}

void AudioEmitter::setLoop(bool loop)
{
    m_loop = loop;
    alSourcei(m_idSource, AL_LOOPING, loop);
}

void AudioEmitter::setPitch(const float pitch)
{
    m_pitch = pitch;
    alSourcef(m_idSource, AL_PITCH, m_pitch);
}

void AudioEmitter::setMinMaxDistance(const float &min, const float &max)
{
    m_minDistance = min;
    m_maxDistance = max;

    alSourcef(m_idSource, AL_REFERENCE_DISTANCE, m_minDistance);
    alSourcef(m_idSource, AL_REFERENCE_DISTANCE, m_maxDistance);
}

void AudioEmitter::setMinMaxGain(const float &min, const float &max)
{
    if(min < 0.0f && max > 1.0f)
    {
        LOG("Warning: The gain must be range: [0.0 - 1.0]");
        return;
    }

    m_minGain = min;
    m_maxGain = max;

    alSourcef(m_idSource, AL_MIN_GAIN, min);
    alSourcef(m_idSource, AL_MAX_GAIN, max);
}

void AudioEmitter::setDopplerFactor(const float &strength)
{
    alSourcef(m_idSource, AL_DOPPLER_FACTOR, strength);
}

void AudioEmitter::setSpeedOfSound(const float &speed)
{
    alSpeedOfSound(speed);
}

void AudioEmitter::enableRelativeListener(bool relative)
{
    alSourcei(m_idSource, AL_SOURCE_RELATIVE, relative);
}

void AudioEmitter::play()
{
    alSourcePlay(m_idSource);
    if(AL_NO_ERROR != alGetError())
    {
        LOG("OpenAL error");
    }
}

void AudioEmitter::stop()
{
    alSourceStop(m_idSource);
    if(AL_NO_ERROR != alGetError())
    {
        LOG("OpenAL error");
    }
}

void AudioEmitter::pause()
{
    alSourcePause(m_idSource);
    if(AL_NO_ERROR != alGetError())
    {
        LOG("OpenAL error");
    }
}

ALuint AudioEmitter::getState()
{
    ALint source_state;
    ALuint state = 0;
    alGetSourceiv(m_idSource,
                  AL_SOURCE_STATE, &source_state);

    switch(source_state)
    {
    case(AL_INITIAL):
        state = AL_INITIAL;
        break;
    case(AL_PLAYING):
        state = AL_PLAYING;
        break;
    case(AL_PAUSED):
        state = AL_PAUSED;
        break;
    case(AL_STOPPED):
        state = AL_STOPPED;
        break;
    default:
        LOG("Warning: Unknown source state!");
    }

    return state;
}

} // namespace audio::al
} // namespace al
