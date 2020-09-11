// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Material/BaseMaterialImpl.h
//! @brief     Defines basic material implementation interface.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_CORE_MATERIAL_BASEMATERIALIMPL_H
#define BORNAGAIN_CORE_MATERIAL_BASEMATERIALIMPL_H

#include "Core/Basics/Complex.h"
#include "Core/Vector/EigenCore.h"
#include "Core/Vector/Vectors3D.h"

class Transform3D;
class WavevectorInfo;

enum class MATERIAL_TYPES { InvalidMaterialType = -1, RefractiveMaterial = 0, MaterialBySLD };

//! Interface for material implementation classes.
//! Inherited by MagneticMaterialImpl, which has further children.
//! @ingroup materials

class BA_CORE_API_ BaseMaterialImpl
{
public:
    //! Constructs basic material with name
    BaseMaterialImpl(const std::string& name) : m_name(name) {}

    virtual ~BaseMaterialImpl() = default;

    //! Returns pointer to a copy of material
    virtual BaseMaterialImpl* clone() const = 0;

    //! Constructs a material with inverted magnetization
    virtual BaseMaterialImpl* inverted() const = 0;

    //! Returns refractive index.
    virtual complex_t refractiveIndex(double wavelength) const = 0;

    //! Returns squared refractive index.
    virtual complex_t refractiveIndex2(double wavelength) const = 0;

    //! Indicates whether the interaction with the material is scalar.
    //! This means that different polarization states will be diffracted equally
    virtual bool isScalarMaterial() const = 0;

    virtual bool isMagneticMaterial() const = 0;

    //! Returns the magnetization (in A/m)
    virtual kvector_t magnetization() const = 0;

    //! Returns underlying material data
    virtual complex_t materialData() const = 0;

    //! Returns type of material implementation
    virtual MATERIAL_TYPES typeID() const = 0;

    //! Returns (\f$ \pi/\lambda^2 \f$ - sld), sld being the scattering length density
    virtual complex_t scalarSubtrSLD(const WavevectorInfo& wavevectors) const = 0;

    //! Returns (\f$ \pi/\lambda^2 \f$ - sld) matrix with magnetization corrections
    virtual Eigen::Matrix2cd polarizedSubtrSLD(const WavevectorInfo& wavevectors) const = 0;

    virtual BaseMaterialImpl* rotatedMaterial(const Transform3D& transform) const = 0;

    //! Prints object data
    virtual void print(std::ostream& ostr) const = 0;

    //! Returns name of the material
    const std::string& getName() const { return m_name; }

private:
    const std::string m_name;
};

#endif // BORNAGAIN_CORE_MATERIAL_BASEMATERIALIMPL_H
