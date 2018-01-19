#include "ALBuffer.hpp"

namespace audio
{
namespace newapi
{

ALBuffer::ALBuffer()
{
    alGenBuffers(1, &m_buffer);
    LOG("Generated buffer");
}

ALBuffer::~ALBuffer()
{
    alDeleteBuffers(1, &m_buffer);
    LOG("Deleted buffer");
}

ALuint ALBuffer::getBuffer()
{
    return m_buffer;
}

} // namespace audio::al
} // namespace al
