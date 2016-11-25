// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Basics/ISingleton.h
//! @brief     Defines the standard mix-in ISingleton.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef ISINGLETON_H
#define ISINGLETON_H

#include <iostream>
#include <mutex>
#include <stdexcept>

//! Base class for singletons.
//! @ingroup tools_internal

template <class T> class ISingleton
{
public:
    static T& instance()
    {
        static std::mutex single_mutex;
        std::unique_lock<std::mutex> single_lock(single_mutex);
        if (!m_instance) {
            if (m_destroyed)
                // In BornAgain, an ISingleton is deleted when and only when the application
                // terminates. Therefore there is no point in re-creating a deleted ISingleton.
                // To be 110% sure, we explicitly forbid re-creation.
                throw std::runtime_error("Invalid attempt to re-create a deleted ISingleton");
            static T theInstance;
            m_instance = &theInstance;
        }
        return *m_instance;
    }

protected:
    ISingleton() {}
    virtual ~ISingleton()
    {
        m_instance = nullptr;
        m_destroyed = true;
    }

private:
    ISingleton(const ISingleton&) = delete;
    ISingleton& operator=(const ISingleton&) = delete;
    static T* m_instance;
    static bool m_destroyed; //!< to detect re-creation
};

// for templated classes, initializations go into the .h file:
template <class T> T* ISingleton<T>::m_instance = nullptr;
template <class T> bool ISingleton<T>::m_destroyed = false;

#endif // ISINGLETON_H
