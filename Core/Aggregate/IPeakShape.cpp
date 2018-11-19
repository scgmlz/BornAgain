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

#include <limits>

namespace {
const double maxkappa = std::log(1.0/std::numeric_limits<double>::epsilon())/2.0;
double FisherDistribution(double x, double kappa);
double Gauss3D(double q2, double domainsize);
double Cauchy3D(double q2, double domainsize);
}

IPeakShape::~IPeakShape() =default;

IsotropicGaussPeakShape::IsotropicGaussPeakShape(double max_intensity, double domainsize)
    : m_max_intensity(max_intensity)
    , m_domainsize(domainsize)
{}

IsotropicGaussPeakShape::~IsotropicGaussPeakShape() =default;

IsotropicGaussPeakShape* IsotropicGaussPeakShape::clone() const
{
    return new IsotropicGaussPeakShape(m_max_intensity, m_domainsize);
}

double IsotropicGaussPeakShape::evaluate(const kvector_t q) const
{
    double q_norm = q.mag2();
    return m_max_intensity * Gauss3D(q_norm, m_domainsize);
}

double IsotropicGaussPeakShape::evaluate(const kvector_t q, const kvector_t q_lattice_point) const
{
    return evaluate(q - q_lattice_point);
}

IsotropicLorentzPeakShape::IsotropicLorentzPeakShape(double max_intensity, double domainsize)
    : m_max_intensity(max_intensity)
    , m_domainsize(domainsize)
{}

IsotropicLorentzPeakShape::~IsotropicLorentzPeakShape() =default;

IsotropicLorentzPeakShape* IsotropicLorentzPeakShape::clone() const
{
    return new IsotropicLorentzPeakShape(m_max_intensity, m_domainsize);
}

double IsotropicLorentzPeakShape::evaluate(const kvector_t q) const
{
    double q_norm = q.mag2();
    return m_max_intensity * Cauchy3D(q_norm, m_domainsize);
}

double IsotropicLorentzPeakShape::evaluate(const kvector_t q, const kvector_t q_lattice_point) const
{
    return evaluate(q - q_lattice_point);
}

GaussFisherPeakShape::GaussFisherPeakShape(double max_intensity, double radial_size, double kappa)
    : m_max_intensity(max_intensity)
    , m_radial_size(radial_size)
    , m_kappa(kappa)
{}

GaussFisherPeakShape::~GaussFisherPeakShape() =default;

GaussFisherPeakShape* GaussFisherPeakShape::clone() const
{
    return new GaussFisherPeakShape(m_max_intensity, m_radial_size, m_kappa);
}

double GaussFisherPeakShape::evaluate(const kvector_t q, const kvector_t q_lattice_point) const
{
    double q_r = q.mag();
    double q_lat_r = q_lattice_point.mag();
    double dq2 = (q_r - q_lat_r)*(q_r - q_lat_r);
    if (q_lat_r == 0.0)
        return m_max_intensity * Gauss3D(dq2, m_radial_size);
    double norm_factor = m_radial_size / std::sqrt(M_TWOPI);
    double radial_part = norm_factor * std::exp(-dq2*m_radial_size*m_radial_size/2.0);
    double angular_part = 1.0;
    if (q_r*q_lat_r > 0.0) {
        double dot_norm = q.dot(q_lattice_point)/q_r/q_lat_r;
        angular_part = FisherDistribution(dot_norm, m_kappa)/(q_r*q_r);
    }
    return m_max_intensity * radial_part * angular_part;
}

LorentzFisherPeakShape::LorentzFisherPeakShape(double max_intensity, double radial_size, double kappa)
    : m_max_intensity(max_intensity)
    , m_radial_size(radial_size)
    , m_kappa(kappa)
{}

LorentzFisherPeakShape::~LorentzFisherPeakShape() =default;

LorentzFisherPeakShape* LorentzFisherPeakShape::clone() const
{
    return new LorentzFisherPeakShape(m_max_intensity, m_radial_size, m_kappa);
}

double LorentzFisherPeakShape::evaluate(const kvector_t q, const kvector_t q_lattice_point) const
{
    double q_r = q.mag();
    double q_lat_r = q_lattice_point.mag();
    double dq2 = (q_r - q_lat_r)*(q_r - q_lat_r);
    if (q_lat_r == 0.0)
        return m_max_intensity * Cauchy3D(dq2, m_radial_size);
    double radial_part = m_radial_size / (1.0 + dq2*m_radial_size*m_radial_size) / M_PI;
    double angular_part = 1.0;
    if (q_r*q_lat_r > 0.0) {
        double dot_norm = q.dot(q_lattice_point)/q_r/q_lat_r;
        angular_part = FisherDistribution(dot_norm, m_kappa)/(q_r*q_r);
    }
    return m_max_intensity * radial_part * angular_part;
}

namespace {
double FisherDistribution(double x, double kappa)
{
    if (kappa<=0.0) {
        return 1.0/(4.0*M_PI);
    }
    double prefactor = kappa / (4.0*M_PI);
    if (kappa>maxkappa) {
        return 2.0*prefactor*std::exp(kappa*(x-1.0));
    }
    return prefactor*std::exp(kappa*x)/std::sinh(kappa);
}
double Gauss3D(double q2, double domainsize)
{
    double norm_factor = std::pow(domainsize / std::sqrt(M_TWOPI), 3.0);
    double exponent = -q2*domainsize*domainsize/2.0;
    return norm_factor * std::exp(exponent);
}
double Cauchy3D(double q2, double domainsize)
{
    double lorentz1 = domainsize / (1.0 + q2*domainsize*domainsize) / M_PI;
    return domainsize * lorentz1 * lorentz1;
}
}

