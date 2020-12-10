//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Device/InputOutput/OutputDataReadWriteNumpyTXT.h
//! @brief     Defines OutputDataReadWriteNumpyTXT
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
#ifndef BORNAGAIN_DEVICE_INPUTOUTPUT_OUTPUTDATAREADWRITENUMPYTXT_H
#define BORNAGAIN_DEVICE_INPUTOUTPUT_OUTPUTDATAREADWRITENUMPYTXT_H

#include <istream>

template <class T> class OutputData;

//! Class for reading and writing OutputData from simple ASCII file with the layout as in
//! numpy.savetxt.
//! @ingroup input_output_internal

class OutputDataReadWriteNumpyTXT {
public:
    OutputData<double>* readOutputData(std::istream& input_stream);
    void writeOutputData(const OutputData<double>& data, std::ostream& output_stream);

private:
    static void write1DRepresentation(const OutputData<double>& data, std::ostream& output_stream);
    static void write2DRepresentation(const OutputData<double>& data, std::ostream& output_stream);
    static double ignoreDenormalized(double value);
};

#endif // BORNAGAIN_DEVICE_INPUTOUTPUT_OUTPUTDATAREADWRITENUMPYTXT_H
#endif // USER_API
