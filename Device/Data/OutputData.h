//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Device/Data/OutputData.h
//! @brief     Defines and implements templated class OutputData.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_DEVICE_DATA_OUTPUTDATA_H
#define BORNAGAIN_DEVICE_DATA_OUTPUTDATA_H

#include "Base/Axis/FixedBinAxis.h"
#include "Base/Py/PyObject.h"
#include "Base/Types/SafePointerVector.h"
#include "Base/Utils/Assert.h"
#include "Base/Utils/ThreadInfo.h"
#include "Device/Data/LLData.h"
#include "Device/Data/OutputDataIterator.h"
#include <sstream>

using std::size_t;

//! Templated class to store data of type double or CumulativeValue in multi-dimensional space.
//! @ingroup tools

template <class T> class OutputData {
public:
    using value_type = T;

    OutputData();
    OutputData(const OutputData&) = delete;
    const OutputData& operator=(const OutputData&) = delete;
    ~OutputData();
    OutputData* clone() const;

    void copyFrom(const OutputData<T>& x);
    template <class U> void copyShapeFrom(const OutputData<U>& other);
    OutputData<double>* meanValues() const;

    void addAxis(const IAxis& new_axis);
    void addAxis(const std::string& name, size_t size, double start, double end);

    //! returns axis with given serial number
    const IAxis& axis(size_t serial_number) const;

    // retrieve basic info

    //! Returns number of dimensions.
    size_t rank() const { return m_value_axes.size(); }

    //! Returns total size of data buffer (product of bin number in every dimension).
    size_t getAllocatedSize() const {
        if (m_ll_data)
            return m_ll_data->getTotalSize();
        return 0;
    }

    //! Returns all sizes of its axes
    std::vector<size_t> getAllSizes() const;

    //! Returns copy of raw data vector
    std::vector<T> getRawDataVector() const;

    //! Returns sum of all values in the data structure
    T totalSum() const;

    // iterators

    friend class OutputDataIterator<T, OutputData<T>>;
    friend class OutputDataIterator<const T, const OutputData<T>>;

    //! Read/write iterator type
    typedef OutputDataIterator<T, OutputData<T>> iterator;

    //! Read-only iterator type
    typedef OutputDataIterator<const T, const OutputData<T>> const_iterator;

    //! Returns  read/write iterator that points to the first element
    iterator begin();

    //! Returns  read-only iterator that points to the first element
    const_iterator begin() const;

    //! Returns  read/write iterator that points to the one past last element
    iterator end() { return iterator(this, getAllocatedSize()); }

    //! Returns  read-only iterator that points to the one past last element
    const_iterator end() const { return const_iterator(this, getAllocatedSize()); }

    // coordinate and index functions

    //! Returns vector of axes indices for given global index
    //! @param global_index The global index of this data structure.
    //! @return Vector of bin indices for all axes defined
    std::vector<int> getAxesBinIndices(size_t global_index) const;

    //! Returns axis bin index for given global index
    //! @param global_index The global index of this data structure.
    //! @param i_selected_axis Serial number of selected axis.
    //! @return Corresponding bin index for selected axis
    size_t getAxisBinIndex(size_t global_index, size_t i_selected_axis) const;

    //! Returns axis bin index for given global index
    //! @param global_index The global index of this data structure.
    //! @param axis_name The name of selected axis.
    //! @return Corresponding bin index for selected axis
    size_t getAxisBinIndex(size_t global_index, const std::string& axis_name) const;

    //! Returns global index for specified indices of axes
    //! @param axes_indices Vector of axes indices for all specified axes in this dataset
    //! @return Corresponding global index
    size_t toGlobalIndex(const std::vector<unsigned>& axes_indices) const;

    //! Returns global index for specified axes values
    //! @param coordinates Vector of axes coordinates for all specified axes in this dataset
    //! @return Closest global index
    size_t findGlobalIndex(const std::vector<double>& coordinates) const;

    //! Returns the value of selected axis for given global_index.
    //! @param global_index The global index of this data structure.
    //! @param i_selected_axis Serial number of selected axis.
    //! @return corresponding bin center of selected axis
    double getAxisValue(size_t global_index, size_t i_selected_axis) const;

    //! Returns the value of selected axis for given global_index.
    //! @param global_index The global index of this data structure.
    //! @param axis_name The name of selected axis.
    //! @return corresponding bin center of selected axis
    double getAxisValue(size_t global_index, const std::string& axis_name) const;

    //! Returns values on all defined axes for given globalbin number
    //! @param global_index The global index of this data structure.
    //! @return Vector of corresponding bin centers
    std::vector<double> getAxesValues(size_t global_index) const;

    //! Returns bin of selected axis for given global_index.
    //! @param global_index The global index of this data structure.
    //! @param i_selected_axis Serial number of selected axis.
    //! @return Corresponding Bin1D object
    Bin1D getAxisBin(size_t global_index, size_t i_selected_axis) const;

    //! Returns bin of selected axis for given global_index.
    //! @param global_index The global index of this data structure.
    //! @param axis_name The name of selected axis.
    //! @return Corresponding Bin1D object
    Bin1D getAxisBin(size_t global_index, const std::string& axis_name) const;

    // modifiers

    //! Sets object into initial state (no dimensions, data)
    void clear();

    //! Sets content of output data to specific value
    void setAllTo(const T& value);

    //! multiply every item of this output data by value
    void scaleAll(const T& factor);

    //! Adds 'rank' axes with indicated sizes
    void setAxisSizes(size_t rank, int* n_dims);

    //! Sets new values to raw data vector
    void setRawDataVector(const std::vector<T>& data_vector);

    //! Sets new values to raw data array
    void setRawDataArray(const T* source);

    //! addition-assignment operator for two output data
    const OutputData<T>& operator+=(const OutputData<T>& right);

    //! substraction-assignment operator for two output data
    const OutputData<T>& operator-=(const OutputData<T>& right);

    //! division-assignment operator for two output data
    const OutputData<T>& operator/=(const OutputData<T>& right);

    //! multiplication-assignment operator for two output data
    const OutputData<T>& operator*=(const OutputData<T>& right);

    //! Returns value or summed value, depending on T
    double getValue(size_t index) const;

    //! indexed accessor
    T& operator[](size_t index) {
        ASSERT(m_ll_data);
        return (*m_ll_data)[index];
    }

    //! indexed accessor (const)
    const T& operator[](size_t index) const {
        ASSERT(m_ll_data);
        return (*m_ll_data)[index];
    }

    // helpers

    //! Returns true if object have same dimensions and number of axes bins
    template <class U> bool hasSameDimensions(const OutputData<U>& right) const;

    //! Returns true if objects a) have same dimensions b) bin boundaries of axes coincide
    template <class U> bool hasSameShape(const OutputData<U>& right) const;

    //! returns data as Python numpy array
#ifdef BORNAGAIN_PYTHON
    PyObject* getArray() const;
#endif

    //! returns true if object is correctly initialized
    bool isInitialized() const;

    //! memory allocation for current dimensions configuration
    void allocate();

private:
    //! returns serial number of axis with given name
    size_t getAxisIndex(const std::string& axis_name) const;

    //! checks if given axis name exists
    bool axisNameExists(const std::string& axis_name) const;

    SafePointerVector<IAxis> m_value_axes;
    LLData<T>* m_ll_data;
};

// --------------------------------------------------------------------- //
// Implementation
// --------------------------------------------------------------------- //

template <class T> OutputData<T>::OutputData() : m_value_axes(), m_ll_data(nullptr) {
    allocate();
}

template <class T> OutputData<T>::~OutputData() {
    clear();
    delete m_ll_data;
}

template <class T> OutputData<T>* OutputData<T>::clone() const {
    OutputData<T>* ret = new OutputData<T>();
    ret->m_value_axes = m_value_axes;
    (*ret->m_ll_data) = *m_ll_data;
    return ret;
}

template <class T> void OutputData<T>::copyFrom(const OutputData<T>& other) {
    clear();
    m_value_axes = other.m_value_axes;
    delete m_ll_data;
    m_ll_data = 0;
    if (other.m_ll_data)
        m_ll_data = new LLData<T>(*other.m_ll_data);
}

template <class T>
template <class U>
void OutputData<T>::copyShapeFrom(const OutputData<U>& other) {
    clear();
    size_t rank = other.rank();
    for (size_t i = 0; i < rank; ++i)
        addAxis(other.axis(i));
}

template <class T> OutputData<double>* OutputData<T>::meanValues() const {
    auto* ret = new OutputData<double>();
    ret->copyShapeFrom(*this);
    ret->allocate();
    for (size_t i = 0; i < m_ll_data->getTotalSize(); ++i)
        (*ret)[i] = getValue(i);
    return ret;
}

template <class T> void OutputData<T>::addAxis(const IAxis& new_axis) {
    if (axisNameExists(new_axis.getName()))
        throw std::runtime_error("OutputData<T>::addAxis(const IAxis& new_axis) -> "
                                 "Error! Attempt to add axis with already existing name '"
                                 + new_axis.getName() + "'");
    if (new_axis.size() > 0) {
        m_value_axes.push_back(new_axis.clone());
        allocate();
    }
}

template <class T>
void OutputData<T>::addAxis(const std::string& name, size_t size, double start, double end) {
    if (axisNameExists(name))
        throw std::runtime_error("OutputData<T>::addAxis(std::string name) -> "
                                 "Error! Attempt to add axis with already existing name '"
                                 + name + "'");
    FixedBinAxis new_axis(name, size, start, end);
    addAxis(new_axis);
}

template <class T> const IAxis& OutputData<T>::axis(size_t serial_number) const {
    return *m_value_axes[serial_number];
}

template <class T> inline std::vector<size_t> OutputData<T>::getAllSizes() const {
    ASSERT(m_ll_data);
    std::vector<size_t> result;
    for (size_t i = 0; i < rank(); ++i) {
        int dim = m_ll_data->dimensions()[i];
        result.push_back(dim);
    }
    return result;
}

template <class T> inline std::vector<T> OutputData<T>::getRawDataVector() const {
    ASSERT(m_ll_data);
    std::vector<T> result;
    for (size_t i = 0; i < getAllocatedSize(); ++i)
        result.push_back((*m_ll_data)[i]);
    return result;
}

template <class T> typename OutputData<T>::iterator OutputData<T>::begin() {
    typename OutputData<T>::iterator result(this);
    return result;
}

template <class T> typename OutputData<T>::const_iterator OutputData<T>::begin() const {
    typename OutputData<T>::const_iterator result(this);
    return result;
}

template <class T> std::vector<int> OutputData<T>::getAxesBinIndices(size_t global_index) const {
    ASSERT(m_ll_data);
    size_t remainder = global_index;
    std::vector<int> result;
    result.resize(m_ll_data->rank());
    for (size_t i = 0; i < m_ll_data->rank(); ++i) {
        result[m_ll_data->rank() - 1 - i] =
            (int)(remainder % m_value_axes[m_ll_data->rank() - 1 - i]->size());
        remainder /= m_value_axes[m_ll_data->rank() - 1 - i]->size();
    }
    return result;
}

template <class T>
size_t OutputData<T>::getAxisBinIndex(size_t global_index, size_t i_selected_axis) const {
    ASSERT(m_ll_data);
    size_t remainder(global_index);
    for (size_t i = 0; i < m_ll_data->rank(); ++i) {
        size_t i_axis = m_ll_data->rank() - 1 - i;
        size_t result = remainder % m_value_axes[i_axis]->size();
        if (i_selected_axis == i_axis)
            return result;
        remainder /= m_value_axes[i_axis]->size();
    }
    throw std::runtime_error("OutputData<T>::getAxisBinIndex() -> "
                             "Error! No axis with given number");
}

template <class T>
size_t OutputData<T>::getAxisBinIndex(size_t global_index, const std::string& axis_name) const {
    return getAxisBinIndex(global_index, getAxisIndex(axis_name));
}

template <class T>
size_t OutputData<T>::toGlobalIndex(const std::vector<unsigned>& axes_indices) const {
    ASSERT(m_ll_data);
    if (axes_indices.size() != m_ll_data->rank())
        throw std::runtime_error("size_t OutputData<T>::toGlobalIndex() -> "
                                 "Error! Number of coordinates must match rank of data structure");
    size_t result = 0;
    size_t step_size = 1;
    for (size_t i = m_ll_data->rank(); i > 0; --i) {
        if (axes_indices[i - 1] >= m_value_axes[i - 1]->size()) {
            std::ostringstream message;
            message << "size_t OutputData<T>::toGlobalIndex() -> Error. Index ";
            message << axes_indices[i - 1] << " is out of range. Axis ";
            message << m_value_axes[i - 1]->getName();
            message << " size " << m_value_axes[i - 1]->size() << ".\n";
            throw std::runtime_error(message.str());
        }
        result += axes_indices[i - 1] * step_size;
        step_size *= m_value_axes[i - 1]->size();
    }
    return result;
}

template <class T>
size_t OutputData<T>::findGlobalIndex(const std::vector<double>& coordinates) const {
    ASSERT(m_ll_data);
    if (coordinates.size() != m_ll_data->rank())
        throw std::runtime_error("OutputData<T>::findClosestIndex() -> "
                                 "Error! Number of coordinates must match rank of data structure");
    std::vector<unsigned> axes_indexes;
    axes_indexes.resize(m_ll_data->rank());
    for (size_t i = 0; i < m_ll_data->rank(); ++i)
        axes_indexes[i] = static_cast<unsigned>(m_value_axes[i]->findClosestIndex(coordinates[i]));
    return toGlobalIndex(axes_indexes);
}

template <class T>
double OutputData<T>::getAxisValue(size_t global_index, size_t i_selected_axis) const {
    auto axis_index = getAxisBinIndex(global_index, i_selected_axis);
    return (*m_value_axes[i_selected_axis])[axis_index];
}

template <class T>
double OutputData<T>::getAxisValue(size_t global_index, const std::string& axis_name) const {
    return getAxisValue(global_index, getAxisIndex(axis_name));
}

template <class T> std::vector<double> OutputData<T>::getAxesValues(size_t global_index) const {
    std::vector<int> indices = getAxesBinIndices(global_index);
    std::vector<double> result;
    for (size_t i_axis = 0; i_axis < indices.size(); ++i_axis)
        result.push_back((*m_value_axes[i_axis])[indices[i_axis]]);
    return result;
}

template <class T>
Bin1D OutputData<T>::getAxisBin(size_t global_index, size_t i_selected_axis) const {
    auto axis_index = getAxisBinIndex(global_index, i_selected_axis);
    return m_value_axes[i_selected_axis]->bin(axis_index);
}

template <class T>
Bin1D OutputData<T>::getAxisBin(size_t global_index, const std::string& axis_name) const {
    return getAxisBin(global_index, getAxisIndex(axis_name));
}

template <class T> inline T OutputData<T>::totalSum() const {
    ASSERT(m_ll_data);
    return m_ll_data->getTotalSum();
}

template <class T> void OutputData<T>::clear() {
    m_value_axes.clear();
    allocate();
}

template <class T> void OutputData<T>::setAllTo(const T& value) {
    if (!m_ll_data)
        throw std::runtime_error(
            "OutputData::setAllTo() -> Error! Low-level data object was not yet initialized.");
    m_ll_data->setAll(value);
}

template <class T> void OutputData<T>::scaleAll(const T& factor) {
    if (!m_ll_data)
        throw std::runtime_error(
            "OutputData::scaleAll() -> Error! Low-level data object was not yet initialized.");
    m_ll_data->scaleAll(factor);
}

template <class T> void OutputData<T>::setAxisSizes(size_t rank, int* n_dims) {
    clear();
    std::string basename("axis");
    for (size_t i = 0; i < rank; ++i) {
        std::ostringstream name;
        name << basename << i;
        addAxis(name.str(), n_dims[i], 0.0, (double)(n_dims[i] - 1));
    }
}

template <class T> const OutputData<T>& OutputData<T>::operator+=(const OutputData<T>& right) {
    ASSERT(m_ll_data);
    *this->m_ll_data += *right.m_ll_data;
    return *this;
}

template <class T> const OutputData<T>& OutputData<T>::operator-=(const OutputData<T>& right) {
    ASSERT(m_ll_data);
    *this->m_ll_data -= *right.m_ll_data;
    return *this;
}

template <class T> const OutputData<T>& OutputData<T>::operator*=(const OutputData<T>& right) {
    ASSERT(m_ll_data);
    *this->m_ll_data *= *right.m_ll_data;
    return *this;
}

template <class T> bool OutputData<T>::isInitialized() const {
    if (!m_ll_data)
        return false;
    if (rank() != m_ll_data->rank())
        return false;
    if (!rank())
        return false;
    return true;
}

template <class T> const OutputData<T>& OutputData<T>::operator/=(const OutputData<T>& right) {
    ASSERT(m_ll_data);
    *this->m_ll_data /= *right.m_ll_data;
    return *this;
}

template <class T> void OutputData<T>::allocate() {
    delete m_ll_data;
    size_t rank = m_value_axes.size();
    int* dims = new int[rank];
    for (size_t i = 0; i < rank; ++i) {
        dims[i] = (int)axis(i).size();
    }
    m_ll_data = new LLData<T>(rank, dims);
    T default_value = {};
    m_ll_data->setAll(default_value);
    delete[] dims;
}

template <class T> inline void OutputData<T>::setRawDataVector(const std::vector<T>& data_vector) {
    if (data_vector.size() != getAllocatedSize())
        throw std::runtime_error(
            "OutputData<T>::setRawDataVector() -> Error! "
            "setRawDataVector can only be called with a data vector of the correct size.");
    for (size_t i = 0; i < getAllocatedSize(); ++i)
        (*m_ll_data)[i] = data_vector[i];
}

template <class T> inline void OutputData<T>::setRawDataArray(const T* source) {
    for (size_t i = 0; i < getAllocatedSize(); ++i)
        (*m_ll_data)[i] = source[i];
}

//! Returns true if object have same dimensions
template <class T>
template <class U>
inline bool OutputData<T>::hasSameDimensions(const OutputData<U>& right) const {
    if (!isInitialized())
        return false;
    if (!right.isInitialized())
        return false;
    if (rank() != right.rank())
        return false;
    for (size_t i_axis = 0; i_axis < rank(); ++i_axis)
        if (axis(i_axis).size() != right.axis(i_axis).size())
            return false;
    return true;
}

//! Returns true if object have same dimensions and shape of axis
template <class T>
template <class U>
bool OutputData<T>::hasSameShape(const OutputData<U>& right) const {
    if (!hasSameDimensions(right))
        return false;

    for (size_t i = 0; i < m_value_axes.size(); ++i)
        if (!HaveSameNameAndShape(axis(i), right.axis(i)))
            return false;
    return true;
}

//! returns data as Python numpy array
#ifdef BORNAGAIN_PYTHON
template <> PyObject* OutputData<double>::getArray() const;
#endif

// return index of axis
template <class T> size_t OutputData<T>::getAxisIndex(const std::string& axis_name) const {
    for (size_t i = 0; i < m_value_axes.size(); ++i)
        if (m_value_axes[i]->getName() == axis_name)
            return i;
    throw std::runtime_error("OutputData<T>::getAxisIndex() -> "
                             "Error! Axis with given name not found '"
                             + axis_name + "'");
}

template <class T> bool OutputData<T>::axisNameExists(const std::string& axis_name) const {
    for (size_t i = 0; i < m_value_axes.size(); ++i)
        if (m_value_axes[i]->getName() == axis_name)
            return true;
    return false;
}

#endif // BORNAGAIN_DEVICE_DATA_OUTPUTDATA_H
