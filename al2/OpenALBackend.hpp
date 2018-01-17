#ifndef OPENA_AL_BACKEND_HPP
#define OPENA_AL_BACKEND_HPP

#include <iostream>
#include <glm/glm.hpp>

#include <AL/al.h>
#include <AL/alc.h>
#include <AL/alext.h>

#include "utils/Log.hpp"
#include "utils/Singleton.hpp"

namespace audio
{
namespace newapi
{

/// OpenAL audio backend. Class initialize
/// openal device and create context.
class OpenALBackend : public Singleton<OpenALBackend>
{
public:

    OpenALBackend();
    virtual ~OpenALBackend();

    /// Return true if device was initialize.
    bool isInitialized();

private:

    /// Pointer to ALCdevice structure. NULL is failure.
    ALCdevice *m_device;

    /// Pointer to ALCcontext structure. NULL is failure.
    ALCcontext *m_context;

    /// This flag is for control initialize openal device and context.
    /// Flag inhibiting for multi initilize openal device and context.
    bool m_isInitialized;
};

} // namespace audio::al
} // namespace al

#endif
