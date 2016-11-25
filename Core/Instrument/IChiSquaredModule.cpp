// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Instrument/IChiSquaredModule.cpp
//! @brief     Implements class IChiSquaredModule.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "IChiSquaredModule.h"

IChiSquaredModule::IChiSquaredModule()
    : mp_squared_function(0), mp_data_normalizer(0), mp_intensity_function(0)
{
    mp_squared_function = new SquaredFunctionDefault();
}

IChiSquaredModule::IChiSquaredModule(const IChiSquaredModule& other)
    : ICloneable(), mp_squared_function(0), mp_data_normalizer(0), mp_intensity_function(0)
{
    if (other.mp_squared_function)
        mp_squared_function = other.mp_squared_function->clone();
    if (other.mp_data_normalizer)
        mp_data_normalizer = other.mp_data_normalizer->clone();
    if (other.mp_intensity_function)
        mp_intensity_function = other.mp_intensity_function->clone();
}

IChiSquaredModule::~IChiSquaredModule()
{
    delete mp_squared_function;
    delete mp_data_normalizer;
    delete mp_intensity_function;
}

void IChiSquaredModule::setChiSquaredFunction(ISquaredFunction* squared_function)
{
    delete mp_squared_function;
    mp_squared_function = squared_function;
}

void IChiSquaredModule::setChiSquaredFunction(const ISquaredFunction& squared_function)
{
    setChiSquaredFunction(squared_function.clone());
}

void IChiSquaredModule::setIntensityNormalizer(const IIntensityNormalizer& data_normalizer)
{
    delete mp_data_normalizer;
    mp_data_normalizer = data_normalizer.clone();
}

void IChiSquaredModule::setIntensityFunction(const IIntensityFunction& intensity_function)
{
    delete mp_intensity_function;
    mp_intensity_function = intensity_function.clone();
}
