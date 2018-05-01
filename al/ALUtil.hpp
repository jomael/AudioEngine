#ifndef AL_UTIL_HPP
#define AL_UTIL_HPP

#include <memory>
#include "ALBackend.hpp"
#include "ALSoundBase.hpp"
#include "ALOggSample.hpp"
#include "ALWavSample.hpp"
#include "util/Exception.hpp"

namespace audio
{
namespace al
{

ALint getFormatNumChannels(ALuint channels);
std::unique_ptr<AudioSampleBase> createSample(const std::string &path);
void setDistanceModel(ALenum model);

} // namespace audio::al
} // namespace al

#endif
