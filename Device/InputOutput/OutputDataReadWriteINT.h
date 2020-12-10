//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Device/InputOutput/OutputDataReadWriteINT.h
//! @brief     Defines OutputDataReadWriteINT
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
#ifndef BORNAGAIN_DEVICE_INPUTOUTPUT_OUTPUTDATAREADWRITEINT_H
#define BORNAGAIN_DEVICE_INPUTOUTPUT_OUTPUTDATAREADWRITEINT_H

#include <istream>

template <class T> class OutputData;

//! Class for reading and writing BornAgain native IntensityData from ASCII file.
//! @ingroup input_output_internal

class OutputDataReadWriteINT {
public:
    OutputData<double>* readOutputData(std::istream& input_stream);
    void writeOutputData(const OutputData<double>& data, std::ostream& output_stream);

private:
    static void writeOutputDataDoubles(const OutputData<double>& data, std::ostream& output_stream,
                                       size_t n_columns);
    static double ignoreDenormalized(double value);
};

#endif // BORNAGAIN_DEVICE_INPUTOUTPUT_OUTPUTDATAREADWRITEINT_H
#endif // USER_API
