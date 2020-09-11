// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Material/MaterialBySLDImpl.cpp
//! @brief     Implements class MaterialBySLDImpl.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Core/Material/MaterialBySLDImpl.h"
#include "Core/Basics/Units.h"
#include "Core/Vector/WavevectorInfo.h"

namespace
{
const double square_angstroms = Units::angstrom * Units::angstrom;

inline double getWlPrefactor(double wavelength)
{
    return wavelength * wavelength / M_PI;
}
} // namespace

MaterialBySLDImpl::MaterialBySLDImpl(const std::string& name, double sld_real, double sld_imag,
                                     kvector_t magnetization)
    : MagneticMaterialImpl(name, magnetization), m_sld_real(sld_real),
      m_sld_imag(sld_imag < 0. ? throw std::runtime_error(
                     "The imaginary part of the SLD must be greater or equal zero")
                               : sld_imag)
{
}

MaterialBySLDImpl* MaterialBySLDImpl::clone() const
{
    return new MaterialBySLDImpl(*this);
}

complex_t MaterialBySLDImpl::refractiveIndex(double wavelength) const
{
    return std::sqrt(refractiveIndex2(wavelength));
}

complex_t MaterialBySLDImpl::refractiveIndex2(double wavelength) const
{
    return 1.0 - getWlPrefactor(wavelength) * sld();
}

complex_t MaterialBySLDImpl::materialData() const
{
    return complex_t(m_sld_real * square_angstroms, m_sld_imag * square_angstroms);
}

complex_t MaterialBySLDImpl::scalarSubtrSLD(const WavevectorInfo& wavevectors) const
{
    double wavelength = wavevectors.getWavelength();
    return 1.0 / getWlPrefactor(wavelength) - sld();
}

void MaterialBySLDImpl::print(std::ostream& ostr) const
{
    ostr << "MaterialBySLD:" << getName() << "<" << this << ">{ "
         << "sld_real=" << m_sld_real << ", sld_imag = " << m_sld_imag << ", B=" << magnetization()
         << "}";
}

complex_t MaterialBySLDImpl::sld() const
{
    return complex_t(m_sld_real, -m_sld_imag);
}
