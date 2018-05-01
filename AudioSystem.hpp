#ifndef AUDIO_SYSTEM_HPP
#define AUDIO_SYSTEM_HPP

#include <memory>
#include <map>
#include <iostream>

#include "al/ALBackend.hpp"
#include "al/ALSoundEmitter.hpp"
#include "al/ALListener.hpp"

namespace audio
{
namespace al
{

class AudioSystem : public OpenALBackend
{
public:

    explicit AudioSystem();
    virtual ~AudioSystem();

    void loadFromFile(const std::string &name,
                      const std::string &path);

public:

    std::shared_ptr<audio::al::AudioEmitter> getEmitter(const std::string &name);

protected:

    std::map<std::string, std::shared_ptr<AudioEmitter>> m_emitters;
};

} // namespace audio::al
} // namespace al

#endif
