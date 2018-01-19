#ifndef ALSOUNDBASE_HPP
#define ALSOUNDBASE_HPP

#include <iostream>
#include <glm/glm.hpp>
#include <AL/al.h>

class AudioSampleBase
{
public:

    AudioSampleBase() { }
    virtual ~AudioSampleBase() { }

    virtual float duration() const = 0;
    //virtual std::string name() const = 0;
    virtual int numberOfChannel() const = 0;
    //virtual int sizeofBytes() const = 0;
    virtual ALuint getBuffer() const = 0;
};

struct AudioPropertiesBase
{
    glm::vec3 position = glm::vec3(0.0f,0.0f,0.0f);
    float baseVolume = 0.0f;
    float volume = 0.0f;
    float sampleRate = 0.0f;
    float minimumDistance = 0.0f;
    float maximumDistance = 0.0f;
};

class AudioEmitterBase
{
public:

    AudioEmitterBase() { }
    virtual ~AudioEmitterBase() { }

    virtual void is2DSound() = 0;
    virtual void is3DSound() = 0;
    virtual void setPosition(glm::vec3 &position) = 0;
    virtual void setSampleRate(float &sampleRate) = 0;
    virtual void setVolume(float &volume) = 0;
    virtual void setPriority(float &volume) = 0;
    virtual void setStop(bool &stop) = 0;
    virtual void setLoop(bool &loop) = 0;
    //virtual AudioPropertiesBase getProperties() = 0;
};

#endif
