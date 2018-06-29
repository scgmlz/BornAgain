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

#include "ChiSquaredModule.h"
#include <cassert>

void ChiSquaredModule::processFitElements(std::vector<FitElement>::iterator first,
                                          std::vector<FitElement>::iterator last)
{
    assert(mp_squared_function);

    for (std::vector<FitElement>::iterator it = first; it != last; ++it) {
        double value_simu = it->getSimulValue();
        double value_real = it->getRealValue();
        double weight = it->getWeight();

        if(mp_intensity_function) {
            value_simu = mp_intensity_function->evaluate(value_simu);
            value_real = mp_intensity_function->evaluate(value_real);
        }

        double squared_difference =
            mp_squared_function->calculateSquaredDifference(
                value_real, value_simu)*weight;

        it->setSquaredDifference(squared_difference);

        double squared_error = mp_squared_function->calculateSquaredError(value_real, value_simu);
        double residual = std::sqrt(weight)*(value_simu - value_real)/std::sqrt(squared_error);

        it->setResidual(residual);
    }
}

double ChiSquaredModule::residual(double a, double b, double weight)
{
    double value_simu = a;
    double value_real = b;

    if(mp_intensity_function) {
        value_simu = mp_intensity_function->evaluate(value_simu);
        value_real = mp_intensity_function->evaluate(value_real);
    }

    double squared_error = mp_squared_function->calculateSquaredError(value_real, value_simu);

    double residual = std::sqrt(weight)*(value_simu - value_real)/std::sqrt(squared_error);
    return residual;
}
