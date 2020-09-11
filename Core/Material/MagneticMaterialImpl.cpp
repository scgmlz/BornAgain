// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Material/MagneticMaterialImpl.cpp
//! @brief     Implements magnetic material base implementation.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Core/Material/MagneticMaterialImpl.h"
#include "Core/Basics/PhysicalConstants.h"
#include "Core/Material/MaterialUtils.h"
#include "Core/Vector/Transform3D.h"
#include "Core/Vector/WavevectorInfo.h"
#include <memory>

using PhysConsts::gamma_n;
using PhysConsts::mu_B;
using PhysConsts::r_e;
// The factor 1e-18 is here to have unit: m/A*nm^-2
constexpr double magnetization_prefactor = (gamma_n * r_e / 2.0 / mu_B) * 1e-18;

namespace
{
cvector_t OrthogonalToBaseVector(cvector_t base, const kvector_t vector)
{
    if (base.mag2() == 0.0)
        return cvector_t{};
    cvector_t projection = (base.dot(vector) / base.mag2()) * base;
    return vector.complex() - projection;
}
} // namespace

MagneticMaterialImpl::MagneticMaterialImpl(const std::string& name, kvector_t magnetization)
    : BaseMaterialImpl(name), m_magnetization(magnetization)
{
}

MagneticMaterialImpl* MagneticMaterialImpl::inverted() const
{
    std::string name = isScalarMaterial() ? getName() : getName() + "_inv";
    std::unique_ptr<MagneticMaterialImpl> result(this->clone());
    result->setMagnetization(-magnetization());
    return result.release();
}

bool MagneticMaterialImpl::isScalarMaterial() const
{
    return m_magnetization == kvector_t{};
}

bool MagneticMaterialImpl::isMagneticMaterial() const
{
    return !isScalarMaterial();
}

kvector_t MagneticMaterialImpl::magnetization() const
{
    return m_magnetization;
}

Eigen::Matrix2cd MagneticMaterialImpl::polarizedSubtrSLD(const WavevectorInfo& wavevectors) const
{
    cvector_t mag_ortho = OrthogonalToBaseVector(wavevectors.getQ(), m_magnetization);
    complex_t unit_factor = scalarSubtrSLD(wavevectors);
    return MaterialUtils::MagnetizationCorrection(unit_factor, magnetization_prefactor, mag_ortho);
}

MagneticMaterialImpl* MagneticMaterialImpl::rotatedMaterial(const Transform3D& transform) const
{
    kvector_t transformed_field = transform.transformed(m_magnetization);
    std::unique_ptr<MagneticMaterialImpl> result(this->clone());
    result->setMagnetization(transformed_field);
    return result.release();
}
