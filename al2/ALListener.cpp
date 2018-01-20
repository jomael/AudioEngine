#include "ALListener.hpp"

namespace audio
{
namespace newapi
{

AudioListener::AudioListener() : m_position(0.0f, 0.0f, 0.0f), m_velocity(0.0f, 0.0f, 0.0f),
    m_direction(0.f, 0.f, -1.f), m_up_vector(0.f, 1.f, 0.1f)
{
    LOG("Constructor");
}

AudioListener::~AudioListener()
{
    LOG("Destructor");
}

void AudioListener::setPosition(const glm::vec3 &position)
{
    m_position = position;
    alListener3f(AL_POSITION, m_position.x, m_position.y, m_position.z);
}

void AudioListener::setPosition(const float &x, const float &y, const float &z)
{
    m_position = glm::vec3(x, y, z);
    alListener3f(AL_POSITION, m_position.x, m_position.y, m_position.z);
}

void AudioListener::setVelocity(const glm::vec3 &velocity)
{
    m_velocity = velocity;
    alListener3f(AL_VELOCITY, m_velocity.x, m_velocity.y, m_velocity.z);
}

void AudioListener::setVelocity(const float &x, const float &y, const float &z)
{
    m_velocity = glm::vec3(x, y, z);
    alListener3f(AL_VELOCITY, m_velocity.x, m_velocity.y, m_velocity.z);
}

void AudioListener::setDirection(const glm::vec3 &direction)
{
    m_direction = direction;

    float orientation[6] = {
        m_direction.x, m_direction.y, m_direction.z,
        m_up_vector.x, m_up_vector.y, m_up_vector.z
    };

    alListenerfv(AL_ORIENTATION, orientation);
}

void AudioListener::setDirection(const float &x, const float &y, const float &z)
{
    m_direction = glm::vec3(x, y, z);

    float orientation[6] = {
        m_direction.x, m_direction.y, m_direction.z,
        m_up_vector.x, m_up_vector.y, m_up_vector.z
    };

    alListenerfv(AL_ORIENTATION, orientation);
}

void AudioListener::updateListenerPosition(const glm::vec3 &pos, const glm::vec3 &dir)
{
    m_position = pos;
    m_direction = dir;

    float orientation[6] = {
        m_direction.x, m_direction.y, m_direction.z,
        m_up_vector.x, m_up_vector.y, m_up_vector.z
    };

    alListener3f(AL_POSITION, m_position.x, m_position.y, m_position.z);
    alListenerfv(AL_ORIENTATION, orientation);
}

glm::vec3 AudioListener::getPosition()
{
    return m_position;
}

glm::vec3 AudioListener::getVelocity()
{
    return m_velocity;
}

} // namespace audio::al
} // namespace al
