//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Device/InputOutput/OutputDataReadWriteTiff.h
//! @brief     Defines class OutputDataReadWriteTiff
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifdef SWIG
#error no need to expose this header to Swig
#endif

#ifndef USER_API
#ifndef BORNAGAIN_DEVICE_INPUTOUTPUT_OUTPUTDATAREADWRITETIFF_H
#define BORNAGAIN_DEVICE_INPUTOUTPUT_OUTPUTDATAREADWRITETIFF_H

#ifdef BORNAGAIN_TIFF_SUPPORT

#include "Device/Data/OutputData.h"
#include <memory>
#include <tiffio.h>

//! Reads/write tiff files.
//! @ingroup input_output_internal

class OutputDataReadWriteTiff {
public:
    OutputDataReadWriteTiff();
    ~OutputDataReadWriteTiff();

    OutputData<double>* readOutputData(std::istream& input_stream);
    void writeOutputData(const OutputData<double>& data, std::ostream& output_stream);

private:
    void read(std::istream& input_stream);
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

#endif // BORNAGAIN_DEVICE_INPUTOUTPUT_OUTPUTDATAREADWRITETIFF_H
#endif // USER_API
