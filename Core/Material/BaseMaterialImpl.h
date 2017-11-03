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

#ifndef IMATERIALIMPL_H_
#define IMATERIALIMPL_H_

#include "INamed.h"
#include "Vectors3D.h"
#include "Complex.h"
#include "EigenCore.h"

class Transform3D;
class WavevectorInfo;

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

    //! Returns material type id
    virtual unsigned typeID() const = 0;

    //! Returns (\f$ \pi/\lambda^2 \f$ - sld), sld being the scattering length density
    virtual complex_t scalarSubtrSLD(const WavevectorInfo& wavevectors) const = 0;

    //! Returns (\f$ \pi/\lambda^2 \f$ - sld) matrix with magnetization corrections
    virtual Eigen::Matrix2cd polarizedSubtrSLD(const WavevectorInfo& wavevectors) const = 0;

    virtual BaseMaterialImpl* transformedMaterial(const Transform3D& transform) const = 0;

    //! Prints object data
    virtual void print(std::ostream &ostr) const = 0;

    //! Returns unique identifier of material implementation type
    //! (the same as typeID method, but works without constructing object).
    template <class T> static unsigned g_typeID();

private:
    template <class T> struct MaterialTag {
        static char ID_storage;
        static const void* const ID;
    };
};

template <typename T> char BaseMaterialImpl::MaterialTag<T>::ID_storage;
template <typename T>
const void* const BaseMaterialImpl::MaterialTag<T>::ID
    = &BaseMaterialImpl::MaterialTag<T>::ID_storage;

template <class T> unsigned BaseMaterialImpl::g_typeID()
{
    static const unsigned type_id = static_cast<unsigned>(reinterpret_cast<intptr_t>(MaterialTag<T>::ID));
    return type_id;
}

#endif /* IMATERIALIMPL_H_ */
