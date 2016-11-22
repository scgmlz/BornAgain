// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Material/HomogeneousMagneticMaterial.cpp
//! @brief     Implements class HomogeneousMagneticMaterial.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "HomogeneousMagneticMaterial.h"
#include "Transform3D.h"

const double HomogeneousMagneticMaterial::m_magnetic_prefactor = -2.91042993836710484e-3;

HomogeneousMagneticMaterial::HomogeneousMagneticMaterial(
        const std::string& name, const complex_t refractive_index,
        const kvector_t magnetic_field)
: HomogeneousMaterial(name, refractive_index)
, m_magnetic_field(magnetic_field)
{
    initializePrivateMemebers();
}

HomogeneousMagneticMaterial::HomogeneousMagneticMaterial(
        const std::string& name, double refractive_index_delta,
        double refractive_index_beta, const kvector_t magnetic_field)
    : HomogeneousMaterial(name, refractive_index_delta, refractive_index_beta)
    , m_magnetic_field(magnetic_field)
{
    initializePrivateMemebers();
}

HomogeneousMagneticMaterial* HomogeneousMagneticMaterial::clone() const
{
    return new HomogeneousMagneticMaterial(getName(), getRefractiveIndex(), getMagneticField());
}

HomogeneousMagneticMaterial* HomogeneousMagneticMaterial::cloneInverted() const
{
    return new HomogeneousMagneticMaterial(
        getName()+"_inv", getRefractiveIndex(), -getMagneticField());
}

Eigen::Matrix2cd HomogeneousMagneticMaterial::getScatteringMatrix(
        double k_mag2) const
{
    Eigen::Matrix2cd result;
    double factor = m_magnetic_prefactor/k_mag2;
    complex_t unit_factor = m_refractive_index*m_refractive_index;
    result = unit_factor*m_unit_matrix
            + factor*m_pauli_operator[0]*m_magnetic_field[0]
            + factor*m_pauli_operator[1]*m_magnetic_field[1]
            + factor*m_pauli_operator[2]*m_magnetic_field[2];
    return result;
}

const IMaterial* HomogeneousMagneticMaterial::createTransformedMaterial(
        const Transform3D& transform) const
{
    kvector_t mag_field_transformed = transform.transformed(m_magnetic_field);
    return new HomogeneousMagneticMaterial(getName(), getRefractiveIndex(),
            mag_field_transformed);
}

void HomogeneousMagneticMaterial::initializePrivateMemebers()
{
    m_unit_matrix.setIdentity();
    m_pauli_operator.clear();
    Eigen::Matrix2cd sigma;
    sigma(0,0) = 0.0;
    sigma(0,1) = 1.0;
    sigma(1,0) = 1.0;
    sigma(1,1) = 0.0;
    m_pauli_operator.push_back(sigma);
    sigma(0,0) = 0.0;
    sigma(0,1) = complex_t(0.0, -1.0);
    sigma(1,0) = complex_t(0.0, 1.0);
    sigma(1,1) = 0.0;
    m_pauli_operator.push_back(sigma);
    sigma(0,0) = 1.0;
    sigma(0,1) = 0.0;
    sigma(1,0) = 0.0;
    sigma(1,1) = -1.0;
    m_pauli_operator.push_back(sigma);
}
