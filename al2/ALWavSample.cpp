#include "ALWavSample.hpp"

namespace audio
{
namespace newapi
{

WavSample::WavSample() : m_channels(0), m_sampleRate(0),
    m_duration(0.0f), m_sizeStream(0.0f)
{
    LOG("Constructor");
}

WavSample::WavSample(const std::string &path) : m_file(path)
{
    WavHeader header;

    const size_t WAV_BIT_DEPTH = 16;

    std::ifstream file(path, std::ifstream::binary | std::ifstream::in);
    if(!file.is_open()) {
        LOG("Error : Cannot open the audio file." + path);
    }

    file.read(reinterpret_cast<char*>(&header), sizeof(header));

    if(memcmp(header.id, "RIFF", 4) != 0) {
        LOG("ERROR : Bad RIFF header.");
    }

    if(memcmp(header.waveFmt, "WAVEfmt ", 8) != 0 ||
            memcmp(header.data, "data", 4) != 0) {
        LOG("ERROR: This file is not wav format!");
    }

    if(header.format != WAV_BIT_DEPTH) {
        LOG("ERROR: This file is not 16 bit wav format.");
    }

    m_channels = header.channels;
    m_sampleRate = header.sampleRate;

    m_wave.resize(static_cast<unsigned int>(header.bytesInData));
    file.read(m_wave.data(), static_cast<long>(m_wave.size()));
    m_sizeStream = m_wave.size();

    m_duration = header.totalLength / (header.channels * header.sampleRate * (header.bitsPerSample / 8.0f)) * 1.0f;

    std::clog << "---WAV Audio info--- " << "\n"
              << "Sampling rate : "  << m_sampleRate / 1000.0 << " kHz " << "\n"
              << "Channel       : "  << m_channels << " Channel(s) " << "\n"
              << "Size stream   : "  << m_sizeStream / (1024 * 1024) << " MB" << "\n"
              << "Duration      : "  << m_duration << " ms " << "\n"
              << "Bit depth     : "  << header.format << "\n"
              << "File is       : "  << (header.pcm == 1 ? "Uncompresed"  : "Compresed") <<  "\n\n";

    ALuint channelFomat = getFormatNumChannels(static_cast<ALuint>(m_channels));

    alBufferData(m_buffer, static_cast<ALenum>(channelFomat),
                 m_wave.data(), static_cast<ALsizei>(m_wave.size()), m_sampleRate);

    if(AL_NO_ERROR != alGetError())
    {
        LOG("OpenAL error");
    }
}

WavSample::~WavSample()
{
    LOG("Destroy sample");
}

} // namespace audio::al
} // namespace al
