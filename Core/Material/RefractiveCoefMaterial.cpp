#include "RefractiveCoefMaterial.h"
#include "WavevectorInfo.h"

RefractiveCoefMaterial::RefractiveCoefMaterial(const std::string& name, double delta, double beta,
                                                 kvector_t magnetization)
    : MagneticMaterialImpl(name, magnetization)
    , m_delta(delta)
    , m_beta(beta)
{}

RefractiveCoefMaterial* RefractiveCoefMaterial::clone() const
{
    return new RefractiveCoefMaterial(*this);
}

complex_t RefractiveCoefMaterial::refractiveIndex(double) const
{
    return complex_t(1.0 - m_delta, m_beta);
}

complex_t RefractiveCoefMaterial::refractiveIndex2(double) const
{
    complex_t result(1.0 - m_delta, m_beta);
    return result * result;
}

complex_t RefractiveCoefMaterial::materialData() const
{
    return complex_t(m_delta, m_beta);
}

complex_t RefractiveCoefMaterial::scalarSubtrSLD(const WavevectorInfo& wavevectors) const
{
    double wavelength = wavevectors.getWavelength();
    double prefactor = M_PI/wavelength/wavelength;
    return prefactor * refractiveIndex2(wavelength);
}

void RefractiveCoefMaterial::print(std::ostream& ostr) const
{
    ostr << "RefractiveCoefMaterial:" << getName() << "<" << this << ">{ "
         << "delta=" << m_delta << ", beta=" << m_beta
         << ", B=" << magnetization() << "}";
}

