// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Multilayer/Slice.cpp
//! @brief     Implements class Slice.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Core/Multilayer/Slice.h"
#include "Core/Material/MaterialUtils.h"
#include "Core/Multilayer/LayerRoughness.h"

Slice::Slice(double thickness, const Material& material)
    : m_thickness{thickness}, m_material{material}, m_B_field{}, mP_top_roughness{nullptr}
{
}

Slice::Slice(double thickness, const Material& material, const LayerRoughness& top_roughness)
    : m_thickness{thickness}, m_material{material}, m_B_field{}, mP_top_roughness{
                                                                     top_roughness.clone()}
{
}

Slice::Slice(const Slice& other)
    : m_thickness{other.m_thickness}, m_material{other.m_material}, m_B_field{other.m_B_field},
      mP_top_roughness{}
{
    if (other.mP_top_roughness) {
        mP_top_roughness.reset(other.mP_top_roughness->clone());
    }
}

Slice::Slice(Slice&& other)
    : m_thickness{other.m_thickness}, m_material{std::move(other.m_material)},
      m_B_field{other.m_B_field}, mP_top_roughness{std::move(other.mP_top_roughness)}
{
}

Slice& Slice::operator=(const Slice& other)
{
    m_thickness = other.m_thickness;
    m_material = other.m_material;
    m_B_field = other.m_B_field;
    if (other.mP_top_roughness) {
        mP_top_roughness.reset(other.mP_top_roughness->clone());
    }
    return *this;
}

Slice::~Slice() = default;

void Slice::setMaterial(const Material& material)
{
    m_material = material;
}

Material Slice::material() const
{
    return m_material;
}

double Slice::thickness() const
{
    return m_thickness;
}

const LayerRoughness* Slice::topRoughness() const
{
    return mP_top_roughness.get();
}

complex_t Slice::scalarReducedPotential(kvector_t k, double n_ref) const
{
    complex_t n = m_material.refractiveIndex(2.0 * M_PI / k.mag());
    return MaterialUtils::ScalarReducedPotential(n, k, n_ref);
}

Eigen::Matrix2cd Slice::polarizedReducedPotential(kvector_t k, double n_ref) const
{
    complex_t n = m_material.refractiveIndex(2.0 * M_PI / k.mag());
    return MaterialUtils::PolarizedReducedPotential(n, m_B_field, k, n_ref);
}

void Slice::initBField(kvector_t h_field, double b_z)
{
    m_B_field = Magnetic_Permeability * (h_field + m_material.magnetization());
    m_B_field.setZ(b_z);
}

void Slice::invertBField()
{
    m_B_field = -m_B_field;
}
