// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Computation/PoissonNoiseBackground.h
//! @brief     Defines class PoissonNoiseBackground.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_CORE_COMPUTATION_POISSONNOISEBACKGROUND_H
#define BORNAGAIN_CORE_COMPUTATION_POISSONNOISEBACKGROUND_H

#include "Core/Computation/IBackground.h"

//! Class representing Poisson noise on top of the scattered intensity
//!
//! @ingroup simulation

class PoissonNoiseBackground : public IBackground
{
public:
    PoissonNoiseBackground();
    PoissonNoiseBackground* clone() const override final;

    void accept(INodeVisitor* visitor) const override { visitor->visit(this); }

    double addBackGround(double intensity) const override final;
};

#endif // BORNAGAIN_CORE_COMPUTATION_POISSONNOISEBACKGROUND_H
