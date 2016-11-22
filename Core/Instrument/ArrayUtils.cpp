// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Instrument/ArrayUtils.cpp
//! @brief     Implements various functions to interact from numpy on Python side
//!
//! @homepage  http://bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "Exceptions.h"
#include "ArrayUtils.h"

std::pair<size_t, size_t> ArrayUtils::getShape(const std::vector<std::vector<double>>& data)
{
    size_t nrows = data.size();
    size_t ncols(0);
    if(nrows) ncols = data[0].size();
    for(size_t row=0; row<nrows; row++)
        if(data[row].size() != ncols)
            throw std::runtime_error("Util::getShape() -> Error. "
                                     "Number of elements is different from row to row.");
    return std::make_pair(nrows, ncols);
}

#ifdef BORNAGAIN_PYTHON
#define PY_ARRAY_UNIQUE_SYMBOL BORNAGAIN_PYTHONAPI_ARRAY
#define NO_IMPORT_ARRAY
#include <numpy/arrayobject.h>

PyObject* ArrayUtils::createNumpyArray(const std::vector<double>& data)
{
    const size_t ndim(1);
    npy_int ndim_numpy = ndim;
    npy_intp *ndimsizes_numpy = new npy_intp[ndim];
    ndimsizes_numpy[0] = data.size();

    // creating standalone numpy array
    PyObject *pyarray = PyArray_SimpleNew(ndim_numpy, ndimsizes_numpy, NPY_DOUBLE);
    delete [] ndimsizes_numpy;
    if(pyarray == nullptr )
        throw Exceptions::RuntimeErrorException("ExportOutputData() -> Panic in PyArray_SimpleNew");
    Py_INCREF(pyarray);

    // getting pointer to data buffer of numpy array
    double *array_buffer = (double *)PyArray_DATA((PyArrayObject*)pyarray);

    for(size_t index=0; index<data.size(); ++index)
        *array_buffer++ = data[index];

    return pyarray;
}

#endif // BORNAGAIN_PYTHON
