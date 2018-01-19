#ifndef AUDIOSYSTEM_HPP
#define AUDIOSYSTEM_HPP

#include <memory>
#include <iostream>

#include "ALBackend.hpp"
#include "ALOggSample.hpp"
#include "ALWavSample.hpp"

#include "utils/Exception.hpp"

namespace audio
{
namespace newapi
{

class AudioSystem : public OpenALBackend
{
public:
    AudioSystem();
    virtual ~AudioSystem();

    void loadFromFile(const std::string &path);

private:

    std::unique_ptr<AudioSampleBase> createSample(const std::string &path);


};

class AudioEmitter : public AudioEmitterBase
{
public:
    virtual ~AudioEmitter();

};

} // namespace audio::al
} // namespace al

#endif
