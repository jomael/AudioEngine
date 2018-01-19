#include "AudioSystem.hpp"

namespace audio
{
namespace newapi
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
        std::shared_ptr<AudioSource> source = std::make_shared<AudioSource>();
        source->loadFromFile(path);
        m_sources.insert(std::pair<std::string, std::shared_ptr<AudioSource>>(name, source));
    }
    else
    {
        LOG("Path for audio file is empty!");
    }
}

std::shared_ptr<AudioSource> AudioSystem::getEmitter(const std::string &name)
{
    //std::shared_ptr<AudioSource> s;
    //std::shared_ptr<AudioEmitter> emitter = std::make_shared<AudioEmitter>();
    auto source = m_sources.find(name);
    if(source != m_sources.end())
    {
         return source->second;
    }

    //s->play();
    //Throw(InvalidArgument,
    //    strprintf("Cannot for audio source according to key (name) '%s'", name.c_str()));
}

} // namespace audio::al
} // namespace al
