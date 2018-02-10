#include "ALBuffer.hpp"

namespace audio
{
namespace newapi
{

ALBuffer::ALBuffer() : m_buffer(0)
{
    alGenBuffers(1, &m_buffer);
    LOG("Generated buffer");
}

ALBuffer::~ALBuffer()
{
    alDeleteBuffers(1, &m_buffer);
    LOG("Deleted buffer");
}

ALuint ALBuffer::getBuffer() const
{
    return m_buffer;
}

} // namespace audio::al
} // namespace al
