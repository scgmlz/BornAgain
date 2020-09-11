// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/InputOutput/TiffHandler.cpp
//! @brief     Implements class TiffReadStrategy.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifdef BORNAGAIN_TIFF_SUPPORT

#include "Core/InputOutput/TiffHandler.h"
#include "Core/Tools/SysUtils.h"
#include <tiffio.hxx>

TiffHandler::TiffHandler()
    : m_tiff(0), m_width(0), m_height(0), m_bitsPerSample(0), m_samplesPerPixel(0),
      m_sampleFormat(0)
{
}

TiffHandler::~TiffHandler()
{
    close();
}

void TiffHandler::read(std::istream& input_stream)
{
    m_tiff = TIFFStreamOpen("MemTIFF", &input_stream);
    if (!m_tiff) {
        throw Exceptions::FormatErrorException("TiffHandler::read() -> Can't open the file.");
    }
    read_header();
    read_data();
    close();
}

const OutputData<double>* TiffHandler::getOutputData() const
{
    return m_data.get();
}

void TiffHandler::write(const OutputData<double>& data, std::ostream& output_stream)
{
    m_data.reset(data.clone());
    if (m_data->getRank() != 2)
        throw Exceptions::LogicErrorException("TiffHandler::write -> Error. "
                                              "Only 2-dim arrays supported");
    m_tiff = TIFFStreamOpen("MemTIFF", &output_stream);
    m_width = m_data->getAxis(0).size();
    m_height = m_data->getAxis(1).size(); // this does not exist for 1d data
    write_header();
    write_data();
    close();
}

void TiffHandler::read_header()
{
    ASSERT(m_tiff);
    uint32 width(0);
    uint32 height(0);
    if (!TIFFGetField(m_tiff, TIFFTAG_IMAGEWIDTH, &width)
        || !TIFFGetField(m_tiff, TIFFTAG_IMAGELENGTH, &height)) {
        throw Exceptions::FormatErrorException("TiffHandler::read_header() -> Error. "
                                               "Can't read width/height.");
    }

    m_width = (size_t)width;
    m_height = (size_t)height;

    uint16 orientationTag(0);
    TIFFGetField(m_tiff, TIFFTAG_ORIENTATION, &orientationTag);

    bool good = true;

    // BitsPerSample defaults to 1 according to the TIFF spec.
    if (!TIFFGetField(m_tiff, TIFFTAG_BITSPERSAMPLE, &m_bitsPerSample))
        m_bitsPerSample = 1;
    if (8 != m_bitsPerSample && 16 != m_bitsPerSample && 32 != m_bitsPerSample)
        good = false;

    // they may be e.g. grayscale with 2 samples per pixel
    if (!TIFFGetField(m_tiff, TIFFTAG_SAMPLESPERPIXEL, &m_samplesPerPixel))
        m_samplesPerPixel = 1;
    if (m_samplesPerPixel != 1)
        good = false;

    if (!TIFFGetField(m_tiff, TIFFTAG_SAMPLEFORMAT, &m_sampleFormat))
        m_sampleFormat = 1;

    switch (m_sampleFormat) {
    case 1: // unsigned int
    case 2: // signed int
        break;
    case 3: // IEEE float
        if (32 != m_bitsPerSample)
            good = false;
        break;
    default:
        good = false;
    }

    if (!good) {
        std::ostringstream message;
        message << "TiffHandler::read_header() -> Error. "
                << "Can't read tiff image with following parameters:" << std::endl
                << "    TIFFTAG_BITSPERSAMPLE: " << m_bitsPerSample << std::endl
                << "    TIFFTAG_SAMPLESPERPIXEL: " << m_samplesPerPixel << std::endl
                << "    TIFFTAG_SAMPLEFORMAT: " << m_sampleFormat << std::endl;
        throw Exceptions::FormatErrorException(message.str());
    }
}

void TiffHandler::read_data()
{
    ASSERT(m_tiff);

    ASSERT(0 == m_bitsPerSample % 8);
    uint16 bytesPerSample = m_bitsPerSample / 8;
    tmsize_t buf_size = TIFFScanlineSize(m_tiff);
    tmsize_t expected_size = bytesPerSample * m_width;
    if (buf_size != expected_size)
        throw Exceptions::FormatErrorException(
            "TiffHandler::read_data() -> Error. Wrong scanline size.");

    tdata_t buf = _TIFFmalloc(buf_size);
    if (!buf)
        throw Exceptions::FormatErrorException(
            "TiffHandler::read_data() -> Error. Can't allocate buffer.");

    create_output_data();

    std::vector<int8> line_buf;
    line_buf.resize(buf_size, 0);

    std::vector<unsigned> axes_indices(2);

    for (uint32 row = 0; row < (uint32)m_height; row++) {
        if (TIFFReadScanline(m_tiff, buf, row) < 0)
            throw Exceptions::FormatErrorException(
                "TiffHandler::read_data() -> Error. Error in scanline.");

        memcpy(&line_buf[0], buf, buf_size);

        for (unsigned col = 0; col < m_width; ++col) {
            axes_indices[0] = col;
            axes_indices[1] = static_cast<unsigned>(m_height) - 1 - row;
            size_t global_index = m_data->toGlobalIndex(axes_indices);

            void* incoming = &line_buf[col * bytesPerSample];
            double sample = 0;

            switch (m_sampleFormat) {
            case 1: // unsigned int
                switch (m_bitsPerSample) {
                case 8:
                    sample = *reinterpret_cast<uint8*>(incoming);
                    break;
                case 16:
                    sample = *reinterpret_cast<uint16*>(incoming);
                    break;
                case 32:
                    sample = *reinterpret_cast<uint32*>(incoming);
                    break;
                }
                break;
            case 2: // signed int
                switch (m_bitsPerSample) {
                case 8:
                    sample = *reinterpret_cast<int8*>(incoming);
                    break;
                case 16:
                    sample = *reinterpret_cast<int16*>(incoming);
                    break;
                case 32:
                    sample = *reinterpret_cast<int32*>(incoming);
                    break;
                }
                break;
            case 3: // IEEE float
                sample = double(*reinterpret_cast<float*>(incoming));
                break;
            default:
                throw Exceptions::FormatErrorException("TiffHandler: unexpected sample format");
            }

            (*m_data)[global_index] = sample;
        }
    }
    _TIFFfree(buf);
}

void TiffHandler::write_header()
{
    ASSERT(m_tiff);
    TIFFSetField(m_tiff, TIFFTAG_ARTIST, "BornAgain.IOFactory");
    TIFFSetField(m_tiff, TIFFTAG_DATETIME, SysUtils::getCurrentDateAndTime().c_str());
    TIFFSetField(m_tiff, TIFFTAG_IMAGEDESCRIPTION,
                 "Image converted from BornAgain intensity file.");
    TIFFSetField(m_tiff, TIFFTAG_SOFTWARE, "BornAgain");

    uint32 width = static_cast<uint32>(m_width);
    uint32 height = static_cast<uint32>(m_height);
    TIFFSetField(m_tiff, TIFFTAG_IMAGEWIDTH, width);
    TIFFSetField(m_tiff, TIFFTAG_IMAGELENGTH, height);

    // output format, hardcoded here
    uint16 bitPerSample = 32, samplesPerPixel = 1;
    TIFFSetField(m_tiff, TIFFTAG_BITSPERSAMPLE, bitPerSample);
    TIFFSetField(m_tiff, TIFFTAG_SAMPLESPERPIXEL, samplesPerPixel);

    TIFFSetField(m_tiff, TIFFTAG_PHOTOMETRIC, PHOTOMETRIC_MINISWHITE);
}

void TiffHandler::write_data()
{
    typedef int sample_t;
    tmsize_t buf_size = sizeof(sample_t) * m_width;
    tdata_t buf = _TIFFmalloc(buf_size);
    if (!buf)
        throw Exceptions::FormatErrorException(
            "TiffHandler::write_data() -> Error. Can't allocate buffer.");

    std::vector<sample_t> line_buf;
    line_buf.resize(m_width, 0);
    std::vector<unsigned> axes_indices(2);
    for (unsigned row = 0; row < (uint32)m_height; row++) {
        for (unsigned col = 0; col < line_buf.size(); ++col) {
            axes_indices[0] = col;
            axes_indices[1] = static_cast<unsigned>(m_height) - 1 - row;
            size_t global_index = m_data->toGlobalIndex(axes_indices);
            line_buf[col] = static_cast<sample_t>((*m_data)[global_index]);
        }
        memcpy(buf, &line_buf[0], buf_size);

        if (TIFFWriteScanline(m_tiff, buf, row) < 0)
            throw Exceptions::FormatErrorException(
                "TiffHandler::write_data() -> Error. Error in TIFFWriteScanline.");
    }
    _TIFFfree(buf);
    TIFFFlush(m_tiff);
}

void TiffHandler::close()
{
    if (m_tiff) {
        TIFFClose(m_tiff);
        m_tiff = 0;
        m_width = 0;
        m_height = 0;
    }
}

void TiffHandler::create_output_data()
{
    ASSERT(m_tiff);
    m_data.reset(new OutputData<double>);
    m_data->addAxis("x", m_width, 0.0, double(m_width));
    m_data->addAxis("y", m_height, 0.0, double(m_height));
}

#endif // BORNAGAIN_TIFF_SUPPORT
