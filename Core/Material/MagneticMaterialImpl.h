// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Material/MagneticMaterialImpl.h
//! @brief     Defines magnetic material base implementation.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_CORE_MATERIAL_MAGNETICMATERIALIMPL_H
#define BORNAGAIN_CORE_MATERIAL_MAGNETICMATERIALIMPL_H

#include "Core/Basics/Complex.h"
#include "Core/Material/BaseMaterialImpl.h"
#include "Core/Vector/EigenCore.h"
#include "Core/Vector/Vectors3D.h"

class Transform3D;
class WavevectorInfo;

//! Basic implementation for magnetized material.
//! Inherited by RefractiveMaterialImpl and MaterialBySLDImpl.
//! Incorporates data and methods required to handle material magnetization.
//! @ingroup materials

class BA_CORE_API_ MagneticMaterialImpl : public BaseMaterialImpl
{
public:
    //! Constructs basic material with name and magnetization
    MagneticMaterialImpl(const std::string& name, kvector_t magnetization);

    virtual ~MagneticMaterialImpl() = default;

    //! Returns pointer to a copy of material
    MagneticMaterialImpl* clone() const override = 0;

    //! Constructs a material with inverted magnetization
    MagneticMaterialImpl* inverted() const override final;

    //! Indicates whether the interaction with the material is scalar.
    //! This means that different polarization states will be diffracted equally
    bool isScalarMaterial() const override final;

    bool isMagneticMaterial() const override final;

    //! Returns the magnetization (in A/m)
    kvector_t magnetization() const override final;

    //! Returns (\f$ \pi/\lambda^2 \f$ - sld) matrix with magnetization corrections
    Eigen::Matrix2cd polarizedSubtrSLD(const WavevectorInfo& wavevectors) const override final;

    MagneticMaterialImpl* rotatedMaterial(const Transform3D& transform) const override final;

private:
    void setMagnetization(kvector_t magnetization) { m_magnetization = magnetization; }

    kvector_t m_magnetization; //!< magnetization
};

#endif // BORNAGAIN_CORE_MATERIAL_MAGNETICMATERIALIMPL_H
