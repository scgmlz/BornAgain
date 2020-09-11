// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Beam/FootprintGauss.cpp
//! @brief     Implements class FootprintGauss.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Core/Beam/FootprintGauss.h"
#include "Core/Basics/MathConstants.h"
#include "Core/Tools/MathFunctions.h"
#include "Core/Tools/PyFmt.h"

FootprintGauss::FootprintGauss(const std::vector<double> P)
    : IFootprintFactor({"FootprintGauss", "class_tooltip", {}}, P)
{
}

FootprintGauss::FootprintGauss(double width_ratio)
    : FootprintGauss(std::vector<double>{width_ratio})
{
}

FootprintGauss* FootprintGauss::clone() const
{
    return new FootprintGauss(m_width_ratio);
}

double FootprintGauss::calculate(double alpha) const
{
    if (alpha < 0.0 || alpha > M_PI_2)
        return 0.0;
    if (widthRatio() == 0.0)
        return 1.0;
    const double arg = std::sin(alpha) * M_SQRT1_2 / widthRatio();
    return MathFunctions::erf(arg);
}

std::string FootprintGauss::print() const
{
    std::stringstream result;
    result << "\n" << pyfmt::indent() << "# Defining footprint:\n";
    result << pyfmt::indent() << "footprint = ";
    result << "ba.FootprintGauss";
    result << "(" << pyfmt::printDouble(widthRatio()) << ")";
    return result.str();
}

static_assert(!std::is_copy_constructible<FootprintGauss>::value,
              "FootprintGauss should not be copy constructable");
static_assert(!std::is_copy_assignable<FootprintGauss>::value,
              "FootprintGauss should not be copy assignable");
