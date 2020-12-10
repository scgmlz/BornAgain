//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Residual/ChiSquaredModule.cpp
//! @brief     Implements class ChiSquaredModule.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "Core/Residual/ChiSquaredModule.h"
#include "Base/Utils/Assert.h"
#include "Core/Residual/VarianceFunctions.h"
#include "Core/Residual/IIntensityFunction.h"
#include <cmath>
#include <limits>

double ChiSquaredModule::residual(double a, double b, double weight) {
    double value_simu = a;
    double value_real = b;

    if (m_intensity_function) {
        value_simu = m_intensity_function->evaluate(value_simu);
        value_real = m_intensity_function->evaluate(value_real);
    }

    double variance = m_variance_function->variance(value_real, value_simu);
    double normalize = variance <= 0 ? std::numeric_limits<double>::min() : std::sqrt(variance);

    return std::sqrt(weight) * (value_simu - value_real) / normalize;
}
