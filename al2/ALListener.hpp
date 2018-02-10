#ifndef ALLISTENER_HPP
#define ALLISTENER_HPP

#include "ALSoundBase.hpp"
#include "utils/Log.hpp"

namespace audio
{
namespace newapi
{

class AudioListenerSettings
{
public:
    const glm::vec3 defaultPosition = glm::vec3(0.0f, 0.0f, 0.0f);
    const glm::vec3 defaultVelocity = glm::vec3(0.0f, 0.0f, 0.0f);
    const glm::vec3 defaultDirection = glm::vec3(0.f, 0.f, -1.f);
    const glm::vec3 defaultUpVector = glm::vec3(0.f, 1.f, 0.1f);
};

class AudioListener
{
public:

    explicit AudioListener();
    explicit AudioListener(AudioListenerSettings &audiosettings);
    virtual ~AudioListener();

    /// Set vector position listener
    void setPosition(const glm::vec3 &position);
    void setPosition(const float &x, const float &y, const float &z);

    /// Set vector velocity listener
    void setVelocity(const glm::vec3 &velocity);
    void setVelocity(const float &x, const float &y, const float &z);

    /// Set vector direction listener
    void setDirection(const glm::vec3 &direction);
    void setDirection(const float &x, const float &y, const float &z);

    /// Get vector position listener
    glm::vec3 getPosition() const;

    /// Get vector velocity listener
    glm::vec3 getVelocity() const;

    /// Update every second position and direction listener
    void updateListener(const glm::vec3 &pos, const glm::vec3 &dir);

private:

    glm::vec3 m_position;
    glm::vec3 m_velocity;
    glm::vec3 m_direction;
    glm::vec3 m_up_vector;
    AudioListenerSettings m_audioSettings;
};

} // namespace audio::al
} // namespace al

#endif
