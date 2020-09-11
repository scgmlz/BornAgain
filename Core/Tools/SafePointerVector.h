// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Tools/SafePointerVector.h
//! @brief     Defines and implements template class SafePointerVector.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_CORE_TOOLS_SAFEPOINTERVECTOR_H
#define BORNAGAIN_CORE_TOOLS_SAFEPOINTERVECTOR_H

#include <algorithm>
#include <vector>

//! A vector of pointers, owned by *this, with methods to handle them safely.
//! @ingroup tools_internal

//! The objects pointed to must support the ICloneable interface.

template <class T> class SafePointerVector
{
public:
    typedef typename std::vector<T*>::iterator iterator;
    typedef typename std::vector<T*>::const_iterator const_iterator;
    SafePointerVector() {}
    SafePointerVector(const SafePointerVector& other);
    SafePointerVector(SafePointerVector&& other);
    ~SafePointerVector() { clear(); }

    SafePointerVector& operator=(const SafePointerVector& right);
    SafePointerVector& operator=(SafePointerVector&& right);
    size_t size() const { return m_pointers.size(); }
    bool empty() const { return m_pointers.empty(); }
    void push_back(T* pointer) { m_pointers.push_back(pointer); }
    T* operator[](size_t index) { return m_pointers[index]; }
    const T* operator[](size_t index) const { return m_pointers[index]; }
    iterator begin() { return m_pointers.begin(); }
    const_iterator begin() const { return m_pointers.begin(); }
    iterator end() { return m_pointers.end(); }
    const_iterator end() const { return m_pointers.end(); }

    bool deleteElement(T* pointer);

    T* back() { return m_pointers.back(); }
    const T* back() const { return m_pointers.back(); }
    void clear();

private:
    std::vector<T*> m_pointers;
};

template <class T> SafePointerVector<T>::SafePointerVector(const SafePointerVector<T>& other)
{
    for (const_iterator it = other.begin(); it != other.end(); ++it)
        m_pointers.push_back((*it)->clone());
}

template <class T>
SafePointerVector<T>::SafePointerVector(SafePointerVector<T>&& other) : m_pointers{other.m_pointers}
{
}

template <class T>
SafePointerVector<T>& SafePointerVector<T>::operator=(const SafePointerVector<T>& right)
{
    if (this == &right)
        return *this;
    clear();
    for (const_iterator it = right.begin(); it != right.end(); ++it)
        m_pointers.push_back((*it)->clone());
    return *this;
}

template <class T>
SafePointerVector<T>& SafePointerVector<T>::operator=(SafePointerVector<T>&& right)
{
    clear();
    m_pointers = std::move(right.m_pointers);
    right.m_pointers.clear();
    return *this;
}

template <class T> inline bool SafePointerVector<T>::deleteElement(T* pointer)
{
    iterator it = std::find(m_pointers.begin(), m_pointers.end(), pointer);
    if (it == m_pointers.end())
        return false;
    m_pointers.erase(it);
    delete pointer;
    return true;
}

template <class T> void SafePointerVector<T>::clear()
{
    for (iterator it = begin(); it != end(); ++it)
        delete (*it);
    m_pointers.clear();
}

#endif // BORNAGAIN_CORE_TOOLS_SAFEPOINTERVECTOR_H
