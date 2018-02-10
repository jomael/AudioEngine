#ifndef ALSOUNDEMITTER_HPP
#define ALSOUNDEMITTER_HPP

#include <map>
#include "ALSoundBase.hpp"
#include "ALSource.hpp"

namespace audio
{
namespace newapi
{

class AudioEmitter : public AudioEmitterBase
{
public:

    AudioEmitter();
    virtual ~AudioEmitter();

    /// Create source emitter from audio file
    void create(const std::string &path);

    void setPosition(const glm::vec3 &position);
    void setPosition(const float &x, const float &y, const float &z);
    void setVelocity(const glm::vec3 &velocity);
    void setVelocity(const float &x, const float &y, const float &z);
    void setDirection(const glm::vec3 &direction);
    void setDirection(const float &x, const float &y, const float &z);

    void setVolume(float &volume);
    void setGain(const float &gain);
    void setLoop(const bool loop);

    /// The distance under which the volume for the source
    /// would normally drop by half
    void setMinMaxDistance(const float &min, const float &max);

    /// Set minimum and maximum gain source
    void setMinMaxGain(const float &min, const float &max);

    /// The Doppler effect depends on the velocities of
    /// source and listener relative to the medium, and
    /// the propagation speed of sound in that medium.
    /// Default value is 1.0
    void setDopplerFactor(const float &strength);

    /// The default value is 343.3 (appropriate
    /// for velocity units of meters and air as the
    /// propagation medium)
    void setSpeedOfSound(const float &speed);

    /// Determines if the positions are relative to
    /// the listener default is false
    void enableRelativeListener(bool relative);

    void play();
    void stop();
    void pause();

    /// Return state emitter (played, stopped, paused).
    ALuint getState();

    void setPriority(float &volume) { m_volume = volume; }
    bool is2DSound() { return m_is2DSound;}
    bool is3DSound() { return m_is3DSound;}

private:

    glm::vec3 m_position;
    glm::vec3 m_velocity;
    glm::vec3 m_direction;

    bool m_loop;
    bool m_isRelative;
    bool m_is2DSound;
    bool m_is3DSound;
    bool m_relative;

    float m_volume;
    float m_gain;
    float m_minGain;
    float m_maxGain;
    float m_minDistance;
    float m_maxDistance;

    std::unique_ptr<AudioSource> m_source;
    std::unique_ptr<AudioPropertiesBase> m_properties;
};

} // namespace audio::al
} // namespace al

#endif
