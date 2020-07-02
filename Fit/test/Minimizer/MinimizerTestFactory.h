// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fit/test/Minimizer/MinimizerTestFactory.h
//! @brief     Defines class MinimizerTestFactory
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef MINIMIZERTESTFACTORY_H
#define MINIMIZERTESTFACTORY_H

#include "FunctionalTestFactory.h"

//! Factory to generate standalone fit tests.

class MinimizerTestFactory : public FunctionalTestFactory
{
public:
    MinimizerTestFactory();
};

#endif // MINIMIZERTESTFACTORY_H
