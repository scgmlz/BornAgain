// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/InputOutput/TiffHandler.cpp
//! @brief     Implements class TiffReadStrategy.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifdef BORNAGAIN_TIFF_SUPPORT

#include "TiffHandler.h"
#include "BornAgainNamespace.h"
#include "SysUtils.h"

namespace {
size_t supported_bitPerSample = 32;
size_t supported_samplesPerPixel = 1;
size_t size_of_int = 4;
}

TiffHandler::TiffHandler()
    : m_tiff(0)
    , m_width(0)
    , m_height(0)
{}

TiffHandler::~TiffHandler()
{
    close();
}

void TiffHandler::read(std::istream &input_stream)
{
    m_tiff = TIFFStreamOpen("MemTIFF", &input_stream);
    if(!m_tiff) {
        throw Exceptions::FormatErrorException("TiffHandler::read() -> Can't open the file.");
    }
    read_header();
    read_data();
    close();
}

const OutputData<double> *TiffHandler::getOutputData() const
{
    return m_data.get();
}

void TiffHandler::write(const OutputData<double> &data, std::ostream &output_stream)
{
    m_tiff = TIFFStreamOpen("MemTIFF", &output_stream);
    m_data.reset(data.clone());
    m_width = m_data->getAxis(BornAgain::X_AXIS_INDEX).size();
    m_height = m_data->getAxis(BornAgain::Y_AXIS_INDEX).size();
    write_header();
    write_data();
    close();
}

void TiffHandler::read_header()
{
    assert(m_tiff);
    uint32 width(0);
    uint32 height(0);
    uint16 photometric(0);
    if (!TIFFGetField(m_tiff, TIFFTAG_IMAGEWIDTH, &width)
        || !TIFFGetField(m_tiff, TIFFTAG_IMAGELENGTH, &height)
        || !TIFFGetField(m_tiff, TIFFTAG_PHOTOMETRIC, &photometric)) {
        throw Exceptions::FormatErrorException("TiffHandler::read_header() -> Error. "
                                               "Can't read width/height/photometric info.");
    }

    m_width = (size_t) width;
    m_height = (size_t) height;

    uint16 orientationTag(0);
    TIFFGetField(m_tiff, TIFFTAG_ORIENTATION, &orientationTag);

    // BitsPerSample defaults to 1 according to the TIFF spec.
    uint16 bitPerSample(0);
    if (!TIFFGetField(m_tiff, TIFFTAG_BITSPERSAMPLE, &bitPerSample))
        bitPerSample = 1;
    uint16 samplesPerPixel(0); // they may be e.g. grayscale with 2 samples per pixel
    if (!TIFFGetField(m_tiff, TIFFTAG_SAMPLESPERPIXEL, &samplesPerPixel))
        samplesPerPixel = 1;

    if(bitPerSample!= supported_bitPerSample ||
            samplesPerPixel != supported_samplesPerPixel) {
        std::ostringstream message;
        message << "TiffHandler::read_header() -> Error. "
                << "Can't read tiff image with following parameters:" << std::endl
                << "    TIFFTAG_PHOTOMETRIC: " << photometric << std::endl
                << "    TIFFTAG_BITSPERSAMPLE: " << bitPerSample << std::endl
                << "    TIFFTAG_SAMPLESPERPIXEL: " << samplesPerPixel << std::endl;
        throw Exceptions::FormatErrorException(message.str());
    }

}

void TiffHandler::read_data()
{
    assert(m_tiff);

    tmsize_t buf_size = TIFFScanlineSize(m_tiff);
    tmsize_t expected_size = size_of_int*m_width;
    if(buf_size != expected_size)
        throw Exceptions::FormatErrorException(
            "TiffHandler::read_data() -> Error. Wrong scanline size.");
    tdata_t buf = _TIFFmalloc(buf_size);
    if(!buf)
        throw Exceptions::FormatErrorException(
            "TiffHandler::read_data() -> Error. Can't allocate buffer.");

    create_output_data();

    std::vector<int> line_buf;
    line_buf.resize(m_width, 0);
    std::vector<int> axes_indices(2);
    for (uint32 row = 0; row < (uint32) m_height; row++) {
        if(TIFFReadScanline(m_tiff, buf, row) < 0)
            throw Exceptions::FormatErrorException(
                "TiffHandler::read_data() -> Error. Error in scanline.");
        memcpy(&line_buf[0], buf, buf_size);
        for(size_t col=0; col<line_buf.size(); ++col) {
//            std::cout << "row:" << row << " col:" << col << " " << line_buf[col] << std::endl;
            axes_indices[0] = col;
            axes_indices[1] = m_height - 1 - row;
            size_t global_index = m_data->toGlobalIndex(axes_indices);
            (*m_data)[global_index] = (double)line_buf[col];
        }
    }
    _TIFFfree(buf);
}

void TiffHandler::write_header()
{
    assert(m_tiff);
    TIFFSetField(m_tiff, TIFFTAG_ARTIST, "BornAgain.IOFactory");
    TIFFSetField(m_tiff, TIFFTAG_DATETIME, SysUtils::getCurrentDateAndTime().c_str());
    TIFFSetField(m_tiff, TIFFTAG_IMAGEDESCRIPTION,
           "Image converted from BornAgain intensity file.");
    TIFFSetField(m_tiff, TIFFTAG_SOFTWARE, "BornAgain");

    uint32 width = m_width;
    uint32 height = m_height;
    TIFFSetField(m_tiff, TIFFTAG_IMAGEWIDTH, width);
    TIFFSetField(m_tiff, TIFFTAG_IMAGELENGTH, height);

    uint16 bitPerSample(supported_bitPerSample);
    uint16 samplesPerPixel(supported_samplesPerPixel);
    TIFFSetField(m_tiff, TIFFTAG_BITSPERSAMPLE, bitPerSample);
    TIFFSetField(m_tiff, TIFFTAG_SAMPLESPERPIXEL, samplesPerPixel);

    TIFFSetField(m_tiff, TIFFTAG_PHOTOMETRIC, PHOTOMETRIC_MINISWHITE);
}

void TiffHandler::write_data()
{
    tmsize_t buf_size = size_of_int*m_width;;
    tdata_t buf = _TIFFmalloc(buf_size);
    if(!buf)
        throw Exceptions::FormatErrorException(
            "TiffHandler::write_data() -> Error. Can't allocate buffer.");

    std::vector<int> line_buf;
    line_buf.resize(m_width, 0);
    std::vector<int> axes_indices(2);
    for (uint32 row = 0; row < (uint32) m_height; row++) {
        for(size_t col=0; col<line_buf.size(); ++col) {
            axes_indices[0] = col;
            axes_indices[1] = m_height - 1 - row;
            size_t global_index = m_data->toGlobalIndex(axes_indices);
            line_buf[col] = static_cast<int>((*m_data)[global_index]);
        }
        memcpy(buf, &line_buf[0], buf_size);

        if(TIFFWriteScanline(m_tiff, buf, row) < 0)
            throw Exceptions::FormatErrorException(
                "TiffHandler::write_data() -> Error. Error in TIFFWriteScanline.");
    }
    _TIFFfree(buf);
    TIFFFlush(m_tiff);
}

void TiffHandler::close()
{
    if(m_tiff) {
        TIFFClose(m_tiff);
        m_tiff = 0;
        m_width = 0;
        m_height = 0;
    }
}

void TiffHandler::create_output_data()
{
    assert(m_tiff);
    m_data.reset(new OutputData<double>);
    m_data->addAxis("x", m_width, 0.0, double(m_width));
    m_data->addAxis("y", m_height, 0.0, double(m_height));
}

#endif // BORNAGAIN_TIFF_SUPPORT
