#include "Exceptions.h"
#include "VariableWavelengthMaterial.h"
#include "WavevectorInfo.h"
#include "Transform3D.h"
#include <memory>

namespace
{
// Returns scattering length density conjugate
inline complex_t getSLD(double delta_factor, double beta_factor, double wavelength) noexcept
{
    return complex_t(delta_factor, beta_factor / wavelength);
}
}

VariableWavelengthMaterial::VariableWavelengthMaterial(const std::string& name, complex_t sld,
                                                       double wavelength,
                                                       kvector_t magnetization)
    : HomogeneousMaterial(name, sld, wavelength, magnetization)
    , m_delta_factor(sld.real())
    , m_beta_factor(sld.imag() * wavelength)
{}

VariableWavelengthMaterial::VariableWavelengthMaterial(const std::string& name,
                                                       double number_density,
                                                       double scatt_length, double cx,
                                                       double wavelength, kvector_t magnetization)
    : HomogeneousMaterial(
          name, getSLD(number_density * scatt_length, number_density * cx, wavelength),
          magnetization)
    , m_delta_factor(number_density * scatt_length)
    , m_beta_factor(number_density * cx)
{}

HomogeneousMaterial* VariableWavelengthMaterial::clone() const
{
    return new VariableWavelengthMaterial(*this);
}

complex_t VariableWavelengthMaterial::refractiveIndex(double wavelength) const
{
    double prefactor =  wavelength * wavelength / M_PI;
    return std::sqrt(1.0 - prefactor * getSLD(m_delta_factor, m_beta_factor, wavelength));
}

void VariableWavelengthMaterial::print(std::ostream& ostr) const
{
    ostr << "VariableWavelengthMaterial:" << getName() << "<" << this << ">{ "
         << "R = " << refractiveIndex()
         << ", N*b_coh=" << m_delta_factor << ", N*sigma_ab = " << m_beta_factor
         << ", B=" << magnetization() << "}";
}

void VariableWavelengthMaterial::setRefractiveIndex(const complex_t) {
    throw Exceptions::ClassInitializationException(
        "VariableWavelengthMaterial::setRefractiveIndex() -> Error! "
        "wavelength-independent parameters must be reset in VariableWavelengthMaterial"
        "instead of resetting refractive indices");
}

void VariableWavelengthMaterial::setMaterialData(complex_t sld, double wavelength)
{
    HomogeneousMaterial::setMaterialData(sld, wavelength);
    m_delta_factor = sld.real();
    m_beta_factor = sld.imag() * wavelength;
}

void VariableWavelengthMaterial::setMaterialData(double m_number_density, double m_scatt_length,
                                                     double m_cx, double wavelength)
{
    complex_t sld = getSLD(m_number_density * m_scatt_length, m_number_density * m_cx, wavelength);
    setMaterialData(sld, wavelength);
}

complex_t VariableWavelengthMaterial::scalarSubstrSLD(const WavevectorInfo& wavevectors) const
{
    double wavelength = wavevectors.getWavelength();
    double prefactor = M_PI / wavelength / wavelength;
    complex_t refractive_index = refractiveIndex(wavelength);
    return prefactor * refractive_index * refractive_index;
}
