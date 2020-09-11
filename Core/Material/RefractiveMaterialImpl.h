// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Material/RefractiveMaterialImpl.h
//! @brief     Defines class RefractiveMaterialImpl.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_CORE_MATERIAL_REFRACTIVEMATERIALIMPL_H
#define BORNAGAIN_CORE_MATERIAL_REFRACTIVEMATERIALIMPL_H

#include "Core/Material/MagneticMaterialImpl.h"
#include "Core/Material/Material.h"

//! Material implementation based on refractive coefficiencts (valid for one wavelength value only)
//! @ingroup materials

class BA_CORE_API_ RefractiveMaterialImpl : public MagneticMaterialImpl
{
public:
    friend BA_CORE_API_ Material HomogeneousMaterial(const std::string&, double, double, kvector_t);

    virtual ~RefractiveMaterialImpl() = default;

    //! Returns pointer to a copy of material
    RefractiveMaterialImpl* clone() const override;

    //! Returns refractive index
    //! For this particular implementation returned value does not depend
    //! on passed wavelength
    complex_t refractiveIndex(double wavelength) const override;

    //! Returns squared refractive index.
    //! For this particular implementation returned value does not depend
    //! on passed wavelength.
    complex_t refractiveIndex2(double wavelength) const override;

    //! Returns underlying material data
    complex_t materialData() const override;

    //! Returns type of material implementation
    MATERIAL_TYPES typeID() const override { return MATERIAL_TYPES::RefractiveMaterial; }

    //! Returns (\f$ \pi/\lambda^2 \f$ - sld), sld (in \f$nm^{-2}\f$) being the scattering length
    //! density. If the wavelength associated with passed wavevector is different from the one
    //! associated with refractive coefficients used during the object construction,
    //! provided result is inconsistent.
    complex_t scalarSubtrSLD(const WavevectorInfo& wavevectors) const override;

    //! Prints object data
    void print(std::ostream& ostr) const override;

private:
    RefractiveMaterialImpl(const std::string& name, double delta, double beta,
                           kvector_t magnetization);

    double
        m_delta;   //!< \f$\delta\f$ coefficient for refractive index \f$n = 1 - \delta + i \beta\f$
    double m_beta; //!< \f$\beta\f$ coefficient for refractive index \f$n = 1 - \delta + i \beta\f$
};

#endif // BORNAGAIN_CORE_MATERIAL_REFRACTIVEMATERIALIMPL_H
