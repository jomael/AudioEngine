#ifndef ALWAVSAMPLE_H
#define ALWAVSAMPLE_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string.h>

#include "ALBuffer.hpp"
#include "ALSoundBase.hpp"
#include "ALUtil.hpp"

namespace audio
{
namespace newapi
{

/// Wave files have a master RIFF chunk which includes a
/// WAVE identifier followed by sub-chunks.
/// The data is stored in little-endian byte order.
struct WavHeader
{
    WavHeader() { }

    char    id[4];          // Should always contain "RIFF"
    int32_t totalLength;    // Total file length minus 8
    char    waveFmt[8];     // Should be "WAVEfmt "
    int32_t format;         // 16 for PCM format
    int16_t pcm;            // 1 for PCM format
    int16_t channels;       // number of channels
    int32_t sampleRate;     // Sampling frequency 44100, etc.
    int32_t bytesPerSecond; // Estimating RAM allocation
    int16_t bytesByCapture;
    int16_t bitsPerSample;  // Byte depth 8 bits = 8, 16 bits = 16, etc.
    char    data[4];        // should always contain "data"
    int32_t bytesInData;
};

class WavSample : public AudioSampleBase, public ALBuffer
{
public:

    WavSample();
    WavSample(const std::string &path);
    virtual ~WavSample();

    float duration() const { return m_duration; }
    int numberOfChannel() const   { return m_channels;}

private:

    /// Name wav sample
    std::string m_file;

    /// Number of channels in wav file.
    int16_t m_channels;

    /// Sample frequency wav file. Usually 44100hz.
    int32_t m_sampleRate;

    /// Duration wav file in ms.
    float m_duration;

    /// Size of stream wav file.
    float m_sizeStream;

protected:

    /// Decoded data of wav format.
    std::vector<char> m_wave;
};

} // namespace audio::al
} // namespace al

#endif
