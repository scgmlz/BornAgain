// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Beam/FootprintFactorGaussian.cpp
//! @brief     Implements class FootprintFactorGaussian.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "FootprintFactorGaussian.h"
#include "MathConstants.h"
#include "MathFunctions.h"
#include "PythonFormatting.h"

FootprintFactorGaussian::FootprintFactorGaussian(double width_ratio) : IFootprintFactor(width_ratio)
{
    initialize();
}

FootprintFactorGaussian* FootprintFactorGaussian::clone() const
{
    return new FootprintFactorGaussian(*this);
}

double FootprintFactorGaussian::calculate(double alpha) const
{
    if (alpha < 0.0 || alpha > M_PI_2)
        return 0.0;
    if (widthRatio() == 0.0)
        return 1.0;
    const double arg = std::sin(alpha) * M_SQRT1_2 / widthRatio();
    return MathFunctions::erf(arg);
}

std::string FootprintFactorGaussian::print() const
{
    std::stringstream result;
    result << PythonFormatting::indent() << "footprint = ";
    result << "ba.FootprintFactorGaussian";
    result << "(" << PythonFormatting::printDouble(widthRatio()) << ")";
    return result.str();
}

FootprintFactorGaussian::FootprintFactorGaussian(const FootprintFactorGaussian& other)
    : IFootprintFactor(other)
{
    initialize();
}

void FootprintFactorGaussian::initialize()
{
    setName(BornAgain::GaussianFootprintFactorType);
}

static_assert(!std::is_copy_constructible<FootprintFactorGaussian>::value,
              "FootprintFactorGaussian should not be copy constructable");
static_assert(!std::is_copy_assignable<FootprintFactorGaussian>::value,
              "FootprintFactorGaussian should not be copy assignable");
