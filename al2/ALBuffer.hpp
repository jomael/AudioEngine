#ifndef ALBUFFER_HPP
#define ALBUFFER_HPP

#include "ALBackend.hpp"

namespace audio
{
namespace newapi
{

/// Class initialize OpenAL device only one and
/// generate for every sound buffer id.
class ALBuffer
{
public:

    ALBuffer();
    virtual ~ALBuffer();

    // Gets actual buffer id.
    ALuint getBuffer() const;

public:

    /// Buffer id
    ALuint m_buffer;
};

} // namespace audio::al
} // namespace al

#endif
