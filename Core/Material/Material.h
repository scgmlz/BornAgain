// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Material/Material.h
//! @brief     Defines and implements class Material.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_CORE_MATERIAL_MATERIAL_H
#define BORNAGAIN_CORE_MATERIAL_MATERIAL_H

#include "Core/Basics/Complex.h"
#include "Core/Material/BaseMaterialImpl.h"
#include "Core/Vector/EigenCore.h"
#include "Core/Vector/Vectors3D.h"
#include <memory>
#include <vector>

class Transform3D;
class WavevectorInfo;

//! A wrapper for underlying material implementation
//! @ingroup materials

class Material
{
public:
    //! Material copy-constructor
    Material(const Material& material);

    //! Material move-constructor
    Material(Material&& material) = default;

#ifndef SWIG
    //! Creates material with particular material implementation
    Material(std::unique_ptr<BaseMaterialImpl> material_impl);
#endif // SWIG

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

#ifndef SWIG
    //! Returns the type of underlying material implementation
    MATERIAL_TYPES typeID() const;
#endif // SWIG

    //! Get the magnetization (in A/m)
    kvector_t magnetization() const;

    //! Returns underlying material data. The units of returned values
    //! are the same as the ones passed to material factory functions
    complex_t materialData() const;

    //! Returns true if material underlying data is nullptr
    bool isEmpty() const { return !m_material_impl; }

    //! Returns true if material has refractive index of (1.0, 0.0)
    //! and zero magnetization.
    bool isDefaultMaterial() const;

    //! Returns (\f$ \pi/\lambda^2 \f$ - sld), sld (in \f$nm^{-2}\f$) being the scattering length
    //! density
    complex_t scalarSubtrSLD(const WavevectorInfo& wavevectors) const;

#ifndef SWIG
    //! Returns (\f$ \pi/\lambda^2 \f$ - sld) matrix with magnetization corrections
    Eigen::Matrix2cd polarizedSubtrSLD(const WavevectorInfo& wavevectors) const;
#endif

    Material rotatedMaterial(const Transform3D& transform) const;

    friend std::ostream& operator<<(std::ostream& ostr, const Material& mat);

private:
    std::unique_ptr<BaseMaterialImpl> m_material_impl;
};

//! Comparison operator for material wrapper (equality check)
bool operator==(const Material& left, const Material& right);

//! Comparison operator for material wrapper (inequality check)
bool operator!=(const Material& left, const Material& right);

#endif // BORNAGAIN_CORE_MATERIAL_MATERIAL_H
