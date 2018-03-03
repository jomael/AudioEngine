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
    if(!path.empty())
    {
        std::shared_ptr<AudioEmitter> emitter = std::make_shared<AudioEmitter>();
        emitter->create(path);
        m_emitters.emplace(name, emitter);
    }
    else
    {
        LOG("Path for audio file is empty!");
    }
}

std::shared_ptr<AudioEmitter> AudioSystem::getEmitter(const std::string &name)
{
    auto source = m_emitters.find(name);
    if(source != m_emitters.end())
    {
        return source->second;
    }

    Throw(InvalidArgument,
          strprintf("Cannot for audio emitters according to key (name) '%s'", name.c_str()));
}

} // namespace audio::al
} // namespace al
