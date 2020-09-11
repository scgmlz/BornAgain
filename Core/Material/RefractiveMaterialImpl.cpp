// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Material/RefractiveMaterialImpl.cpp
//! @brief     Implements class RefractiveMaterialImpl.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Core/Material/RefractiveMaterialImpl.h"
#include "Core/Vector/WavevectorInfo.h"

RefractiveMaterialImpl::RefractiveMaterialImpl(const std::string& name, double delta, double beta,
                                               kvector_t magnetization)
    : MagneticMaterialImpl(name, magnetization), m_delta(delta),
      m_beta(beta < 0. ? throw std::runtime_error(
                 "The imaginary part of the refractive index must be greater or equal zero")
                       : beta)
{
}

RefractiveMaterialImpl* RefractiveMaterialImpl::clone() const
{
    return new RefractiveMaterialImpl(*this);
}

complex_t RefractiveMaterialImpl::refractiveIndex(double) const
{
    return complex_t(1.0 - m_delta, m_beta);
}

complex_t RefractiveMaterialImpl::refractiveIndex2(double) const
{
    complex_t result(1.0 - m_delta, m_beta);
    return result * result;
}

complex_t RefractiveMaterialImpl::materialData() const
{
    return complex_t(m_delta, m_beta);
}

complex_t RefractiveMaterialImpl::scalarSubtrSLD(const WavevectorInfo& wavevectors) const
{
    double wavelength = wavevectors.getWavelength();
    double prefactor = M_PI / wavelength / wavelength;
    return prefactor * refractiveIndex2(wavelength);
}

void RefractiveMaterialImpl::print(std::ostream& ostr) const
{
    ostr << "RefractiveMaterial:" << getName() << "<" << this << ">{ "
         << "delta=" << m_delta << ", beta=" << m_beta << ", B=" << magnetization() << "}";
}
