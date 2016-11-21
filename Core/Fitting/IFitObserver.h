// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Fitting/IFitObserver.h
//! @brief     Defines class IFitObserver.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
//* ************************************************************************* //

#ifndef IFITOBSERVER_H
#define IFITOBSERVER_H

#include "IObserver.h"
class FitSuite;

//! Base class for all fit observers. Calls update method in following cases:
//! first iteration, every n-th iteration, last iteration and when fit strategy has changed.
//! @ingroup fitting_internal

class BA_CORE_API_ IFitObserver : public IObserver
{
public:
    IFitObserver(int update_every_nth);

    //! The method used by Ovservable when he wants to be observed by this
    virtual void notify(IObservable* subject);

    //! Here Onserver will do actuall job when he thinks that it is a right moment
    virtual void update(FitSuite* fit_suite);

protected:
    int m_update_every_nth;
    int m_current_strategy_index;
    bool m_strategy_has_changed;
};


#endif // IFITOBSERVER_H
