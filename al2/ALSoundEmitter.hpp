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

    void create(const std::string &path);

    void play();
    void stop();
    void pause();

    bool is2DSound() { }
    bool is3DSound() { }
    void setPosition(const glm::vec3 &position);
    void setPosition(const float &x, const float &y, const float &z);
    void setVolume(float &volume) { m_volume = volume; }
    void setPriority(float &volume) { }
    void setStop(bool &stop) { }
    void setLoop(bool &loop) { }

private:

    glm::vec3 m_position;
    float m_volume;
    bool m_isRelative;

    std::unique_ptr<AudioSource> m_source;
    std::unique_ptr<AudioPropertiesBase> m_properties;
};


} // namespace audio::al
} // namespace al

#endif
