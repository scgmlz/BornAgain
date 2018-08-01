// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Instrument/ArrayUtils.h
//! @brief     Defines various functions to interact from numpy on Python side
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef ARRAYUTILS_H
#define ARRAYUTILS_H

#include "WinDllMacros.h"
#include "PythonCore.h"

#include <vector>

template<class T> class OutputData;

//! Array and Numpy utility functions getShape, createNumpyArray.

namespace ArrayUtils
{
//! Creates OutputData from 1D vector.
//! @param vec: array values
//! @return pointer to OutputData
BA_CORE_API_ OutputData<double>* createData1D(const std::vector<double>& vec);

//! Creates OutputData from 2D vector.
//! @param vec: array values
//! @return pointer to OutputData
BA_CORE_API_ OutputData<double>* createData2D(const std::vector<std::vector<double>>& vec);

#ifndef SWIG
//! Returns shape nrows, ncols of 2D array.
std::pair<size_t, size_t> getShape(const std::vector<std::vector<double>>& data);

#ifdef BORNAGAIN_PYTHON
PyObject* createNumpyArray(const std::vector<double>& data);
#endif // BORNAGAIN_PYTHON
#endif // SWIG
}

#endif // ARRAYUTILS_H
