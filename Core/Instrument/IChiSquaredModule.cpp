// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Instrument/IChiSquaredModule.cpp
//! @brief     Implements class IChiSquaredModule.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Core/Instrument/IChiSquaredModule.h"
#include "Core/Instrument/VarianceFunctions.h"
#include "Core/Intensity/IIntensityFunction.h"

IChiSquaredModule::IChiSquaredModule() : m_variance_function(new VarianceSimFunction) {}

const IVarianceFunction* IChiSquaredModule::varianceFunction() const
{
    return m_variance_function.get();
}

IChiSquaredModule::IChiSquaredModule(const IChiSquaredModule& other)
{
    if (other.m_variance_function)
        m_variance_function.reset(other.m_variance_function->clone());

    if (other.mp_intensity_function)
        mp_intensity_function.reset(other.mp_intensity_function->clone());
}

IChiSquaredModule::~IChiSquaredModule() = default;

void IChiSquaredModule::setVarianceFunction(const IVarianceFunction& variance_function)
{
    m_variance_function.reset(variance_function.clone());
}

const IIntensityFunction* IChiSquaredModule::getIntensityFunction() const
{
    return mp_intensity_function.get();
}

void IChiSquaredModule::setIntensityFunction(const IIntensityFunction& intensity_function)
{
    mp_intensity_function.reset(intensity_function.clone());
}
