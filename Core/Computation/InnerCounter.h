// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Computation/InnerCounter.h
//! @brief     Defines class InnerCounter.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef INNERCOUNTER_H
#define INNERCOUNTER_H

#include "INoncopyable.h"

class ProgressHandler;

//! Base class for threaded computation; keeps count of progress.

class InnerCounter : public INoncopyable
{
public:
    InnerCounter() : m_count(0) {}
    void stepProgress(ProgressHandler* progress);

private:
    const int bundle = 100;
    int m_count;
};

#endif // INNERCOUNTER_H
