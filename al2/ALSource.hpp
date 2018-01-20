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
    void loadFromFile(const std::string &path);

    /// Set postion vector source
    //void setPosition(const glm::vec3 &position);
    //void setPosition(const float &x, const float &y, const float &z);

    /// Set velocity vector source
    void setVelocity(const glm::vec3 &velocity);
    void setVelocity(const float &x, const float &y, const float &z);

    /// Set direction vector source
    void setDirection(const glm::vec3 &direction);
    void setDirection(const float &x, const float &y, const float &z);

    /// Return state (played, stopped, paused) source.
    ALuint getSourceState();

    /// Set loop source
    void enableLoop(bool loop);

    /// Set gain source
    void setGain(float gain);

    /// Set minimum and maximum gain source
    void setMinMaxGain(float min, float max);

    /// The distance under which the volume for the source
    /// would normally drop by half
    void setMinMaxDistance(const float &min, const float &max);

    /// Determines if the positions are relative to
    /// the listener default is false
    void enableRelativeListener(bool relative);

    /// Distance model for environment
    /// Default value is AL_INVERSE_DISTANCE
    void setDistanceModel(ALenum model);

    /// The Doppler effect depends on the velocities of
    /// source and listener relative to the medium, and
    /// the propagation speed of sound in that medium.
    /// Default value is 1.0
    void setDopplerFactor(float strength);

    /// The default value is 343.3 (appropriate
    /// for velocity units of meters and air as the
    /// propagation medium)
    void setSpeedOfSound(float speed);

    /// Pitch multiplier
    void setPitch(float pitch);

    /// Return id source
    ALuint getSource();

    /// Generate source id
    //void generateSource();

    ALuint getSampleBuffer();

private:

    /// The default setting is (0, 0, 0)
    glm::vec3 m_position;

    /// The default setting is (0, 0, 0)
    glm::vec3 m_velocity;

    /// The default setting is (0, 0, 0)
    glm::vec3 m_direction;

    /// Set for looping source.
    bool m_loop;

    /// Gain source for source, should be positive set.
    float m_gain;

    /// Minimum gain source
    float m_min_gain;

    /// Maximum gain source
    float m_max_gain;

    /// Minimum distance source
    float m_min_distance;

    /// Maximum distance source
    float m_max_distance;

    /// Pitch source
    float m_pitch;

    /// Id source
    ALuint m_source;

    /// Decoded sample for next processing
    std::unique_ptr<AudioSampleBase> m_sample;
};

} // namespace audio::al
} // namespace al

#endif
