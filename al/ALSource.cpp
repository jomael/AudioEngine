#include "ALSource.hpp"

namespace audio
{
namespace al
{

ALSource::ALSource() : m_source(0)
{
    alGenSources(1, &m_source);
    LOG("Generated source");
}

ALSource::~ALSource()
{
    alDeleteSources(1, &m_source);
    LOG("Deleted source");
}

void ALSource::createSource(const std::string &path)
{
    m_sample = createSample(path);
}

ALuint ALSource::getSource()
{
    return m_source;
}

ALuint ALSource::getSampleBuffer()
{
    return m_sample->getBuffer();
}

} // namespace audio::al
} // namespace al
