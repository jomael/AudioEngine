#include "ALUtil.hpp"

namespace audio
{
namespace al
{

ALint getFormatNumChannels(ALuint channels)
{
    ALint format = 0;
    switch(channels) {
    case 1: format = AL_FORMAT_MONO16; break;
    case 2: format = AL_FORMAT_STEREO16; break;
    case 4: format = AL_FORMAT_QUAD16; break;
    case 6: format = AL_FORMAT_51CHN16; break;
    case 7: format = AL_FORMAT_61CHN16; break;
    case 8: format = AL_FORMAT_71CHN16; break;
    default : format = 0; break;
    }

    if(format == -1) {
        format = 0;
    }

    return format;
}

std::unique_ptr<AudioSampleBase> createSample(const std::string &path)
{
    if(path.rfind(".wav") == path.size() - 4)
    {
        return std::make_unique<WavSample>(path);
    }
    else if(path.rfind(".ogg") == path.size() - 4)
    {
        return std::make_unique<OggSample>(path);
    }

    Throw(InvalidArgument,
          strprintf("only .wav or .ogg files are currently supported, "
                    "got '%s'", path.c_str()));
}

void setDistanceModel(ALenum model)
{
    switch(model)
    {
    case AL_NONE:
        alDistanceModel(AL_NONE);
        break;
    case AL_EXPONENT_DISTANCE:
        alDistanceModel(AL_EXPONENT_DISTANCE);
        break;
    case AL_EXPONENT_DISTANCE_CLAMPED:
        alDistanceModel(AL_EXPONENT_DISTANCE_CLAMPED);
        break;
    case AL_INVERSE_DISTANCE:
        alDistanceModel(AL_INVERSE_DISTANCE);
        break;
    case AL_INVERSE_DISTANCE_CLAMPED:
        alDistanceModel(AL_INVERSE_DISTANCE_CLAMPED);
        break;
    case AL_LINEAR_DISTANCE:
        alDistanceModel(AL_LINEAR_DISTANCE);
        break;
    case AL_LINEAR_DISTANCE_CLAMPED:
        alDistanceModel(AL_LINEAR_DISTANCE_CLAMPED);
        break;
    default:
        LOG("Warning: Unknown distance model!");
    }
}

} // namespace audio::al
} // namespace al
