//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Device/Beam/FootprintGauss.cpp
//! @brief     Implements class FootprintGauss.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "Device/Beam/FootprintGauss.h"
#include "Base/Math/Constants.h"
#include "Base/Math/Functions.h"

FootprintGauss::FootprintGauss(const std::vector<double> P)
    : IFootprintFactor({"FootprintGauss", "class_tooltip", {}}, P) {}

FootprintGauss::FootprintGauss(double width_ratio)
    : FootprintGauss(std::vector<double>{width_ratio}) {}

FootprintGauss* FootprintGauss::clone() const {
    return new FootprintGauss(m_width_ratio);
}

double FootprintGauss::calculate(double alpha) const {
    if (alpha < 0.0 || alpha > M_PI_2)
        return 0.0;
    if (widthRatio() == 0.0)
        return 1.0;
    const double arg = std::sin(alpha) * M_SQRT1_2 / widthRatio();
    return Math::erf(arg);
}

static_assert(!std::is_copy_constructible<FootprintGauss>::value,
              "FootprintGauss should not be copy constructable");
static_assert(!std::is_copy_assignable<FootprintGauss>::value,
              "FootprintGauss should not be copy assignable");
