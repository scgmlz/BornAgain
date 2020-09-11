// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Material/MaterialBySLDImpl.h
//! @brief     Defines class MaterialBySLDImpl.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_CORE_MATERIAL_MATERIALBYSLDIMPL_H
#define BORNAGAIN_CORE_MATERIAL_MATERIALBYSLDIMPL_H

#include "Core/Material/MagneticMaterialImpl.h"
#include "Core/Material/Material.h"
#include "Core/Material/MaterialFactoryFuncs.h"

//! Material implementation based on wavelength-independent data (valid for a range of wavelengths)
//! @ingroup materials

class BA_CORE_API_ MaterialBySLDImpl : public MagneticMaterialImpl
{
public:
    friend BA_CORE_API_ Material MaterialBySLD(const std::string& name, double sld_real,
                                               double sld_imag, kvector_t magnetization);

    virtual ~MaterialBySLDImpl() = default;

    //! Returns pointer to a copy of material
    MaterialBySLDImpl* clone() const override;

    //! Returns refractive index
    complex_t refractiveIndex(double wavelength) const override;

    //! Returns squared refractive index
    complex_t refractiveIndex2(double wavelength) const override;

    //! Returns underlying material data
    complex_t materialData() const override;

    //! Returns type of material implementation
    MATERIAL_TYPES typeID() const override { return MATERIAL_TYPES::MaterialBySLD; }

    //! Returns (\f$ \pi/\lambda^2 \f$ - sld), sld (in \f$nm^{-2}\f$) being the scattering length
    //! density
    complex_t scalarSubtrSLD(const WavevectorInfo& wavevectors) const override;

    //! Prints object data
    void print(std::ostream& ostr) const override;

private:
    //! Constructs a wavelength-independent material with a given complex-valued
    //! scattering length density (SLD). SLD units are \f$ nm^{-2} \f$.
    MaterialBySLDImpl(const std::string& name, double sld_real, double sld_imag,
                      kvector_t magnetization);
    //! Returns the scattering length density
    complex_t sld() const;

    double m_sld_real; //!< complex-valued scattering length density
    double m_sld_imag; //!< imaginary part of scattering length density (negative by default)
};

#endif // BORNAGAIN_CORE_MATERIAL_MATERIALBYSLDIMPL_H
