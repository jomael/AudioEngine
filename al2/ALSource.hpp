#ifndef AL_SOURCE_HPP
#define AL_SOURCE_HPP

#include <glm/glm.hpp>
#include <AL/al.h>
#include <AL/alc.h>
#include <memory>
#include "ALUtil.hpp"
#include "utils/Log.hpp"

namespace audio
{
namespace al
{

class ALSource
{
public:

    ALSource();
    virtual ~ALSource();

    /// Load from file sound
    void createSource(const std::string &path);

    /// Return id source
    ALuint getSource();

    /// Return sample id from source generator
    ALuint getSampleBuffer();

private:

    /// Id source
    ALuint m_source;

    /// Decoded sample for next processing
    std::unique_ptr<AudioSampleBase> m_sample;
};

} // namespace audio::al
} // namespace al

#endif
