// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fit/test/FitObjective/FitObjectiveTestFactory.h
//! @brief     Defines class FitObjectiveTestFactory
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef FITOBJECTIVETESTFACTORY_H
#define FITOBJECTIVETESTFACTORY_H

#include "FunctionalTestFactory.h"

//! Factory to generate fitting tests. Tests will based on FitObjective approach.

class FitObjectiveTestFactory : public FunctionalTestFactory
{
public:
    FitObjectiveTestFactory();
};

#endif // FITOBJECTIVETESTFACTORY_H
