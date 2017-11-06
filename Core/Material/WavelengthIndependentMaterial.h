// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Material/WavelengthIndependentMaterial.h
//! @brief     Defines class WavelengthIndependentMaterial.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2017
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke, D. Yurov
//
// ************************************************************************** //

#ifndef WAVELENGTHINDEPENDENTMATERIAL_H_
#define WAVELENGTHINDEPENDENTMATERIAL_H_

#include "MagneticMaterialImpl.h"
#include "Material.h"

//! Material implementation based on wavelength-independent data (valid for a range of wavelengths)
//! @ingroup materials

class BA_CORE_API_ WavelengthIndependentMaterial : public MagneticMaterialImpl
{
public:
    friend BA_CORE_API_ Material MaterialBySLD(const std::string&, double, double, kvector_t);

    virtual ~WavelengthIndependentMaterial();

    //! Returns pointer to a copy of material
    virtual WavelengthIndependentMaterial* clone() const override;

    //! Returns refractive index
    virtual complex_t refractiveIndex(double wavelength) const override;

    //! Returns squared refractive index
    virtual complex_t refractiveIndex2(double wavelength) const override;

    //! Returns underlying material data
    virtual complex_t materialData() const override;

    //! Returns type of material implementation
    virtual MATERIAL_TYPES typeID() const override
    {
        return MATERIAL_TYPES::WavelengthIndependentMaterial;
    }

    //! Returns (\f$ \pi/\lambda^2 \f$ - sld), sld (in \f$nm^{-2}\f$) being the scattering length density
    virtual complex_t scalarSubtrSLD(const WavevectorInfo& wavevectors) const override;

    //! Prints object data
    virtual void print(std::ostream &ostr) const override;

private:
    WavelengthIndependentMaterial(const std::string& name, double sld, double abs_term,
                                  kvector_t magnetization);

    double m_sld; //!< product of number density and coherent scattering length
                  //!< (scattering length density)
    double m_abs_term;  //!< product of number density and
                        //!< absorption cross-section normalized to wavelength
};

#endif /* WAVELENGTHINDEPENDENTMATERIAL_H_ */
