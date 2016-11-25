// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Instrument/FitElement.cpp
//! @brief     Implements class FitElement.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "FitElement.h"
#include <algorithm>

FitElement::FitElement()
    : m_index(0)
    , m_simul_value(0.0)
    , m_real_value(0.0)
    , m_weight(1.0)
    , m_squared_difference(0.0)
    , m_residual(0.0)
{
}

FitElement::FitElement(size_t index, double simul_value, double real_value, double weight)
    : m_index(index)
    , m_simul_value(simul_value)
    , m_real_value(real_value)
    , m_weight(weight)
    , m_squared_difference(0.0)
    , m_residual(0.0)
{
}


FitElement::FitElement(const FitElement& other)
    : m_index(other.m_index)
    , m_simul_value(other.m_simul_value)
    , m_real_value(other.m_real_value)
    , m_weight(other.m_weight)
    , m_squared_difference(other.m_squared_difference)
    , m_residual(other.m_residual)
{
}

FitElement& FitElement::operator=(const FitElement& other)
{
    if (this != &other) {
        FitElement tmp(other);
        tmp.swapContent(*this);
    }
    return *this;
}


void FitElement::swapContent(FitElement& other)
{
    std::swap(this->m_index, other.m_index);
    std::swap(this->m_simul_value, other.m_simul_value);
    std::swap(this->m_real_value, other.m_real_value);
    std::swap(this->m_weight, other.m_weight);
    std::swap(this->m_squared_difference, other.m_squared_difference);
    std::swap(this->m_residual, other.m_residual);
}
