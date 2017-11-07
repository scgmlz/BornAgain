// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Material/BaseMaterialImpl.h
//! @brief     Defines basic material implementation interface.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2017
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke, D. Yurov
//
// ************************************************************************** //

#ifndef BASEMATERIALIMPL_H_
#define BASEMATERIALIMPL_H_

#include "INamed.h"
#include "Vectors3D.h"
#include "Complex.h"
#include "EigenCore.h"

class Transform3D;
class WavevectorInfo;

enum class MATERIAL_TYPES {
    RefractiveMaterial = 0,
    MaterialBySLD
};

//! @ingroup materials

class BA_CORE_API_ BaseMaterialImpl : public INamed
{
public:
    //! Constructs basic material with name
    BaseMaterialImpl(const std::string& name) : INamed(name) {}

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

    virtual BaseMaterialImpl* transformedMaterial(const Transform3D& transform) const = 0;

    //! Prints object data
    virtual void print(std::ostream &ostr) const = 0;
};

#endif /* BASEMATERIALIMPL_H_ */
