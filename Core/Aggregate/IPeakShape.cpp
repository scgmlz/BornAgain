// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Aggregate/IPeakShape.cpp
//! @brief     Implements the interface IPeakShape and subclasses.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "IPeakShape.h"
#include "MathConstants.h"

IPeakShape::~IPeakShape() =default;

GaussPeakShape::GaussPeakShape(double max_intensity, double domainsize)
    : m_max_intensity(max_intensity)
    , m_domainsize(domainsize)
{}

GaussPeakShape::~GaussPeakShape() =default;

GaussPeakShape* GaussPeakShape::clone() const
{
    return new GaussPeakShape(m_max_intensity, m_domainsize);
}

double GaussPeakShape::evaluate(const kvector_t q) const
{
    double q_norm = q.mag2();
    double exponent = -q_norm*m_domainsize*m_domainsize/2.0;
    return m_max_intensity * std::exp(exponent);
}

LorentzPeakShape::LorentzPeakShape(double max_intensity, double domainsize)
    : m_max_intensity(max_intensity)
    , m_domainsize(domainsize)
{}

LorentzPeakShape::~LorentzPeakShape() =default;

LorentzPeakShape *LorentzPeakShape::clone() const
{
    return new LorentzPeakShape(m_max_intensity, m_domainsize);
}

double LorentzPeakShape::evaluate(const kvector_t q) const
{
    double q_norm = q.mag2();
    double lorentz = 1.0 / (1.0 + m_domainsize*m_domainsize*q_norm);
    return m_max_intensity * lorentz * lorentz;
}
