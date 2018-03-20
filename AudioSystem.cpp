#include "AudioSystem.hpp"

namespace audio
{
namespace al
{

AudioSystem::AudioSystem()
{
    LOG("Constructor");
}

AudioSystem::~AudioSystem()
{
    LOG("Destructor");
}

void AudioSystem::loadFromFile(const std::string &name, const std::string &path)
{
    if(path.empty())
    {
        Throw(InvalidArgument,
              strprintf("File path is empty! '%s'", name.c_str()));
    }

    std::shared_ptr<AudioEmitter> emitter = std::make_shared<AudioEmitter>(path);
    m_emitters.emplace(name, emitter);
}

std::shared_ptr<AudioEmitter> AudioSystem::getEmitter(const std::string &name)
{
    if(m_emitters.count(name) > 0)
    {
        auto s = m_emitters.find(name);
        return s->second;
    }

    Throw(InvalidArgument,
          strprintf("Cannot for audio emitters according to key (name) '%s'", name.c_str()));
}

} // namespace audio::al
} // namespace al
