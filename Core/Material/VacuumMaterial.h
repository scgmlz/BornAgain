// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Material/VacuumMaterial.h
//! @brief     Defines class VacuumMaterial.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2017
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke, D. Yurov
//
// ************************************************************************** //

#ifndef VACUUMMATERIAL_H_
#define VACUUMMATERIAL_H_

#include "BaseMaterialImpl.h"
#include "Material.h"

//! Default (vacuum) material implementation
//! @ingroup materials

class BA_CORE_API_ VacuumMaterial : public BaseMaterialImpl
{
public:
    friend BA_CORE_API_ Material createVacuumMaterial();

    virtual ~VacuumMaterial() = default;

    //! Returns pointer to a copy of material
    virtual VacuumMaterial* clone() const override final;

    //! Constructs a material with inverted magnetization
    virtual VacuumMaterial* inverted() const override final
    {
        return this->clone();
    }

    //! Returns refractive index \f$ n = (1, 0)\f$
    virtual complex_t refractiveIndex(double) const override final
    {
        return complex_t(0.0, 0.0);
    }

    //! Returns squared refractive index \f$ n^2 = (1, 0)\f$.
    virtual complex_t refractiveIndex2(double) const override final
    {
        return complex_t(0.0, 0.0);
    }

    //! Returns underlying material data (zero value)
    virtual complex_t materialData() const override final {
        return complex_t(0.0, 0.0);
    }

    //! Returns type of material implementation
    virtual MATERIAL_TYPES typeID() const override final
    {
        return MATERIAL_TYPES::VacuumMaterial;
    }

    virtual bool isScalarMaterial() const override final
    {
        return true;
    }

    virtual bool isMagneticMaterial() const override final
    {
        return false;
    }

    //! Returns the magnetization (in A/m)
    virtual kvector_t magnetization() const override final
    {
        return kvector_t{};
    };

    //! Returns (\f$ \pi/\lambda^2 \f$ - sld), sld (in \f$nm^{-2}\f$) being the scattering length density.
    //! In particular case returns just \f$ \pi/\lambda^2 \f$.
    virtual complex_t scalarSubtrSLD(const WavevectorInfo& wavevectors) const override final;

    //! Returns (\f$ \pi/\lambda^2 \f$ - sld) matrix with magnetization corrections
    //! In particular case returns just \f$ \pi/\lambda^2 \f$.
    virtual Eigen::Matrix2cd
    polarizedSubtrSLD(const WavevectorInfo& wavevectors) const override final;

    virtual VacuumMaterial* transformedMaterial(const Transform3D&) const override final
    {
        return this->clone();
    }

    //! Prints object data
    virtual void print(std::ostream &ostr) const override final;

private:
    VacuumMaterial(const std::string& name);
};

#endif /* VACUUMMATERIAL_H_ */
