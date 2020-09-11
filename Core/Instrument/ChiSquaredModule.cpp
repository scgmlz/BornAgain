// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Instrument/ChiSquaredModule.cpp
//! @brief     Implements class ChiSquaredModule.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Core/Instrument/ChiSquaredModule.h"
#include "Core/Basics/Assert.h"
#include "Core/Instrument/VarianceFunctions.h"
#include "Core/Intensity/IIntensityFunction.h"
#include <cmath>
#include <limits>

double ChiSquaredModule::residual(double a, double b, double weight)
{
    double value_simu = a;
    double value_real = b;

    if (mp_intensity_function) {
        value_simu = mp_intensity_function->evaluate(value_simu);
        value_real = mp_intensity_function->evaluate(value_real);
    }

    double variance = m_variance_function->variance(value_real, value_simu);
    double normalize = variance <= 0 ? std::numeric_limits<double>::min() : std::sqrt(variance);

    return std::sqrt(weight) * (value_simu - value_real) / normalize;
}
