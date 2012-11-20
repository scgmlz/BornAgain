#ifndef NAMEDVECTOR_H
#define NAMEDVECTOR_H
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   NamedVector.h
//! @brief  Definition of NamedVector class
//! @author Scientific Computing Group at FRM II
//! @date   01.04.2012

#include <string>
#include <vector>
#include <cmath>
#include "Numeric.h"

class NamedVectorBase
{
public:
    NamedVectorBase(std::string name) : m_name(name) {}
    virtual ~NamedVectorBase() {}

    virtual size_t getSize() const=0;
    std::string getName() const { return m_name; }
    void setName(std::string name) { m_name = name; }
    virtual NamedVectorBase* clone() const=0;
private:
    std::string m_name;
};

template <class T> class NamedVector : public NamedVectorBase
{
public:
    NamedVector(std::string name) : NamedVectorBase(name) {}
    NamedVector(std::string name, T start, T end, size_t size);
    NamedVector<T> *createDoubleBinSize() const;
    ~NamedVector();

    size_t getSize() const { return m_value_vector.size(); }
    virtual NamedVector<T>* clone() const;
    void initElements(T start, T end, size_t size);
    void push_back(T element) { m_value_vector.push_back(element); }
    T& operator[](size_t index) { return m_value_vector.at(index); }
    const T& operator[](size_t index) const { return m_value_vector.at(index); }
    T getMin() const { return m_value_vector.front(); }
    T getMax() const { return m_value_vector.back(); }
private:
    std::vector<T> m_value_vector;
};

// global helper function for comparison
template <class T> bool HaveSameNameAndShape(const NamedVector<T> &left, const NamedVector<T> &right);

template <class T> NamedVector<T>::NamedVector(std::string name, T start, T end, size_t size)
    : NamedVectorBase(name)
{
    initElements(start, end, size);
}

template <class T> NamedVector<T>::~NamedVector()
{
    m_value_vector.clear();
}

template <class T> NamedVector<T> *NamedVector<T>::createDoubleBinSize() const
{
    if (getSize() < 2) {
        return clone();
    }
    NamedVector<T> *p_result = new NamedVector<T>(getName());
    for (size_t source_index=0; source_index<getSize(); source_index+=2)
    {
        T value;
        if (source_index==getSize()-1) {
            value = (3.0*m_value_vector.at(source_index) - m_value_vector.at(source_index-1))/2.0;
        }
        else {
            value =  (m_value_vector.at(source_index) + m_value_vector.at(source_index+1))/2.0;
        }
        p_result->push_back(value);
    }
    return p_result;
}

template <class T> NamedVector<T>* NamedVector<T>::clone() const
{
    NamedVector<T> *p_new = new NamedVector<T>(getName());
    p_new->m_value_vector = this->m_value_vector;
    return p_new;
}

template <class T> void NamedVector<T>::initElements(T start, T end, size_t size)
{
	T step = size>1 ? (end - start)/(size-1) : end;
    for (size_t i=0; i<size; ++i)
    {
        push_back(start + step*i);
    }
}

// global helper function for comparison of named vector shape
template <class T> bool HaveSameNameAndShape(const NamedVector<T> &left, const NamedVector<T> &right)
{
    if(left.getSize() != right.getSize()) return false;
    if(left.getName() != right.getName()) return false;
    for(size_t i=0; i<left.getSize(); ++i) if( std::fabs(left[i] - right[i]) > Numeric::double_epsilon)  return false;
    return true;
}

#endif // NAMEDVECTOR_H
