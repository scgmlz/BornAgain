// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Material/Material.h
//! @brief     Defines and implements class Material.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef MATERIAL_H_
#define MATERIAL_H_

#include "Complex.h"
#include "Vectors3D.h"
#include "EigenCore.h"
#include "BaseMaterialImpl.h"
#include <vector>
#include <memory>

class Transform3D;
class WavevectorInfo;

//! A wrapper for underlying material implementation
//! @ingroup materials

class BA_CORE_API_ Material
{
public:
    //! Material copy-constructor
    Material(const Material& material);

    //! Material move-constructor
    Material(Material&& material) = default;

#ifndef SWIG
    //! Creates material with particular material implementation
    Material(std::unique_ptr<BaseMaterialImpl> material_impl);
#endif //SWIG

    //! Material copy assignment
    Material& operator=(const Material& other);

    //! Material move assignment
    Material& operator=(Material&& other) = default;

    //! Constructs a material with inverted magnetization
    Material inverted() const;

    //! Returns refractive index
    complex_t refractiveIndex(double wavelength) const;

    //! Returns squared refractive index
    complex_t refractiveIndex2(double wavelength) const;

    //! Indicates whether the interaction with the material is scalar.
    //! This means that different polarization states will be diffracted equally
    bool isScalarMaterial() const;

    bool isMagneticMaterial() const;

    //! Returns the name of material
    std::string getName() const;

    //! Returns hash code of underlying material implementation
    size_t typeID() const;

    //! Get the magnetization (in A/m)
    kvector_t magnetization() const;

    //! Returns underlying material data
    complex_t materialData() const;

    //! Returns true if material underlying data is nullptr
    bool isEmpty() const {return !m_material_impl;}

    //! Returns (\f$ \pi/\lambda^2 \f$ - sld), sld (in \f$nm^{-2}\f$) being the scattering length density
    complex_t scalarSubtrSLD(const WavevectorInfo& wavevectors) const;

#ifndef SWIG
    //! Returns (\f$ \pi/\lambda^2 \f$ - sld) matrix with magnetization corrections
    Eigen::Matrix2cd polarizedSubtrSLD(const WavevectorInfo& wavevectors) const;
#endif

    Material transformedMaterial(const Transform3D& transform) const;

    friend BA_CORE_API_ std::ostream& operator<<(
            std::ostream& ostr, const Material& mat);

private:
    std::unique_ptr<BaseMaterialImpl> m_material_impl;
};

//! Comparison operator for material wrapper (equality check)
BA_CORE_API_ bool operator==(const Material& left, const Material& right);

//! Comparison operator for material wrapper (inequality check)
BA_CORE_API_ bool operator!=(const Material& left, const Material& right);

#endif /* MATERIAL_H_ */
