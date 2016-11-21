// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Fitting/IObserver.h
//! @brief     Defines classes IObserver and IObservable (Observer pattern).
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef IOBSERVER_H
#define IOBSERVER_H

#include "WinDllMacros.h"
#include <list>
#include <memory>

class IObservable;

//! Observer interface from %Observer pattern, for 1:n object dependencies.
//! @ingroup tools_internal

class BA_CORE_API_ IObserver {
public:
    virtual ~IObserver() {}

    //! method which is used by observable subject to notify change in status
    virtual void notify (IObservable* subject) = 0;
};

//! Observable interface from %Observer pattern, for 1:n object dependencies.
//! @ingroup tools_internal

class BA_CORE_API_ IObservable {
public:
    //! Shared pointer is used when passing these objects from Python to C++
    typedef std::shared_ptr<IObserver> observer_t;
    typedef std::list<observer_t> observerlist_t;

    virtual ~IObservable() {}

    //! attach observer to the list of observers
    virtual void attachObserver(observer_t obj);

    //! notify observers about change in status
    virtual void notifyObservers();

private:
    observerlist_t m_observers;
};

#endif // IOBSERVER_H
