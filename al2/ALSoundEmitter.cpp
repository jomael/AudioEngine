#include "ALSoundEmitter.hpp"

namespace audio
{
namespace newapi
{

AudioEmitter::AudioEmitter()
{
    LOG("Constructor");
}

AudioEmitter::~AudioEmitter()
{
    LOG("Destructor");
}

void AudioEmitter::create(const std::string &path)
{
    m_source = std::make_unique<AudioSource>();
    m_properties = std::make_unique<AudioPropertiesBase>();
    m_source->loadFromFile(path);
    m_properties->idBuffer = m_source->getSampleBuffer();
    m_properties->idSource = m_source->getSource();


    alSourcei(m_properties->idSource,
              AL_BUFFER, m_properties->idBuffer);

    int status = alGetError();
    if (status != AL_NO_ERROR)
    {
       LOG("OpenAL error");
    }
}

void AudioEmitter::setPosition(const glm::vec3 &position)
{
    m_position = position;
    alSource3f(m_properties->idSource, AL_POSITION,
               m_position.x, m_position.y, m_position.z);
}

void AudioEmitter::setPosition(const float &x, const float &y, const float &z)
{
    m_position = glm::vec3(x, y, z);
    alSource3f(m_properties->idSource, AL_POSITION,
               m_position.x, m_position.y, m_position.z);
}

void AudioEmitter::play()
{
    alSourcePlay(m_properties->idSource);
    int status = alGetError();
    if (status != AL_NO_ERROR)
    {
        LOG("OpenAL error play");
    }
}

void AudioEmitter::stop()
{
    alSourceStop(m_properties->idSource);
    int status = alGetError();
    if (status != AL_NO_ERROR)
    {
        LOG("OpenAL error stop");
    }
}

void AudioEmitter::pause()
{
    alSourcePause(m_properties->idSource);
    int status = alGetError();
    if (status != AL_NO_ERROR)
    {
        LOG("OpenAL error pause");
    }
}

} // namespace audio::al
} // namespace al
