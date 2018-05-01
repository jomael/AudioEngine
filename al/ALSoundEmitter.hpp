#ifndef AL_SOUND_EMITTER_HPP
#define AL_SOUND_EMITTER_HPP

#include "ALSoundBase.hpp"
#include "ALSource.hpp"

namespace audio
{
namespace al
{

class AudioEmitter : public ALSource, public AudioEmitterBase
{
public:

    AudioEmitter(const std::string &path);
    virtual ~AudioEmitter();

    //void setSettings(AudioSystemSettings &settings);
    void setPosition(const glm::vec3 &position);
    void setPosition(const float &x, const float &y, const float &z);
    void setVelocity(const glm::vec3 &velocity);
    void setVelocity(const float &x, const float &y, const float &z);
    void setDirection(const glm::vec3 &direction);
    void setDirection(const float &x, const float &y, const float &z);

    void setVolume(float &volume);
    void setGain(const float &gain);
    void setLoop(const bool loop);
    void setPitch(const float pitch);

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

    /// Play sound from emmitter
    void play();

    /// Stop sound from emitter
    void stop();

    /// Pause sound from emitter
    void pause();

    /// Return state sound in emitter (played, stopped, paused).
    ALuint getState();

private:

    glm::vec3 m_position;
    glm::vec3 m_velocity;
    glm::vec3 m_direction;

    bool m_loop;
    bool m_isRelative;
    bool m_relative;

    float m_volume;
    float m_gain;
    float m_minGain;
    float m_maxGain;
    float m_minDistance;
    float m_maxDistance;
    float m_pitch;

    ALuint m_idBuffer;
    ALuint m_idSource;
};

} // namespace audio::al
} // namespace al

#endif
