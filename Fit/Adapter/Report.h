//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fit/Adapter/Report.h
//! @brief     Declares report namespace.
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
#ifndef BORNAGAIN_FIT_ADAPTER_REPORT_H
#define BORNAGAIN_FIT_ADAPTER_REPORT_H

#include <string>

class MinimizerAdapter;

//! Utility functions to generate reports

namespace mumufit::internal {

//! Reports results of minimization in the form of multi-line string
std::string reportToString(const MinimizerAdapter& minimizer);

}; // namespace mumufit::internal

#endif // BORNAGAIN_FIT_ADAPTER_REPORT_H
#endif // USER_API
