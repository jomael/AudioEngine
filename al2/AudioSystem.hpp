#ifndef AUDIOSYSTEM_HPP
#define AUDIOSYSTEM_HPP

#include <memory>
#include <vector>
#include <unordered_map>
#include <iostream>

#include "ALBackend.hpp"
#include "ALSource.hpp"
#include "ALSoundEmitter.hpp"

namespace audio
{
namespace newapi
{

/// Collects various settings of the audio system.
class AudioSystemSettings
{
public:

    /// Default value for every sound.
    float master_gain = 1.0f;

    /// Default listener gain.
    float default_listener_gain = 1.0f;

    /// Doppler factor is a simple scaling of source and listener velocities
    /// to exaggerate or deemphasize the Doppler (pitch).
    float doppler_factor = 1.0f;

    /// Default value for speed of sound for every sound.
    float speed_of_sound = 343.3f;
};

class AudioSystem : public OpenALBackend
{
public:
    AudioSystem();
    virtual ~AudioSystem();

    void loadFromFile(const std::string &name,
                      const std::string &path);

public:
    std::shared_ptr<audio::newapi::AudioEmitter> getEmitter(const std::string &name);

private:
    std::unordered_map<std::string, std::shared_ptr<AudioEmitter>> m_emitters;
};

} // namespace audio::al
} // namespace al

#endif
