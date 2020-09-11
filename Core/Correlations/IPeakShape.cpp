// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Correlations/IPeakShape.cpp
//! @brief     Implements the interface IPeakShape and subclasses.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Core/Correlations/IPeakShape.h"
#include "Core/Basics/MathConstants.h"
#include "Core/Tools/Integrator.h"
#include "Core/Tools/MathFunctions.h"
#include <limits>

namespace
{

const double maxkappa = std::log(1.0 / std::numeric_limits<double>::epsilon()) / 2.0;
const double maxkappa2 = std::log(std::numeric_limits<double>::max());

double FisherDistribution(double x, double kappa)
{
    if (kappa <= 0.0) {
        return 1.0 / (4.0 * M_PI);
    }
    double prefactor = kappa / (4.0 * M_PI);
    if (kappa > maxkappa) {
        return 2.0 * prefactor * std::exp(kappa * (x - 1.0));
    }
    return prefactor * std::exp(kappa * x) / std::sinh(kappa);
}

double FisherPrefactor(double kappa)
{
    if (kappa <= 0.0) {
        return 1.0 / (4.0 * M_PI);
    }
    if (kappa > maxkappa) {
        return kappa / 2.0 / M_PI;
    } else {
        return kappa * std::exp(kappa) / 4.0 / M_PI / std::sinh(kappa);
    }
}

double MisesPrefactor(double kappa)
{
    if (kappa <= 0.0) {
        return 1.0 / (2.0 * M_PI);
    }
    if (kappa > maxkappa2) {
        return std::sqrt(kappa / 2.0 / M_PI) / (1.0 + 1.0 / (8.0 * kappa));
    } else {
        return std::exp(kappa) / (2.0 * M_PI * MathFunctions::Bessel_I0(kappa));
    }
}

double Gauss3D(double q2, double domainsize)
{
    double norm_factor = std::pow(domainsize / std::sqrt(M_TWOPI), 3.0);
    double exponent = -q2 * domainsize * domainsize / 2.0;
    return norm_factor * std::exp(exponent);
}

double Cauchy3D(double q2, double domainsize)
{
    double lorentz1 = domainsize / (1.0 + q2 * domainsize * domainsize) / M_PI;
    return domainsize * lorentz1 * lorentz1;
}

} // namespace

// ************************************************************************** //
// interface IPeakShape
// ************************************************************************** //

IPeakShape::IPeakShape(const NodeMeta& meta, const std::vector<double>& PValues)
    : ISample(meta, PValues)
{
}

IPeakShape::~IPeakShape() = default;

// ************************************************************************** //
// class IsotropicGaussPeakShape
// ************************************************************************** //

IsotropicGaussPeakShape::IsotropicGaussPeakShape(double max_intensity, double domainsize)
    : m_max_intensity(max_intensity), m_domainsize(domainsize)
{
}

IsotropicGaussPeakShape::~IsotropicGaussPeakShape() = default;

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

// ************************************************************************** //
// class IsotropicLorentzPeakShape
// ************************************************************************** //

IsotropicLorentzPeakShape::IsotropicLorentzPeakShape(double max_intensity, double domainsize)
    : m_max_intensity(max_intensity), m_domainsize(domainsize)
{
}

IsotropicLorentzPeakShape::~IsotropicLorentzPeakShape() = default;

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

// ************************************************************************** //
// class GaussFisherPeakShape
// ************************************************************************** //

GaussFisherPeakShape::GaussFisherPeakShape(double max_intensity, double radial_size, double kappa)
    : m_max_intensity(max_intensity), m_radial_size(radial_size), m_kappa(kappa)
{
}

GaussFisherPeakShape::~GaussFisherPeakShape() = default;

GaussFisherPeakShape* GaussFisherPeakShape::clone() const
{
    return new GaussFisherPeakShape(m_max_intensity, m_radial_size, m_kappa);
}

double GaussFisherPeakShape::evaluate(const kvector_t q, const kvector_t q_lattice_point) const
{
    double q_r = q.mag();
    double q_lat_r = q_lattice_point.mag();
    double dq2 = (q_r - q_lat_r) * (q_r - q_lat_r);
    if (q_lat_r == 0.0)
        return m_max_intensity * Gauss3D(dq2, m_radial_size);
    double norm_factor = m_radial_size / std::sqrt(M_TWOPI);
    double radial_part = norm_factor * std::exp(-dq2 * m_radial_size * m_radial_size / 2.0);
    double angular_part = 1.0;
    if (q_r * q_lat_r > 0.0) {
        double dot_norm = q.dot(q_lattice_point) / q_r / q_lat_r;
        angular_part = FisherDistribution(dot_norm, m_kappa) / (q_r * q_r);
    }
    return m_max_intensity * radial_part * angular_part;
}

// ************************************************************************** //
// class LorentzFisherPeakShape
// ************************************************************************** //

LorentzFisherPeakShape::LorentzFisherPeakShape(double max_intensity, double radial_size,
                                               double kappa)
    : m_max_intensity(max_intensity), m_radial_size(radial_size), m_kappa(kappa)
{
}

LorentzFisherPeakShape::~LorentzFisherPeakShape() = default;

LorentzFisherPeakShape* LorentzFisherPeakShape::clone() const
{
    return new LorentzFisherPeakShape(m_max_intensity, m_radial_size, m_kappa);
}

double LorentzFisherPeakShape::evaluate(const kvector_t q, const kvector_t q_lattice_point) const
{
    double q_r = q.mag();
    double q_lat_r = q_lattice_point.mag();
    double dq2 = (q_r - q_lat_r) * (q_r - q_lat_r);
    if (q_lat_r == 0.0)
        return m_max_intensity * Cauchy3D(dq2, m_radial_size);
    double radial_part = m_radial_size / (1.0 + dq2 * m_radial_size * m_radial_size) / M_PI;
    double angular_part = 1.0;
    if (q_r * q_lat_r > 0.0) {
        double dot_norm = q.dot(q_lattice_point) / q_r / q_lat_r;
        angular_part = FisherDistribution(dot_norm, m_kappa) / (q_r * q_r);
    }
    return m_max_intensity * radial_part * angular_part;
}

// ************************************************************************** //
// class MisesFisherGaussPeakShape
// ************************************************************************** //

MisesFisherGaussPeakShape::MisesFisherGaussPeakShape(double max_intensity, double radial_size,
                                                     kvector_t zenith, double kappa_1,
                                                     double kappa_2)
    : m_max_intensity(max_intensity), m_radial_size(radial_size), m_zenith(zenith.unit()),
      m_kappa_1(kappa_1), m_kappa_2(kappa_2)
{
}

MisesFisherGaussPeakShape::~MisesFisherGaussPeakShape() = default;

MisesFisherGaussPeakShape* MisesFisherGaussPeakShape::clone() const
{
    return new MisesFisherGaussPeakShape(m_max_intensity, m_radial_size, m_zenith, m_kappa_1,
                                         m_kappa_2);
}

double MisesFisherGaussPeakShape::evaluate(const kvector_t q, const kvector_t q_lattice_point) const
{
    // radial part
    double q_r = q.mag();
    double q_lat_r = q_lattice_point.mag();
    double dq2 = (q_r - q_lat_r) * (q_r - q_lat_r);
    if (q_lat_r == 0.0 || q_r == 0.0)
        return m_max_intensity * Gauss3D(dq2, m_radial_size);
    double norm_factor = m_radial_size / std::sqrt(M_TWOPI);
    double radial_part = norm_factor * std::exp(-dq2 * m_radial_size * m_radial_size / 2.0);
    // angular part
    m_uy = m_zenith.cross(q_lattice_point);
    kvector_t zxq = m_zenith.cross(q);
    m_up = q_lattice_point.unit();
    if (m_uy.mag2() <= 0.0 || zxq.mag2() <= 0.0) {
        double x = q.unit().dot(m_up);
        double angular_part = FisherDistribution(x, m_kappa_1);
        return m_max_intensity * radial_part * angular_part;
    }
    m_uy = m_uy.unit();
    m_ux = m_uy.cross(m_zenith);
    kvector_t q_ortho = q - q.dot(m_zenith) * m_zenith;
    m_phi = std::acos(q_ortho.unit().dot(m_ux));
    m_theta = std::acos(q.unit().dot(m_zenith));
    double pre_1 = FisherPrefactor(m_kappa_1);
    double pre_2 = MisesPrefactor(m_kappa_2);
    double integral = RealIntegrator().integrate(
        [&](double phi) -> double { return integrand(phi); }, 0.0, M_TWOPI);
    return m_max_intensity * radial_part * pre_1 * pre_2 * integral;
}

double MisesFisherGaussPeakShape::integrand(double phi) const
{
    kvector_t u_q = std::sin(m_theta) * std::cos(phi) * m_ux
                    + std::sin(m_theta) * std::sin(phi) * m_uy + std::cos(m_theta) * m_zenith;
    double fisher = std::exp(m_kappa_1 * (u_q.dot(m_up) - 1.0));
    double vonmises = std::exp(m_kappa_2 * (std::cos(m_phi - phi) - 1.0));
    return fisher * vonmises;
}

// ************************************************************************** //
// class MisesGaussPeakShape
// ************************************************************************** //

MisesGaussPeakShape::MisesGaussPeakShape(double max_intensity, double radial_size, kvector_t zenith,
                                         double kappa)
    : m_max_intensity(max_intensity), m_radial_size(radial_size), m_zenith(zenith.unit()),
      m_kappa(kappa)
{
}

MisesGaussPeakShape::~MisesGaussPeakShape() = default;

MisesGaussPeakShape* MisesGaussPeakShape::clone() const
{
    return new MisesGaussPeakShape(m_max_intensity, m_radial_size, m_zenith, m_kappa);
}

double MisesGaussPeakShape::evaluate(const kvector_t q, const kvector_t q_lattice_point) const
{
    m_uy = m_zenith.cross(q_lattice_point);
    kvector_t zxq = m_zenith.cross(q);
    if (m_uy.mag2() <= 0.0 || zxq.mag2() <= 0.0) {
        double dq2 = (q - q_lattice_point).mag2();
        return m_max_intensity * Gauss3D(dq2, m_radial_size);
    }
    m_qr = q.mag();
    m_p = q_lattice_point;
    m_uy = m_uy.unit();
    m_ux = m_uy.cross(m_zenith);
    kvector_t q_ortho = q - q.dot(m_zenith) * m_zenith;
    m_phi = std::acos(q_ortho.unit().dot(m_ux));
    m_theta = std::acos(q.unit().dot(m_zenith));
    double pre = MisesPrefactor(m_kappa);
    double integral = RealIntegrator().integrate(
        [&](double phi) -> double { return integrand(phi); }, 0.0, M_TWOPI);
    return m_max_intensity * pre * integral;
}

double MisesGaussPeakShape::integrand(double phi) const
{
    kvector_t q_rot = m_qr
                      * (std::sin(m_theta) * std::cos(phi) * m_ux
                         + std::sin(m_theta) * std::sin(phi) * m_uy + std::cos(m_theta) * m_zenith);
    double dq2 = (q_rot - m_p).mag2();
    double gauss = Gauss3D(dq2, m_radial_size);
    double vonmises = std::exp(m_kappa * (std::cos(m_phi - phi) - 1.0));
    return gauss * vonmises;
}
