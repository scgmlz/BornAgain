//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Device/InputOutput/OutputDataReadReflectometry.h
//! @brief     Defines OutputDataReadReflectometry
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
#ifndef BORNAGAIN_DEVICE_INPUTOUTPUT_OUTPUTDATAREADREFLECTOMETRY_H
#define BORNAGAIN_DEVICE_INPUTOUTPUT_OUTPUTDATAREADREFLECTOMETRY_H

#include <istream>

template <class T> class OutputData;

//! Class for reading reflectometry data from ASCII file.
//! @ingroup input_output_internal

class OutputDataReadReflectometry {
public:
    OutputData<double>* readOutputData(std::istream& input_stream);
};

#endif // BORNAGAIN_DEVICE_INPUTOUTPUT_OUTPUTDATAREADREFLECTOMETRY_H
#endif // USER_API
