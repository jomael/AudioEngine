#ifndef AL_SOUND_BASE_HPP
#define AL_SOUND_BASE_HPP

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
    ALuint idSource = 0;
    ALuint idBuffer = 0;
};

class AudioEmitterBase
{
public:

    AudioEmitterBase() { }
    virtual ~AudioEmitterBase() { }

    virtual void setPosition(const glm::vec3 &position) = 0;
    virtual void setVelocity(const glm::vec3 &velocity) = 0;
    virtual void setDirection(const glm::vec3 &direction) = 0;
    virtual void setVolume(float &volume) = 0;
    virtual void setLoop(bool loop) = 0;
};

#endif
