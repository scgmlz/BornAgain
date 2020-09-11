// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Instrument/PyArrayImportUtils.h
//! @brief     Declares functions in namespace PyArrayImport.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_CORE_INSTRUMENT_PYARRAYIMPORTUTILS_H
#define BORNAGAIN_CORE_INSTRUMENT_PYARRAYIMPORTUTILS_H

#include "Wrap/WinDllMacros.h"
#include <vector>

template <class T> class OutputData;

//! Functions for numpy array import to OutputData.
//! Required solely as a shortcut to produce OutputData from numpy arrays of doubles.

namespace PyArrayImport
{

//! for importing 1D array of doubles from python into OutputData
BA_CORE_API_ OutputData<double>* importArrayToOutputData(const std::vector<double>& vec);
//! for importing 2D array of doubles from python into OutputData
BA_CORE_API_ OutputData<double>*
importArrayToOutputData(const std::vector<std::vector<double>>& vec);

} // namespace PyArrayImport

#endif // BORNAGAIN_CORE_INSTRUMENT_PYARRAYIMPORTUTILS_H
