// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Intensity/ArrayUtils.cpp
//! @brief     Implements various functions to interact from numpy on Python side
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifdef BORNAGAIN_PYTHON

#include "Core/Intensity/ArrayUtils.h"
#include "Core/Basics/Exceptions.h"
#include "Core/Tools/PythonCore.h"

PyObject* ArrayUtils::createNumpyArray(const std::vector<double>& data)
{
    const size_t ndim(1);
    npy_int ndim_numpy = ndim;
    npy_intp* ndimsizes_numpy = new npy_intp[ndim];
    ndimsizes_numpy[0] = data.size();

    // creating standalone numpy array
    PyObject* pyarray = PyArray_SimpleNew(ndim_numpy, ndimsizes_numpy, NPY_DOUBLE);
    delete[] ndimsizes_numpy;
    if (pyarray == nullptr)
        throw Exceptions::RuntimeErrorException("ExportOutputData() -> Panic in PyArray_SimpleNew");

    // getting pointer to data buffer of numpy array
    double* array_buffer = (double*)PyArray_DATA((PyArrayObject*)pyarray);

    for (size_t index = 0; index < data.size(); ++index)
        *array_buffer++ = data[index];

    return pyarray;
}

#endif // BORNAGAIN_PYTHON
