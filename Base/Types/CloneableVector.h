// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Base/Types/CloneableVector.h
//! @brief     Defines and implements templated class CloneableVector.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_BASE_TYPES_CLONEABLEVECTOR_H
#define BORNAGAIN_BASE_TYPES_CLONEABLEVECTOR_H

#include <memory>
#include <vector>

//! A vector of unique pointers to objects that are cloneable.
//!
//! Equips vector<unique_ptr<T>> with copy constructor.
//! For use with polymorphic objects, or in pimpl idiom.
//!
//! @ingroup tools_internal

//! The objects pointed to must posses a clone() function.

template <class T> class CloneableVector : public std::vector<std::unique_ptr<T>>
{
    using super = std::vector<std::unique_ptr<T>>;

public:
    CloneableVector() : super() {}
    CloneableVector(const CloneableVector& other) : super()
    {
        super::reserve(other.size());
        for (const std::unique_ptr<T>& t : other)
            super::emplace_back(t->clone());
    }
    void push_back(T* t) { super::emplace_back(std::unique_ptr<T>(t)); }
    void emplace_back(std::unique_ptr<T>&& t) { super::emplace_back(t); }
};

#endif // BORNAGAIN_BASE_TYPES_CLONEABLEVECTOR_H
