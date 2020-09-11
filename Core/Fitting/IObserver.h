// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Fitting/IObserver.h
//! @brief     Defines classes IObserver and IObservable (Observer pattern).
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_CORE_FITTING_IOBSERVER_H
#define BORNAGAIN_CORE_FITTING_IOBSERVER_H

#include "Wrap/WinDllMacros.h"
#include <list>
#include <memory>

class IObservable;

//! Observer interface from %Observer pattern.
//! @ingroup tools_internal

class BA_CORE_API_ IObserver
{
public:
    virtual ~IObserver();

    //! method which is used by observable subject to notify change in status
    virtual void notify(IObservable* subject) = 0;
};

//! Observable interface from %Observer pattern
//! @ingroup tools_internal

class BA_CORE_API_ IObservable
{
public:
    //! Shared pointer is used when passing these objects from Python to C++
    typedef std::shared_ptr<IObserver> observer_t;

    virtual ~IObservable();

    //! attach observer to the list of observers
    virtual void attachObserver(observer_t obj);

    //! notify observers about change in status
    virtual void notifyObservers();

private:
    std::list<observer_t> m_observers;
};

#endif // BORNAGAIN_CORE_FITTING_IOBSERVER_H
