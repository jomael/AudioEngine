#include "ALUtil.hpp"

namespace audio
{
namespace newapi
{

ALuint getFormatNumChannels(ALuint channels)
{
    ALuint format = 0;
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

} // namespace audio::al
} // namespace al
