// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Material/WavelengthIndependentMaterial.h
//! @brief     Defines and implements class WavelengthIndependentMaterial.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef WAVELENGTHINDEPENDENTMATERIAL_H
#define WAVELENGTHINDEPENDENTMATERIAL_H

#include "HomogeneousMaterial.h"

//! Material class derived from Homogeneous material. Incorporates methods
//! for recalculating refractive indices for a wavelength specified by a user
//! Material is assumed to be applied in the case of neutron calculations
class BA_CORE_API_ VariableWavelengthMaterial : public HomogeneousMaterial
{
public:
    //! Creates material with the given scattering length density
    VariableWavelengthMaterial(const std::string& name, complex_t sld, double wavelength,
                                  kvector_t magnetization = kvector_t());

    //! Creates material with the given number density, coherent scattering length and absorption
    //! cross-section
    VariableWavelengthMaterial(const std::string& name, double number_density,
                               double scatt_length, double cx, double wavelength,
                               kvector_t magnetization = kvector_t());

    virtual ~VariableWavelengthMaterial() {}

    using HomogeneousMaterial::refractiveIndex;

    //! Returns refractive index for particular wavelength
    complex_t refractiveIndex(double wavelength) const;

    //TODO: setRefractiveIndex method should be removed in favor of setSLD method
    virtual void setRefractiveIndex(const complex_t refractive_index) override;

    //! resets material data
    virtual void setMaterialData(complex_t sld, double wavelength) override;
    void setMaterialData(double m_number_density, double m_scatt_length, double m_cx,
                             double wavelength);

    virtual complex_t scalarSubstrSLD(const WavevectorInfo& wavevectors) const override;

private:
    virtual HomogeneousMaterial* clone() const override;
    virtual void print(std::ostream& ostr) const override;

    double m_delta_factor; //!< product of number density and coherent scattering length
    double m_beta_factor;  //!< product of number density and absorption cross-section
};

#endif /* WAVELENGTHINDEPENDENTMATERIAL_H */
