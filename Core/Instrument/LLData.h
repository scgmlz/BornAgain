// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Instrument/LLData.h
//! @brief     Defines class LLData.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef LLDATA_H
#define LLDATA_H

#include "EigenCore.h"
#include "Exceptions.h"
#include <limits>

//! Template class to store data of any type in multi-dimensional space (low-level).
//! @ingroup tools_internal

template <class T> class LLData
{
public:
    // construction, destruction and assignment
    LLData(size_t rank, const int* dimensions);
    LLData(const LLData<T>& right);
    LLData<T>& operator=(const LLData<T>& right);
    ~LLData();

    LLData<double> meanValues() const;

    // accessors
    T& operator[](size_t i);
    const T& operator[](size_t i) const;
    T& atCoordinate(int* coordinate);
    const T& atCoordinate(int* coordinate) const;

    // arithmetic operations
    LLData<T>& operator+=(const LLData<T>& right);
    LLData<T>& operator-=(const LLData<T>& right);
    LLData<T>& operator*=(const LLData<T>& right);
    LLData<T>& operator/=(const LLData<T>& right);

    // initialization, scaling
    void setAll(const T& value);
    void scaleAll(const T& factor);

    // retrieve basic info
    size_t getTotalSize() const;
    inline size_t getRank() const { return m_rank; }
    const int* getDimensions() const { return m_dims; }
    T getTotalSum() const;

private:
    void allocate(size_t rank, const int* dimensions);
    void clear();
    int checkPositiveDimension(int dimension) const;
    size_t convertCoordinate(int* coordinate) const;
    void swapContents(LLData<T>& other);
    T getZeroElement() const;

    size_t m_rank;
    int* m_dims;
    T* m_data_array;
};

#ifndef SWIG
template <>
BA_CORE_API_ Eigen::Matrix2d LLData<Eigen::Matrix2d>::getZeroElement() const;
#endif

// Global helper functions for arithmetic
template <class T> LLData<T> operator+(const LLData<T>& left, const LLData<T>& right);
template <class T> LLData<T> operator-(const LLData<T>& left, const LLData<T>& right);
template <class T> LLData<T> operator*(const LLData<T>& left, const LLData<T>& right);
template <class T> LLData<T> operator/(const LLData<T>& left, const LLData<T>& right);

// Global helper functions for comparison
template <class T> bool HaveSameDimensions(const LLData<T>& left, const LLData<T>& right);


template<class T>
inline LLData<T>::LLData(size_t rank, const int* dimensions)
    : m_rank(0)
    , m_dims(0)
    , m_data_array(0)
{
    allocate(rank, dimensions);
}

template<class T>
LLData<T>::LLData(const LLData<T>& right)
    : m_rank(0)
    , m_dims(0)
    , m_data_array(0)
{
    allocate(right.getRank(), right.getDimensions());
    for (size_t i=0; i<getTotalSize(); ++i) {
        m_data_array[i] = right[i];
    }
}

template<class T>
LLData<T>::~LLData()
{
    clear();
}

template<class T> LLData<T>& LLData<T>::operator=(const LLData<T>& right)
{
    if( this !=& right) {
        LLData<T> copy(right);
        swapContents(copy);
    }
    return *this;
}

template<class T>
inline T& LLData<T>::operator[](size_t i)
{
    return m_data_array[i];
}

template<class T>
inline const T& LLData<T>::operator[](size_t i) const
{
    return m_data_array[i];
}

template<class T>
inline T& LLData<T>::atCoordinate(int* coordinate)
{
    return m_data_array[convertCoordinate(coordinate)];
}

template<class T>
inline const T& LLData<T>::atCoordinate(int* coordinate) const
{
    return m_data_array[convertCoordinate(coordinate)];
}

template<class T> LLData<T>& LLData<T>::operator+=(const LLData<T>& right)
{
    if (!HaveSameDimensions(*this, right))
        throw Exceptions::RuntimeErrorException(
            "Operation += on LLData requires both operands to have the same dimensions");
    for (size_t i=0; i<getTotalSize(); ++i) {
        m_data_array[i] += right[i];
    }
    return *this;
}

template<class T> LLData<T>& LLData<T>::operator-=(const LLData& right)
{
    if (!HaveSameDimensions(*this, right))
        throw Exceptions::RuntimeErrorException(
            "Operation -= on LLData requires both operands to have the same dimensions");
    for (size_t i=0; i<getTotalSize(); ++i) {
        m_data_array[i] -= right[i];
    }
    return *this;
}

template<class T> LLData<T>& LLData<T>::operator*=(const LLData& right)
{
    if (!HaveSameDimensions(*this, right))
        throw Exceptions::RuntimeErrorException(
            "Operation *= on LLData requires both operands to have the same dimensions");
    for (size_t i=0; i<getTotalSize(); ++i) {
        m_data_array[i] *= right[i];
    }
    return *this;
}

template<class T> LLData<T>& LLData<T>::operator/=(const LLData& right)
{
    if (!HaveSameDimensions(*this, right))
        throw Exceptions::RuntimeErrorException(
            "Operation /= on LLData requires both operands to have the same dimensions");
    for (size_t i=0; i<getTotalSize(); ++i) {
        double ratio;
        if( std::abs(m_data_array[i]-right[i]) <=
            std::numeric_limits<double>::epsilon()*std::abs(right[i])) {
            ratio = 1.0;
        } else if (std::abs(right[i]) <= std::numeric_limits<double>::min()) {
            ratio = double(m_data_array[i])/std::numeric_limits<double>::min();
        } else {
            ratio = double(m_data_array[i]/right[i]);
        }
        m_data_array[i] = (T)ratio;
    }
    return *this;
}

template<class T> void LLData<T>::setAll(const T& value)
{
    for (size_t i=0; i<getTotalSize(); ++i)
        m_data_array[i] = value;
}

template<class T> void LLData<T>::scaleAll(const T& factor)
{
    for (size_t i=0; i<getTotalSize(); ++i)
        m_data_array[i] *= factor;
}

template<class T> inline size_t LLData<T>::getTotalSize() const
{
    size_t result = 1;
    for (size_t i=0; i<m_rank; ++i)
        result *= m_dims[i];
    return result;
}

template<class T> T LLData<T>::getTotalSum() const
{
    T result = getZeroElement();
    for (size_t i=0; i<getTotalSize(); ++i)
        result += m_data_array[i];
    return result;
}

template<class T> void LLData<T>::allocate(size_t rank, const int* dimensions)
{
    clear();
    m_rank = rank;
    if (m_rank) {
        m_dims = new int[m_rank];
        for (size_t i=0; i<m_rank; ++i)
            m_dims[i] = checkPositiveDimension(dimensions[i]);
        m_data_array = new T[getTotalSize()];
    }
    else {
        m_data_array = new T[1];
    }
}

template<class T> void LLData<T>::clear()
{
    if (m_rank>0) {
        m_rank = 0;
        delete[] m_data_array;
        delete[] m_dims;
        m_data_array = 0;
        m_dims = 0;
    } else {
        delete[] m_data_array;
    }
}

template<class T> inline int LLData<T>::checkPositiveDimension(int dimension) const
{
    if (dimension<1) {
        throw Exceptions::OutOfBoundsException("Dimension must be bigger than zero.");
    }
    return dimension;
}

template<class T> inline size_t LLData<T>::convertCoordinate(int* coordinate) const
{
    size_t offset = 1;
    size_t result = 0;
    for (size_t i = m_rank; i>0; --i) {
        result += offset*coordinate[i-1];
        offset *= m_dims[i-1];
    }
    return result;
}

template<class T> void LLData<T>::swapContents(LLData<T>& other)
{
    std::swap(this->m_rank, other.m_rank);
    std::swap(this->m_dims, other.m_dims);
    std::swap(this->m_data_array, other.m_data_array);
}

template<class T> T LLData<T>::getZeroElement() const
{
    T result = 0;
    return result;
}

template<class T> LLData<T> operator+(const LLData<T>& left, const LLData<T>& right)
{
    LLData<T> *p_result = new LLData<T>(left);
    (*p_result) += right;
    return *p_result;
}

template<class T> LLData<T> operator-(const LLData<T>& left, const LLData<T>& right)
{
    LLData<T> *p_result = new LLData<T>(left);
    (*p_result) -= right;
    return *p_result;
}

template<class T> LLData<T> operator*(const LLData<T>& left, const LLData<T>& right)
{
    LLData<T> *p_result = new LLData<T>(left);
    (*p_result) *= right;
    return *p_result;
}

template<class T> LLData<T> operator/(const LLData<T>& left, const LLData<T>& right)
{
    LLData<T> *p_result = new LLData<T>(left);
    *p_result /= right;
    return *p_result;
}

template<class T> bool HaveSameDimensions(const LLData<T>& left, const LLData<T>& right)
{
    if (left.getRank() != right.getRank())
        return false;
    const int* ldims = left.getDimensions();
    const int* rdims = right.getDimensions();
    for (size_t i=0; i<left.getRank(); ++i) {
        if (ldims[i] != rdims[i])
            return false;
    }
    return true;
}

#endif // LLDATA_H
