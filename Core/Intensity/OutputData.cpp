// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Intensity/OutputData.cpp
//! @brief     Implements template specializations of class OutputData.cpp.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Core/Intensity/OutputData.h"
#include "Core/Intensity/CumulativeValue.h"

#ifdef BORNAGAIN_PYTHON

#include "Core/Tools/PythonCore.h"

template <> PyObject* OutputData<double>::getArray() const
{
    std::vector<size_t> dimensions;
    for (size_t i = 0; i < getRank(); i++)
        dimensions.push_back(getAxis(i).size());

    // for rot90 of 2-dim arrays to conform with numpy
    if (dimensions.size() == 2)
        std::swap(dimensions[0], dimensions[1]);

    // creating ndarray objects describing size of dimensions
    npy_int ndim_numpy = (int)dimensions.size();
    npy_intp* ndimsizes_numpy = new npy_intp[dimensions.size()];
    for (size_t i = 0; i < dimensions.size(); i++)
        ndimsizes_numpy[i] = dimensions[i];

    // creating standalone numpy array
    PyObject* pyarray = PyArray_SimpleNew(ndim_numpy, ndimsizes_numpy, NPY_DOUBLE);
    delete[] ndimsizes_numpy;
    if (pyarray == nullptr)
        throw Exceptions::RuntimeErrorException("ExportOutputData() -> Panic in PyArray_SimpleNew");

    // getting pointer to data buffer of numpy array
    double* array_buffer = (double*)PyArray_DATA((PyArrayObject*)pyarray);

    // filling numpy array with output_data
    if (getRank() == 2) {
        for (size_t index = 0; index < getAllocatedSize(); ++index) {
            std::vector<int> axes_indices = getAxesBinIndices(index);
            size_t offset =
                axes_indices[0]
                + m_value_axes[0]->size() * (m_value_axes[1]->size() - 1 - axes_indices[1]);
            array_buffer[offset] = (*this)[index];
        }

    } else {
        for (size_t index = 0; index < getAllocatedSize(); ++index)
            *array_buffer++ = (*this)[index];
    }

    return pyarray;
}

#endif // BORNAGAIN_PYTHON

template <> double OutputData<double>::getValue(size_t index) const
{
    return (*this)[index];
}

template <> double OutputData<CumulativeValue>::getValue(size_t index) const
{
    return (*this)[index].getContent();
}
