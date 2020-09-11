// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Beam/FootprintSquare.cpp
//! @brief     Implements class FootprintSquare.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Core/Beam/FootprintSquare.h"
#include "Core/Basics/MathConstants.h"
#include "Core/Tools/PyFmt.h"
#include <algorithm>
#include <stdexcept>

FootprintSquare::FootprintSquare(const std::vector<double> P)
    : IFootprintFactor({"FootprintSquare", "class_tooltip", {}}, P)
{
}

FootprintSquare::FootprintSquare(double width_ratio)
    : FootprintSquare(std::vector<double>{width_ratio})
{
}

FootprintSquare* FootprintSquare::clone() const
{
    return new FootprintSquare(m_width_ratio);
}

double FootprintSquare::calculate(double alpha) const
{
    if (alpha < 0.0 || alpha > M_PI_2)
        return 0.0;
    if (widthRatio() == 0.0)
        return 1.0;
    const double arg = std::sin(alpha) / widthRatio();
    return std::min(arg, 1.0);
}

std::string FootprintSquare::print() const
{
    std::stringstream result;
    result << "\n" << pyfmt::indent() << "# Defining footprint:\n";
    result << pyfmt::indent() << "footprint = ";
    result << "ba.FootprintSquare";
    result << "(" << pyfmt::printDouble(widthRatio()) << ")";
    return result.str();
}

static_assert(!std::is_copy_constructible<FootprintSquare>::value,
              "FootprintSquare should not be copy constructable");
static_assert(!std::is_copy_assignable<FootprintSquare>::value,
              "FootprintSquare should not be copy assignable");
