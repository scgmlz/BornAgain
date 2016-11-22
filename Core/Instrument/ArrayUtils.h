// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Instrument/ArrayUtils.h
//! @brief     Defines various functions to interact from numpy on Python side
//!
//! @homepage  http://bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef ARRAYUTILS_H
#define ARRAYUTILS_H

#include <vector>

#ifdef BORNAGAIN_PYTHON
#define NPY_NO_DEPRECATED_API NPY_1_7_API_VERSION
#include <Python.h>
#endif // BORNAGAIN_PYTHON

//! Array and Numpy utility functions getShape, createNumpyArray.

namespace ArrayUtils
{

    //! Returns shape nrows, ncols of 2D array.
    BA_CORE_API_ std::pair<size_t, size_t> getShape(const std::vector<std::vector<double>>& data);

#ifdef BORNAGAIN_PYTHON
    PyObject* createNumpyArray(const std::vector<double>& data);
#endif // BORNAGAIN_PYTHON

}

#endif // ARRAYUTILS_H
