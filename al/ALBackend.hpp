#ifndef OPENAL_BACKEND_HPP
#define OPENAL_BACKEND_HPP

#include <iostream>
#include <glm/glm.hpp>

#include <AL/al.h>
#include <AL/alc.h>
#include <AL/alext.h>

#include "util/Log.hpp"
#include "util/Singleton.hpp"

namespace audio
{
namespace al
{

/// OpenAL audio backend. Class initialize
/// openal device and create context.
class OpenALBackend : public Singleton<OpenALBackend>
{
public:

    explicit OpenALBackend();
    virtual ~OpenALBackend();

    /// Return true if device was initialize.
    bool isInitialized();

private:

    /// Pointer to ALCdevice structure. NULL is failure.
    ALCdevice *m_device;

    /// Pointer to ALCcontext structure. NULL is failure.
    ALCcontext *m_context;

    /// This flag is for control initialize openal device and context.
    bool m_isInitialized;
};

} // namespace audio::al
} // namespace al

#endif
