#ifndef AL_UTIL_HPP
#define AL_UTIL_HPP

#include <memory>
#include "ALBackend.hpp"
#include "ALSoundBase.hpp"
#include "ALOggSample.hpp"
#include "ALWavSample.hpp"
#include "utils/Exception.hpp"

namespace audio
{
namespace newapi
{

ALint getFormatNumChannels(ALuint channels);

std::unique_ptr<AudioSampleBase> createSample(const std::string &path);

} // namespace audio::newapi
} // namespace al

#endif
