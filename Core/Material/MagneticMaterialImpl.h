// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Material/MagneticMaterialImpl.h
//! @brief     Defines magnetic material base implementation.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2017
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke, D. Yurov
//
// ************************************************************************** //

#ifndef MAGNETICMATERIALIMPL_H_
#define MAGNETICMATERIALIMPL_H_

#include "BaseMaterialImpl.h"
#include "Vectors3D.h"
#include "Complex.h"
#include "EigenCore.h"

class Transform3D;
class WavevectorInfo;

//! Basic implementation for magnetized material.
//! Incorporates data and methods required to handle material magnetization.
//! @ingroup materials

class BA_CORE_API_ MagneticMaterialImpl : public BaseMaterialImpl
{
public:
    //! Constructs basic material with name and magnetization
    MagneticMaterialImpl(const std::string& name, kvector_t magnetization);

    virtual ~MagneticMaterialImpl() = default;

    //! Returns pointer to a copy of material
    virtual MagneticMaterialImpl* clone() const override = 0;

    //! Constructs a material with inverted magnetization
    virtual MagneticMaterialImpl* inverted() const override final;

    //! Indicates whether the interaction with the material is scalar.
    //! This means that different polarization states will be diffracted equally
    virtual bool isScalarMaterial() const override final;

    virtual bool isMagneticMaterial() const override final;

    //! Returns the magnetization (in A/m)
    virtual kvector_t magnetization() const override final;

    //! Returns (\f$ \pi/\lambda^2 \f$ - sld) matrix with magnetization corrections
    virtual Eigen::Matrix2cd polarizedSubtrSLD(const WavevectorInfo& wavevectors) const override final;

    virtual MagneticMaterialImpl* transformedMaterial(const Transform3D& transform) const override final;

private:
    void setMagnetization(kvector_t magnetization)
    {
        m_magnetization = magnetization;
    }

    kvector_t m_magnetization; //!< magnetization
};

#endif /* MAGNETICMATERIALIMPL_H_ */
