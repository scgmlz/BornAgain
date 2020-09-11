// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Basics/ISingleton.h
//! @brief     Defines the standard mix-in ISingleton.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_CORE_BASICS_ISINGLETON_H
#define BORNAGAIN_CORE_BASICS_ISINGLETON_H

//! Base class for singletons.
//! @ingroup tools_internal

template <class T> class ISingleton
{
public:
    static T& instance()
    {
        static T m_instance;
        return m_instance;
    }

protected:
    ISingleton() = default;
    ~ISingleton() = default;

private:
    ISingleton(const ISingleton&) = delete;
    ISingleton& operator=(const ISingleton&) = delete;
    ISingleton(ISingleton&&) = delete;
    ISingleton& operator=(ISingleton&&) = delete;
};

#endif // BORNAGAIN_CORE_BASICS_ISINGLETON_H
