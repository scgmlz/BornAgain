// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Fitting/FitObserver.h
//! @brief     Defines class FitObserver.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_CORE_FITTING_FITOBSERVER_H
#define BORNAGAIN_CORE_FITTING_FITOBSERVER_H

#include "Core/Fitting/FitTypes.h"
#include <functional>
#include <vector>

//! Contains collection of observers and call them at specified intervals.
//! Each observer will be called at first iteration and every-nth iterations.

template <class T> class FitObserver
{
public:
    using observer_t = std::function<void(const T&)>;
    FitObserver();

    //! Adds observer to the list.
    //! @param every_nth: An observer function will be called every_nth iterations.
    //! @param observer: Observer function to be called.
    void addObserver(int every_nth, observer_t observer);

    //! Notifies all observers at their personally specified intervals.
    //! @param data: The data which will be passed to the observer.
    void notify(const T& data);

    void notify_all(const T& data);

private:
    class ObserverData
    {
    public:
        ObserverData() : m_every_nth(0) {}
        ObserverData(int every_nth, observer_t observer)
            : m_every_nth(every_nth), m_observer(observer)
        {
        }
        int m_every_nth;
        observer_t m_observer;
    };

    bool need_notify(int every_nth);

    std::vector<ObserverData> m_observers;
    int m_notify_count; //! Total number of notify calls
};

template <class T> FitObserver<T>::FitObserver() : m_notify_count(0) {}

template <class T>
void FitObserver<T>::addObserver(int every_nth, typename FitObserver::observer_t observer)
{
    m_observers.push_back(ObserverData(every_nth, observer));
}

template <class T> void FitObserver<T>::notify(const T& data)
{
    for (const auto& observer : m_observers) {
        if (need_notify(observer.m_every_nth))
            observer.m_observer(data);
    }

    m_notify_count++;
}

template <class T> void FitObserver<T>::notify_all(const T& data)
{
    for (const auto& observer : m_observers)
        observer.m_observer(data);

    m_notify_count++;
}

template <class T> bool FitObserver<T>::need_notify(int every_nth)
{
    return m_notify_count == 0 || m_notify_count % every_nth == 0 ? true : false;
}

#endif // BORNAGAIN_CORE_FITTING_FITOBSERVER_H
