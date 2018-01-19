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

void AudioSystem::loadFromFile(const std::string &path)
{
    //std::unique_ptr<AudioSampleBase> base = createSoundSample(path);
}


std::unique_ptr<AudioSampleBase> AudioSystem::createSample(const std::string &path)
{
    if(path.rfind(".wav") == path.size() - 4)
    {
        return std::make_unique<WavSample>(path);
    }
    else if(path.rfind(".ogg") == path.size() - 4)
    {
        return std::make_unique<OggSample>(path);
    }

    Throw(InvalidArgument,
        strprintf("only .wav or .ogg files are currently supported, got '%s'", path.c_str()));
}


} // namespace audio::al
} // namespace al
