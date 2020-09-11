// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/InputOutput/TiffHandler.h
//! @brief     Defines class TiffHandler.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_CORE_INPUTOUTPUT_TIFFHANDLER_H
#define BORNAGAIN_CORE_INPUTOUTPUT_TIFFHANDLER_H

#ifdef BORNAGAIN_TIFF_SUPPORT

#include "Core/Intensity/OutputData.h"
#include <memory>
#include <tiffio.h>

//! Reads/write tiff files, should be used through TiffReadStrategy.
//! @ingroup input_output_internal

class BA_CORE_API_ TiffHandler
{
public:
    TiffHandler();
    ~TiffHandler();

    void read(std::istream& input_stream);

    const OutputData<double>* getOutputData() const;

    void write(const OutputData<double>& data, std::ostream& output_stream);

private:
    void read_header();
    void read_data();
    void write_header();
    void write_data();
    void close();
    void create_output_data();

    TIFF* m_tiff;
    size_t m_width, m_height;
    uint16 m_bitsPerSample, m_samplesPerPixel, m_sampleFormat;
    std::unique_ptr<OutputData<double>> m_data;
};

#endif // BORNAGAIN_TIFF_SUPPORT

#endif // BORNAGAIN_CORE_INPUTOUTPUT_TIFFHANDLER_H
