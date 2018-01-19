#include "ALOggSample.hpp"

// Stb vorbis implementation
#include "stb_vorbis.h"

namespace audio
{
namespace newapi
{

OggSample::OggSample() : m_channels(0), m_sampleRate(0.0), m_error(0)
{
    LOG("Constructor");
}

OggSample::OggSample(const std::string &path) : m_channels(0), m_sampleRate(0.0), m_error(0)
{
    // Size of kilobyte for convert.
    //const float SIZE_KB = 1024.0;

    stb_vorbis *vorbis = stb_vorbis_open_filename(path.c_str(), &m_error, nullptr);

    if(!vorbis)
    {
        LOG("Bad initialize stb_vorbis!");
    }

    // Information about format ogg sound.
    stb_vorbis_info info = stb_vorbis_get_info(vorbis);
    m_sampleRate = info.sample_rate;
    m_duration = stb_vorbis_stream_length_in_seconds(vorbis);
    stb_vorbis_close(vorbis);

    short *data;
    int samples, sample_rate;
    samples = stb_vorbis_decode_filename(path.c_str(), &m_channels, &sample_rate, &data);

    ALuint format = getFormatNumChannels(m_channels);

    std::clog << "---Ogg Audio info--- "    << "\n"
              << "Sampling rate : " << sample_rate / 1000.0 << " kHz " << "\n"
              << "Channel       : " << m_channels << " Channel(s) " << "\n"
             // << "Size stream   : " << m_streamSize / (SIZE_KB * SIZE_KB) << " MB" << "\n"
              << "Duration      : " << m_duration << " ms " << "\n\n";

    alBufferData(m_buffer, format, data, sizeof(short) * samples * m_channels, m_sampleRate);
}

OggSample::~OggSample()
{
    LOG("Destructor");
}

} // namespace audio::al
} // namespace al
