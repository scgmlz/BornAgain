// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Instrument/OutputDataIterator.h
//! @brief     Defines and implements template class OutputDataIterator.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef OUTPUTDATAITERATOR_H
#define OUTPUTDATAITERATOR_H

#include <cstddef>
#include <iterator>
#include <utility>

//! Iterator for underlying OutputData container.
//! @ingroup tools_internal

template <class TValue, class TContainer> class OutputDataIterator {
public:
    //! Empty constructor to comply with stl forward iterators
    OutputDataIterator();

    //! constructor
    OutputDataIterator(TContainer* p_output_data, size_t start_at_index = 0);

    //! templated copy construction
    template <class TValue2, class TContainer2>
    OutputDataIterator(const OutputDataIterator<TValue2, TContainer2>& other);

    //! non-templated copy construction
    OutputDataIterator(const OutputDataIterator<TValue, TContainer>& other);

    //! templated copy assignment
    template <class TValue2, class TContainer2>
    OutputDataIterator<TValue, TContainer>&
    operator=(const OutputDataIterator<TValue2, TContainer2>& right);

    //! non-templated copy asssignment
    OutputDataIterator<TValue, TContainer>&
    operator=(const OutputDataIterator<TValue, TContainer>& right);

    ~OutputDataIterator();

    //! prefix increment
    OutputDataIterator<TValue, TContainer>& operator++();

    //! postfix increment
    OutputDataIterator<TValue, TContainer> operator++(int);

    //! retrieve current element
    TValue& operator*() const;

    //! pointer access
    TValue* operator->() const;

    //! Returns current index
    size_t getIndex() const { return m_current_index; }

    //! Returns container pointer
    TContainer* getContainer() const { return mp_output_data; }

    //! Swaps iterators
    void swap(OutputDataIterator<TValue, TContainer>& other);

    // typedefs for std::iterator_traits
    typedef std::forward_iterator_tag iterator_category;
    typedef TValue value_type;
    typedef ptrdiff_t difference_type;
    typedef TValue* pointer_type;
    typedef TValue& reference_type;
    //#ifdef _MSC_VER
    typedef TValue* pointer;
    typedef TValue& reference;
    //#endif

private:
    size_t m_current_index;
    TContainer* mp_output_data;
};

//! make Swappable
template <class TValue, class TContainer>
void swap(OutputDataIterator<TValue, TContainer>& left,
          OutputDataIterator<TValue, TContainer>& right) {
    left.swap(right);
}

//! test for equality
template <class TValue1, class TContainer1, class TValue2, class TContainer2>
bool operator==(const OutputDataIterator<TValue1, TContainer1>& left,
                const OutputDataIterator<TValue2, TContainer2>& right);

//! test for inequality
template <class TValue1, class TContainer1, class TValue2, class TContainer2>
bool operator!=(const OutputDataIterator<TValue1, TContainer1>& left,
                const OutputDataIterator<TValue2, TContainer2>& right);

template <class TValue, class TContainer>
OutputDataIterator<TValue, TContainer>::OutputDataIterator()
    : m_current_index(0), mp_output_data(0) {}

template <class TValue, class TContainer>
OutputDataIterator<TValue, TContainer>::OutputDataIterator(
    TContainer* p_output_data, size_t start_at_index)
    : m_current_index(start_at_index), mp_output_data(p_output_data) {}

template <class TValue, class TContainer>
template <class TValue2, class TContainer2>
OutputDataIterator<TValue, TContainer>::OutputDataIterator(
    const OutputDataIterator<TValue2, TContainer2>& other)
    : m_current_index(0), mp_output_data(0) {
    mp_output_data = static_cast<TContainer*>(other.getContainer());
    m_current_index = other.getIndex();
}

template <class TValue, class TContainer>
OutputDataIterator<TValue, TContainer>::OutputDataIterator(
    const OutputDataIterator<TValue, TContainer>& other)
    : m_current_index(0), mp_output_data(0) {
    mp_output_data = other.getContainer();
    m_current_index = other.getIndex();
}

template <class TValue, class TContainer>
template <class TValue2, class TContainer2>
OutputDataIterator<TValue, TContainer>& OutputDataIterator<TValue, TContainer>::
operator=(const OutputDataIterator<TValue2, TContainer2>& right) {
    OutputDataIterator<TValue, TContainer> copy(right);
    swap(copy);
    return *this;
}

template <class TValue, class TContainer>
OutputDataIterator<TValue, TContainer>& OutputDataIterator<TValue, TContainer>::
operator=(const OutputDataIterator<TValue, TContainer>& right) {
    OutputDataIterator<TValue, TContainer> copy(right);
    swap(copy);
    return *this;
}

template <class TValue, class TContainer>
OutputDataIterator<TValue, TContainer>::~OutputDataIterator() {}

template <class TValue, class TContainer>
OutputDataIterator<TValue, TContainer>& OutputDataIterator<TValue, TContainer>::
operator++() {
    if (m_current_index < mp_output_data->getAllocatedSize()) {
        ++m_current_index;
    }
    return *this;
}

template <class TValue, class TContainer>
OutputDataIterator<TValue, TContainer> OutputDataIterator<TValue, TContainer>::
operator++(int /**/) {
    OutputDataIterator<TValue, TContainer> result(*this);
    this->operator++();
    return result;
}

template <class TValue, class TContainer>
TValue& OutputDataIterator<TValue, TContainer>::operator*() const {
    return (*mp_output_data)[m_current_index];
}

template <class TValue, class TContainer>
TValue* OutputDataIterator<TValue, TContainer>::operator->() const {
    return& ((*mp_output_data)[m_current_index]);
}

template <class TValue, class TContainer>
void OutputDataIterator<TValue, TContainer>::swap(
    OutputDataIterator<TValue, TContainer>& other) {
    std::swap(this->m_current_index, other.m_current_index);
    std::swap(this->mp_output_data, other.mp_output_data);
}

//! test for equality
template <class TValue1, class TContainer1, class TValue2, class TContainer2>
bool operator==(const OutputDataIterator<TValue1, TContainer1>& left,
                const OutputDataIterator<TValue2, TContainer2>& right) {
    return left.getContainer() == right.getContainer() &&
           left.getIndex() == right.getIndex();
}

//! test for inequality
template <class TValue1, class TContainer1, class TValue2, class TContainer2>
bool operator!=(const OutputDataIterator<TValue1, TContainer1>& left,
                const OutputDataIterator<TValue2, TContainer2>& right) {
    return !(left == right);
}

#endif // OUTPUTDATAITERATOR_H
