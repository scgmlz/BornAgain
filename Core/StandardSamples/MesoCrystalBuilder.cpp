// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/StandardSamples/MesoCrystalBuilder.cpp
//! @brief     Implements class MesoCrystalBuilder.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "MesoCrystalBuilder.h"
#include "Crystal.h"
#include "FormFactorCylinder.h"
#include "FormFactorDecoratorDebyeWaller.h"
#include "FormFactorSphereGaussianRadius.h"
#include "HomogeneousMaterial.h"
#include "ISelectionRule.h"
#include "Layer.h"
#include "LayerInterface.h"
#include "LayerRoughness.h"
#include "MathConstants.h"
#include "MesoCrystal.h"
#include "MultiLayer.h"
#include "Particle.h"
#include "ParticleComposition.h"
#include "ParticleLayout.h"
#include "RealParameter.h"
#include "Units.h"

MesoCrystalBuilder::MesoCrystalBuilder()
    : m_lattice_length_a(6.2091e+00 * Units::nanometer)
    , m_lattice_length_c(6.5677e+00 * Units::nanometer)
    , m_nanoparticle_radius(4.6976e+00 * Units::nanometer)
    , m_sigma_nanoparticle_radius(3.6720e-01 * Units::nanometer)
    , m_meso_height(1.1221e+02 * Units::nanometer)
    , m_meso_radius(9.4567e+02 * Units::nanometer)
    , m_sigma_meso_height(1.3310e+00 * Units::nanometer)
    , m_sigma_meso_radius(1.3863e+00 * Units::nanometer)
    , m_sigma_lattice_length_a(1.1601e+00 * Units::nanometer)
    , m_surface_filling_ratio(1.7286e-01)
    , m_roughness(12e+00 * Units::nanometer)
    , m_nphi_rotations(2)
{
    init_parameters();
}

void MesoCrystalBuilder::init_parameters()
{
    registerParameter("meso_radius", &m_meso_radius).setUnit("nm").setNonnegative();
    registerParameter("surface_filling_ratio", &m_surface_filling_ratio).setNonnegative();
    registerParameter("meso_height", &m_meso_height).setUnit("nm").setNonnegative();
    registerParameter("sigma_meso_height", &m_sigma_meso_height).setUnit("nm").setNonnegative();
    registerParameter("sigma_meso_radius", &m_sigma_meso_radius).setUnit("nm").setNonnegative();
    registerParameter("lattice_length_a", &m_lattice_length_a).setUnit("nm").setNonnegative();
    registerParameter("lattice_length_c", &m_lattice_length_c).setUnit("nm").setNonnegative();
    registerParameter("nanoparticle_radius", &m_nanoparticle_radius).setUnit("nm").setNonnegative();
    registerParameter("sigma_nanoparticle_radius", &m_sigma_nanoparticle_radius)
        .setUnit("nm")
        .setNonnegative();
    registerParameter("sigma_lattice_length_a", &m_sigma_lattice_length_a)
        .setUnit("nm")
        .setNonnegative();
    registerParameter("roughness", &m_roughness).setUnit("nm").setNonnegative();
    registerParameter("nphi_rotations", &m_nphi_rotations).setNonnegative();
}


// create mesocrystal
MultiLayer* MesoCrystalBuilder::buildSample() const
{
    // create mesocrystal
    double surface_density = m_surface_filling_ratio / M_PI / m_meso_radius / m_meso_radius;
    //    complex_t n_particle(1.0-1.55e-5, 1.37e-6); // data from Artur
    // data from http://henke.lbl.gov/optical_constants/getdb2.html
    complex_t n_particle(1.0 - 2.84e-5, 4.7e-7);
    complex_t avg_n_squared_meso = 0.7886 * n_particle * n_particle + 0.2114;
    complex_t n_avg =
        std::sqrt(m_surface_filling_ratio * avg_n_squared_meso + 1.0 - m_surface_filling_ratio);
    complex_t n_particle_adapted = std::sqrt(n_avg * n_avg + n_particle * n_particle - 1.0);
    FormFactorCylinder ff_cyl(m_meso_radius, m_meso_height);
    FormFactorDecoratorDebyeWaller ff_meso(
        ff_cyl, m_sigma_meso_height * m_sigma_meso_height / 2.0,
        m_sigma_meso_radius * m_sigma_meso_radius / 2.0);

    // Create multilayer
    MultiLayer* p_multi_layer = new MultiLayer();

    complex_t n_air(1.0, 0.0);
    complex_t n_substrate(1.0 - 7.57e-6, 1.73e-7);

    HomogeneousMaterial air_material("Air", n_air);
    HomogeneousMaterial average_layer_material("Averagelayer", n_avg);
    HomogeneousMaterial substrate_material("Substrate", n_substrate);

    Layer air_layer(air_material);
    Layer avg_layer(average_layer_material, m_meso_height);
    Layer substrate_layer(substrate_material);

    ParticleLayout particle_layout;
    size_t n_max_phi_rotation_steps = int(m_nphi_rotations);
    size_t n_alpha_rotation_steps = 1;

    //    double alpha_step = 5.0*Units::degree/n_alpha_rotation_steps;
    //    double alpha_start = - (n_alpha_rotation_steps/2.0)*alpha_step;

    double phi_step = M_TWOPI / 3.0 / n_max_phi_rotation_steps;
    double phi_start = 0.0;
    for (size_t i = 0; i < n_max_phi_rotation_steps; ++i) {
        for (size_t j = 0; j < n_alpha_rotation_steps; ++j) {
            RotationZ z_rotation(phi_start + i * phi_step);
            const std::unique_ptr<MesoCrystal> P_meso(createMesoCrystal(
                m_lattice_length_a, m_lattice_length_c, n_particle_adapted, &ff_meso));
            P_meso->setPosition(0.0, 0.0, -m_meso_height);
            //            particle_layout.addParticle(*P_meso, z_rotation);
            particle_layout.addParticle(*P_meso, 1.0, kvector_t(0.0, 0.0, 0.0), z_rotation);
        }
    }

    particle_layout.setTotalParticleSurfaceDensity(surface_density);

    avg_layer.addLayout(particle_layout);

    LayerRoughness roughness(m_roughness, 0.3, 500.0 * Units::nanometer);

    p_multi_layer->addLayer(air_layer);
    p_multi_layer->addLayer(avg_layer);
    p_multi_layer->addLayerWithTopRoughness(substrate_layer, roughness);

    //    std::cout << "Average layer index: " << n_avg << std::endl;
    //    std::cout << "Adapted particle index: " << n_particle_adapted << std::endl;
    //    std::cout << "Substrate layer index: " << n_substrate << std::endl;

    return p_multi_layer;
}

MesoCrystal* MesoCrystalBuilder::createMesoCrystal(
    double stacking_radius_a, double stacking_radius_c, complex_t n_particle,
    const IFormFactor* p_meso_form_factor) const
{
    const Lattice* p_lat = createLattice(stacking_radius_a, stacking_radius_c);
    kvector_t bas_a = p_lat->getBasisVectorA();
    kvector_t bas_b = p_lat->getBasisVectorB();
    kvector_t bas_c = p_lat->getBasisVectorC();

    HomogeneousMaterial particle_material("Particle", n_particle);

    FormFactorSphereGaussianRadius ff_sphere(m_nanoparticle_radius, m_sigma_nanoparticle_radius);
    Particle particle(particle_material, ff_sphere);
    kvector_t position_0 = kvector_t(0.0, 0.0, 0.0);
    kvector_t position_1 = 1.0 / 3.0 * (2.0 * bas_a + bas_b + bas_c);
    kvector_t position_2 = 1.0 / 3.0 * (bas_a + 2.0 * bas_b + 2.0 * bas_c);
    std::vector<kvector_t> pos_vector;
    pos_vector.push_back(position_0);
    pos_vector.push_back(position_1);
    pos_vector.push_back(position_2);
    ParticleComposition basis(particle, pos_vector);

    Crystal npc(basis, *p_lat);
    delete p_lat;
    double dw_factor = m_sigma_lattice_length_a * m_sigma_lattice_length_a / 6.0;
    npc.setDWFactor(dw_factor);
    return new MesoCrystal(npc.clone(), p_meso_form_factor->clone());
}

const Lattice*
MesoCrystalBuilder::createLattice(double stacking_radius_a, double stacking_radius_c) const
{
    Lattice* p_result = new Lattice(
        Lattice::createTrigonalLattice(stacking_radius_a * 2.0, stacking_radius_c * 2.0 * 2.3));
    p_result->setSelectionRule(SimpleSelectionRule(-1, 1, 1, 3));
    return p_result;
}
