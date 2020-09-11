// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Intensity/ArrayUtils.h
//! @brief     Defines various functions to interact from numpy on Python side
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_CORE_INTENSITY_ARRAYUTILS_H
#define BORNAGAIN_CORE_INTENSITY_ARRAYUTILS_H

#include "Core/Intensity/OutputData.h"
#include "Wrap/WinDllMacros.h"
#include <memory>
#include <stdexcept>
#include <vector>

//! Array and Numpy utility functions getShape, createNumpyArray.

namespace ArrayUtils
{
//! Returns shape nrows, ncols of 2D array.
template <class T> std::pair<size_t, size_t> getShape(const T& data);

class CreateDataImpl
{
    //! Holds the dimensionality of template argument as the enum value.
    //! Intended for vectors only.
    template <typename T> struct nDim {
        enum { value = 0 };
    };
    template <typename T, typename A> struct nDim<std::vector<T, A>> {
        enum { value = 1 + nDim<T>::value };
    };

    template <typename T> struct baseClass {
        using value = T;
    };
    template <typename T, typename A> struct baseClass<std::vector<T, A>> {
        using value = typename baseClass<T>::value;
    };

    template <class T>
    using ReturnType = std::unique_ptr<OutputData<typename CreateDataImpl::baseClass<T>::value>>;

    template <class T> friend ReturnType<T> createData(const T& vec);

    template <class T>
    static std::unique_ptr<OutputData<T>> createDataImpl(const std::vector<T>& vec);

    template <class T>
    static std::unique_ptr<OutputData<T>> createDataImpl(const std::vector<std::vector<T>>& vec);
};

//! Creates OutputData array from input vector.
//! @param vec: input vector
template <class T> CreateDataImpl::ReturnType<T> createData(const T& vec)
{
    constexpr const int size = CreateDataImpl::nDim<T>::value;
    static_assert(
        size == 1 || size == 2,
        "Error in ArrayUtils::createData: invalid dimensionality or type of the input argument");
    static_assert(std::is_same<CreateDataImpl::ReturnType<T>,
                               decltype(CreateDataImpl::createDataImpl(vec))>::value,
                  "Error in ArrayUtils::createData: invalid return type.");
    return CreateDataImpl::createDataImpl(vec);
}

#ifdef BORNAGAIN_PYTHON
PyObject* createNumpyArray(const std::vector<double>& data);
#endif // BORNAGAIN_PYTHON

//! Creates 1D vector from OutputData.
//! @param vec: OutputData<double>
//! @return vector<double>
template <class T> decltype(auto) createVector1D(const T& data);

//! Creates 2D vector from OutputData.
//! @param vec: OutputData<double>
//! @return vector<vector<double>>
template <class T> decltype(auto) createVector2D(const T& data);

} // namespace ArrayUtils

template <class T>
std::unique_ptr<OutputData<T>> ArrayUtils::CreateDataImpl::createDataImpl(const std::vector<T>& vec)
{
    auto result = std::make_unique<OutputData<T>>();
    const size_t length = vec.size();
    result->addAxis(FixedBinAxis("axis0", length, 0.0, static_cast<double>(length)));
    result->setRawDataVector(vec);
    return result;
}

template <class T>
std::unique_ptr<OutputData<T>>
ArrayUtils::CreateDataImpl::createDataImpl(const std::vector<std::vector<T>>& vec)
{
    auto result = std::make_unique<OutputData<T>>();

    auto shape = ArrayUtils::getShape(vec);
    const size_t nrows = shape.first;
    const size_t ncols = shape.second;

    if (nrows == 0 || ncols == 0)
        throw std::runtime_error(
            "Error in ArrayUtils::createDataImpl: input argument contains empty dimensions");

    result->addAxis(FixedBinAxis("axis0", ncols, 0.0, static_cast<double>(ncols)));
    result->addAxis(FixedBinAxis("axis1", nrows, 0.0, static_cast<double>(nrows)));

    // filling the data
    for (size_t row = 0; row < nrows; ++row) {
        for (size_t col = 0; col < ncols; ++col) {
            size_t globalbin = nrows - row - 1 + col * nrows;
            (*result)[globalbin] = vec[row][col];
        }
    }

    return result;
}

template <class T> std::pair<size_t, size_t> ArrayUtils::getShape(const T& data)
{
    size_t nrows = data.size();
    size_t ncols(0);
    if (nrows)
        ncols = data[0].size();
    for (size_t row = 0; row < nrows; row++)
        if (data[row].size() != ncols)
            throw std::runtime_error("Util::getShape() -> Error. "
                                     "Number of elements is different from row to row.");
    return std::make_pair(nrows, ncols);
}

template <class T> decltype(auto) ArrayUtils::createVector1D(const T& data)
{
    if (data.getRank() != 1)
        throw std::runtime_error("ArrayUtils::createVector1D() -> Error. Not 1D data.");

    using value_type = typename T::value_type;
    std::vector<value_type> result = data.getRawDataVector();
    return result;
}

template <class T> decltype(auto) ArrayUtils::createVector2D(const T& data)
{
    using value_type = typename T::value_type;
    std::vector<std::vector<value_type>> result;

    const size_t nrows = data.getAxis(1).size();
    const size_t ncols = data.getAxis(0).size();

    result.resize(nrows);

    for (size_t row = 0; row < nrows; ++row) {
        result[row].resize(ncols, 0.0);
        for (size_t col = 0; col < ncols; ++col) {
            size_t globalbin = nrows - row - 1 + col * nrows;
            result[row][col] = data[globalbin];
        }
    }

    return result;
}

#endif // BORNAGAIN_CORE_INTENSITY_ARRAYUTILS_H
