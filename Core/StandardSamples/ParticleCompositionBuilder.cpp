// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/StandardSamples/ParticleCompositionBuilder.cpp
//! @brief     Implements class ParticleCompositionBuilder.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Core/StandardSamples/ParticleCompositionBuilder.h"
#include "Core/Aggregate/InterferenceFunction2DLattice.h"
#include "Core/Aggregate/ParticleLayout.h"
#include "Core/Basics/Units.h"
#include "Core/HardParticle/FormFactorFullSphere.h"
#include "Core/Material/MaterialFactoryFuncs.h"
#include "Core/Multilayer/Layer.h"
#include "Core/Multilayer/MultiLayer.h"
#include "Core/Parametrization/RealParameter.h"
#include "Core/Particle/Particle.h"
#include "Core/Particle/ParticleComposition.h"

// --- ParticleCompositionBuilder ---

MultiLayer* ParticleCompositionBuilder::buildSample() const
{
    MultiLayer* multi_layer = new MultiLayer();

    Material air_material = HomogeneousMaterial("Air", 0.0, 0.0);
    Material substrate_material = HomogeneousMaterial("Substrate", 6e-6, 2e-8);
    Material particle_material = HomogeneousMaterial("Particle", 6e-4, 2e-8);

    Layer air_layer(air_material);
    Layer substrate_layer(substrate_material);

    double radius(10.0 * Units::nanometer);
    FormFactorFullSphere sphere_ff(radius);
    Particle sphere(particle_material, sphere_ff);
    ParticleLayout particle_layout;

    kvector_t pos0(0.0, 0.0, 0.0);
    kvector_t pos1(radius, radius / std::sqrt(3.0), std::sqrt(8.0 / 3.0) * radius);
    std::vector<kvector_t> positions;
    positions.push_back(pos0);
    positions.push_back(pos1);

    ParticleComposition basis;

    basis.addParticles(sphere, positions);
    particle_layout.addParticle(basis);

    std::unique_ptr<InterferenceFunction2DLattice> P_interference{
        InterferenceFunction2DLattice::createHexagonal(radius * 2.0, 0)};
    FTDecayFunction2DCauchy pdf(10 * Units::nanometer, 10 * Units::nanometer, 0);
    P_interference->setDecayFunction(pdf);

    particle_layout.setInterferenceFunction(*P_interference);

    air_layer.addLayout(particle_layout);
    multi_layer->addLayer(air_layer);
    multi_layer->addLayer(substrate_layer);

    return multi_layer;
}
