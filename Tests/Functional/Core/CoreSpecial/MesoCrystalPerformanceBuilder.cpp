// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/Core/CoreSpecial/MesoCrystalPerformanceBuilder.cpp
//! @brief     Defines MesoCrystalPerformanceBuilder class.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "MesoCrystalPerformanceBuilder.h"
#include "Crystal.h"
#include "FormFactorCylinder.h"
#include "FormFactorDecoratorDebyeWaller.h"
#include "FormFactorSphereLogNormalRadius.h"
#include "ISelectionRule.h"
#include "Lattice.h"
#include "Layer.h"
#include "LayerRoughness.h"
#include "MaterialFactoryFuncs.h"
#include "MesoCrystal.h"
#include "MultiLayer.h"
#include "Particle.h"
#include "ParticleComposition.h"
#include "ParticleLayout.h"
#include "Units.h"

using Units::nm;
using Units::deg;

namespace
{
Lattice createLattice(double a, double c);
}

MesoCrystalPerformanceBuilder::MesoCrystalPerformanceBuilder()
    : m_lattice_length_a(12.45 * nm), m_lattice_length_c(31.0 * nm),
      m_nanoparticle_radius(5.0 * nm), m_sigma_nanoparticle_radius(0.3 * nm),
      m_meso_height(200 * nm), m_meso_radius(800 * nm), m_sigma_meso_height(20.0 * nm),
      m_sigma_meso_radius(20.0 * nm), m_sigma_lattice_length_a(0.5 * nm), m_roughness(6.0 * nm),
      m_surface_filling_ratio(0.25), m_phi_start(0.0 * deg), m_phi_stop(360.0 * deg),
      m_phi_rotation_steps(5), m_tilt_start(0.0 * deg), m_tilt_stop(1.0 * deg), m_tilt_steps(1)
{
}

MesoCrystalPerformanceBuilder::~MesoCrystalPerformanceBuilder() = default;

MultiLayer* MesoCrystalPerformanceBuilder::buildSample() const
{
    double surface_density = m_surface_filling_ratio / M_PI / m_meso_radius / m_meso_radius;
    complex_t n_particle(1.0 - 2.84e-5, 4.7e-7);
    auto avg_n_squared_meso = 0.7886 * n_particle * n_particle + 0.2114;
    auto n_avg
        = std::sqrt(m_surface_filling_ratio * avg_n_squared_meso + 1.0 - m_surface_filling_ratio);
    auto n_particle_adapted = std::sqrt(n_avg * n_avg + n_particle * n_particle - 1.0);
    auto particle_material = HomogeneousMaterial("nanoparticle", n_particle_adapted);

    FormFactorCylinder ff_cyl(m_meso_radius, m_meso_height);
    FormFactorDecoratorDebyeWaller ff_meso(ff_cyl, m_sigma_meso_height * m_sigma_meso_height / 2.0,
                                           m_sigma_meso_radius * m_sigma_meso_radius / 2.0);

    auto multi_layer = new MultiLayer;

    auto air_material = HomogeneousMaterial("Air", 0.0, 0.0);
    auto substrate_material = HomogeneousMaterial("Substrate", 7.57e-6, 1.73e-7);
    auto average_layer_material = HomogeneousMaterial("AverageLayer", n_avg);
    Layer air_layer(air_material);
    Layer avg_layer(average_layer_material, m_meso_height);
    Layer substrate_layer(substrate_material);
    ParticleLayout particle_decoration;

    auto mesocrystal = createMeso(particle_material, ff_meso);

    double dphi = (m_phi_stop - m_phi_start) / m_phi_rotation_steps;
    double dtilt = (m_tilt_stop - m_tilt_start) / m_tilt_steps;

    for (int i_tilt = 0; i_tilt < m_tilt_steps; ++i_tilt) {
        for (int i_phi = 0; i_phi < m_phi_rotation_steps; ++i_phi) {

            double phi = m_phi_start + i_phi * dphi;
            RotationZ rotZ(phi);
            double tilt = m_tilt_start + i_tilt * dtilt;
            RotationX rotX(tilt);
            mesocrystal->setRotation(rotZ);
            mesocrystal->rotate(rotX);
            particle_decoration.addParticle(*mesocrystal.get(), 1.0,
                                            kvector_t(0, 0, -m_meso_height));
        }
    }

    particle_decoration.setTotalParticleSurfaceDensity(surface_density);
    avg_layer.addLayout(particle_decoration);

    LayerRoughness roughness(m_roughness, 0.3, 500.0 * nm);

    multi_layer->addLayer(air_layer);
    multi_layer->addLayer(avg_layer);
    multi_layer->addLayerWithTopRoughness(substrate_layer, roughness);

    return multi_layer;
}

std::unique_ptr<MesoCrystal>
MesoCrystalPerformanceBuilder::createMeso(Material material, const IFormFactor& form_factor) const
{

    auto lattice = createLattice(m_lattice_length_a, m_lattice_length_c);
    auto bas_a = lattice.getBasisVectorA();
    auto bas_b = lattice.getBasisVectorB();
    auto bas_c = lattice.getBasisVectorC();

    double scale_param = std::sqrt(
        std::log(std::pow(m_sigma_nanoparticle_radius / m_nanoparticle_radius, 2) + 1.0));
    Particle particle(material,
                      FormFactorSphereLogNormalRadius(m_nanoparticle_radius, scale_param, 10));

    kvector_t position_0(0.0, 0.0, 0.0);
    auto position_1 = 1.0 / 3.0 * (2.0 * bas_a + bas_b + bas_c);
    auto position_2 = 1.0 / 3.0 * (bas_a + 2.0 * bas_b + 2.0 * bas_c);
    std::vector<kvector_t> pos_vector = {position_0, position_1, position_2};
    ParticleComposition basis;
    basis.addParticles(particle, pos_vector);
    Crystal npc(basis, lattice);
    double dw_factor = m_sigma_lattice_length_a * m_sigma_lattice_length_a / 6.0;
    npc.setDWFactor(dw_factor);

    return std::make_unique<MesoCrystal>(npc, form_factor);
}

namespace
{

Lattice createLattice(double a, double c)
{
    Lattice result = Lattice::createHexagonalLattice(a, c);
    result.setSelectionRule(SimpleSelectionRule(-1, 1, 1, 3));
    return result;
}
}
