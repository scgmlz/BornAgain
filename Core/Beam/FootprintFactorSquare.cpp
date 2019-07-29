// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Beam/FootprintFactorSquare.cpp
//! @brief     Implements class FootprintFactorSquare.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "FootprintFactorSquare.h"
#include "MathConstants.h"
#include "PythonFormatting.h"
#include <algorithm>
#include <stdexcept>

FootprintFactorSquare::FootprintFactorSquare(double width_ratio) : IFootprintFactor(width_ratio)
{
    initialize();
}

FootprintFactorSquare* FootprintFactorSquare::clone() const
{
    return new FootprintFactorSquare(*this);
}

double FootprintFactorSquare::calculate(double alpha) const
{
    if (alpha < 0.0 || alpha > M_PI_2)
        return 0.0;
    if (widthRatio() == 0.0)
        return 1.0;
    const double arg = std::sin(alpha) / widthRatio();
    return std::min(arg, 1.0);
}

std::string FootprintFactorSquare::print() const
{
    std::stringstream result;
    result << PythonFormatting::indent() << "footprint = ";
    result << "ba.FootprintFactorSquare";
    result << "(" << PythonFormatting::printDouble(widthRatio()) << ")";
    return result.str();
}

FootprintFactorSquare::FootprintFactorSquare(const FootprintFactorSquare& other)
    : IFootprintFactor(other)
{
    initialize();
}

void FootprintFactorSquare::initialize()
{
    setName(BornAgain::SquareFootprintFactorType);
}

static_assert(!std::is_copy_constructible<FootprintFactorSquare>::value,
              "FootprintFactorSquare should not be copy constructable");
static_assert(!std::is_copy_assignable<FootprintFactorSquare>::value,
              "FootprintFactorSquare should not be copy assignable");
