// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Computation/PoissonNoiseBackground.cpp
//! @brief     Implements class PoissonNoiseBackground.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Core/Computation/PoissonNoiseBackground.h"
#include "Core/Tools/MathFunctions.h"

PoissonNoiseBackground::PoissonNoiseBackground()
    : IBackground({"PoissonNoiseBackground", "class_tooltip", {}}, {})
{
}

PoissonNoiseBackground* PoissonNoiseBackground::clone() const
{
    return new PoissonNoiseBackground;
}

double PoissonNoiseBackground::addBackGround(double intensity) const
{
    return MathFunctions::GeneratePoissonRandom(intensity);
}
