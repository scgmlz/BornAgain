// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Material/MaterialUtils.cpp
//! @brief     Implements functions in namespace MaterialUtils
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Core/Material/MaterialUtils.h"
#include "Core/Basics/PhysicalConstants.h"
#include "Core/Material/Material.h"

using PhysConsts::g_factor_n;
using PhysConsts::h_bar;
using PhysConsts::m_n;
using PhysConsts::mu_N;
// The factor 1e-18 is here to have unit: 1/T*nm^-2
constexpr double magnetic_prefactor = (m_n * g_factor_n * mu_N / h_bar / h_bar) * 1e-18;

// Unit 2x2 matrix
const Eigen::Matrix2cd Unit_Matrix(Eigen::Matrix2cd::Identity());

// Imaginary unit
namespace
{
const complex_t I(0, 1);

// Pauli matrices
const Eigen::Matrix2cd Pauli_X((Eigen::Matrix2cd() << 0, 1, 1, 0).finished());
const Eigen::Matrix2cd Pauli_Y((Eigen::Matrix2cd() << 0, -I, I, 0).finished());
const Eigen::Matrix2cd Pauli_Z((Eigen::Matrix2cd() << 1, 0, 0, -1).finished());
} // namespace

template <typename T>
Eigen::Matrix2cd MaterialUtils::MagnetizationCorrection(complex_t unit_factor,
                                                        double magnetic_factor,
                                                        BasicVector3D<T> polarization)
{
    Eigen::Matrix2cd result =
        unit_factor * Unit_Matrix
        + magnetic_factor
              * (Pauli_X * polarization[0] + Pauli_Y * polarization[1] + Pauli_Z * polarization[2]);
    return result;
}
template Eigen::Matrix2cd MaterialUtils::MagnetizationCorrection(complex_t unit_factor,
                                                                 double magnetic_factor,
                                                                 kvector_t polarization);
template Eigen::Matrix2cd MaterialUtils::MagnetizationCorrection(complex_t unit_factor,
                                                                 double magnetic_factor,
                                                                 cvector_t polarization);

complex_t MaterialUtils::ScalarReducedPotential(complex_t n, kvector_t k, double n_ref)
{
    return n * n - n_ref * n_ref * k.sin2Theta();
}

Eigen::Matrix2cd MaterialUtils::PolarizedReducedPotential(complex_t n, kvector_t b_field,
                                                          kvector_t k, double n_ref)
{
    Eigen::Matrix2cd result;
    double factor = magnetic_prefactor / k.mag2();
    complex_t unit_factor = ScalarReducedPotential(n, k, n_ref);
    return MagnetizationCorrection(unit_factor, factor, b_field);
}

MATERIAL_TYPES MaterialUtils::checkMaterialTypes(const std::vector<const Material*>& materials)
{
    MATERIAL_TYPES result = MATERIAL_TYPES::RefractiveMaterial;
    bool isDefault = true;
    for (const Material* mat : materials) {
        if (isDefault) {
            result = mat->typeID();
            isDefault = mat->isDefaultMaterial();
            continue;
        }
        if (mat->typeID() != result && !mat->isDefaultMaterial())
            return MATERIAL_TYPES::InvalidMaterialType;
    }
    return result;
}
