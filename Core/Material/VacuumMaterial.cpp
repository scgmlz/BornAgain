#include "VacuumMaterial.h"
#include "WavevectorInfo.h"
#include "MaterialUtils.h"

VacuumMaterial::VacuumMaterial(const std::string& name) : BaseMaterialImpl(name)
{
}

VacuumMaterial* VacuumMaterial::clone() const
{
    return new VacuumMaterial(*this);
}

complex_t VacuumMaterial::scalarSubtrSLD(const WavevectorInfo& wavevectors) const
{
    double wavelength = wavevectors.getWavelength();
    return complex_t(M_PI / wavelength / wavelength, 0.0);
}

Eigen::Matrix2cd VacuumMaterial::polarizedSubtrSLD(const WavevectorInfo& wavevectors) const
{
    const complex_t unit_factor = scalarSubtrSLD(wavevectors);

    // MagnetizationCorrection is invoked just to create unit_matrix * unit_factor
    return MaterialUtils::MagnetizationCorrection(unit_factor, 0.0, cvector_t{});
}

void VacuumMaterial::print(std::ostream& ostr) const
{
    ostr << "VacuumMaterial:" << getName() << "<" << this << ">{ "
         << "}";
}
