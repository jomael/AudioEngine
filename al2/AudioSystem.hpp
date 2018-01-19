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

class AudioSystem : public OpenALBackend
{
public:
    AudioSystem();
    virtual ~AudioSystem();

    void loadFromFile(const std::string &name,
                      const std::string &path);

public:
    //std::unique_ptr<AudioEmitter> createEmitter();
    std::shared_ptr<audio::newapi::AudioSource> getEmitter(const std::string &name);
private:
    std::vector<std::shared_ptr<AudioEmitter>> m_emitters;
    std::unordered_map<std::string, std::shared_ptr<AudioSource>> m_sources;
};

} // namespace audio::al
} // namespace al

#endif
