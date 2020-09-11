// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Fitting/IObserver.cpp
//! @brief     Implements class IObserver, mostly by including IObserver.h.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Core/Fitting/IObserver.h"

void IObservable::attachObserver(observer_t obj)
{
    m_observers.push_back(obj);
}

void IObservable::notifyObservers()
{
    for (auto it : m_observers)
        it->notify(this);
}

IObserver::~IObserver() = default;

IObservable::~IObservable() = default;
