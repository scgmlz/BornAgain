// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Beam/IFootprintFactor.cpp
//! @brief     Implements class IFootprintFactor.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "IFootprintFactor.h"
#include "RealParameter.h"
#include <stdexcept>

IFootprintFactor::IFootprintFactor(double width_ratio) : m_width_ratio(width_ratio)
{
    if (m_width_ratio < 0.0)
        throw std::runtime_error(
            "Error in IFootprintFactor::IFootprintFactor: width ratio is negative");
    initialize();
}

IFootprintFactor::~IFootprintFactor() = default;

void IFootprintFactor::setWidthRatio(double width_ratio)
{
    if (width_ratio < 0.0)
        throw std::runtime_error(
            "Error in IFootprintFactor::setWidthRatio: width ratio is negative");
    m_width_ratio = width_ratio;
}

IFootprintFactor::IFootprintFactor(const IFootprintFactor& other)
    : ICloneable()
    , m_width_ratio(other.m_width_ratio)
{
    initialize();
}

void IFootprintFactor::initialize()
{
    registerParameter(BornAgain::BeamToSampleWidthRatio, &m_width_ratio).setNonnegative();
}
