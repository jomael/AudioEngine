#include "ALBackend.hpp"

namespace audio
{
namespace al
{

OpenALBackend::OpenALBackend() : m_isInitialized(false)
{
    if(!m_isInitialized)
    {
        m_device = alcOpenDevice(nullptr);
        if (!m_device)
        {
            LOG("Cannot open a device");
            m_isInitialized = false;
        }
        else
        {
            LOG("OpenAL device   : " + std::string(alcGetString(m_device, ALC_DEVICE_SPECIFIER)));

        }

        m_context = alcCreateContext(m_device, nullptr);
        if(m_context == nullptr || alcMakeContextCurrent(m_context) == ALC_FALSE)
        {
            if(m_context != nullptr)
            {
                alcDestroyContext(m_context);
            }

            alcCloseDevice(m_device);
            LOG("Cannot set an context! Closing device ...");
            m_isInitialized = false;
        }
        else
        {

            LOG("OpenAL version   : " + std::string(alGetString(AL_VERSION)));
            LOG("OpenAL renderer  : " + std::string(alGetString(AL_RENDERER)));
            LOG("OpenAL vendor    : " + std::string(alGetString(AL_VENDOR)));
            LOG("OpenAL extension : " + std::string(alGetString(AL_EXTENSIONS)));
            LOG("OpenAL init done");
        }
        m_isInitialized = true;
    }
}

OpenALBackend::~OpenALBackend()
{
    if(m_context)
    {
        alcMakeContextCurrent(nullptr);
        alcDestroyContext(m_context);
        m_context = nullptr;
        LOG("Destroy openal context");
    }

    if(m_device)
    {
        alcCloseDevice(m_device);
        m_device = nullptr;
        LOG("Closed openal device");
    }
}

bool OpenALBackend::isInitialized()
{
    return m_isInitialized;
}

} // namespace audio::al
} // namespace al
