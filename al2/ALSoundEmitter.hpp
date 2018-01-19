#ifndef ALSOUNDEMITTER_HPP
#define ALSOUNDEMITTER_HPP

#include <map>
#include "ALSoundBase.hpp"
#include "ALSource.hpp"

namespace audio
{
namespace newapi
{

class AudioEmitter : public AudioEmitterBase
{
public:

    AudioEmitter();
    virtual ~AudioEmitter();

    void create();

private:


};


} // namespace audio::al
} // namespace al

#endif
