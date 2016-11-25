// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/StandardSamples/ParticleCompositionBuilder.cpp
//! @brief     Implements class ParticleCompositionBuilder.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "ParticleCompositionBuilder.h"
#include "FormFactorFullSphere.h"
#include "HomogeneousMaterial.h"
#include "InterferenceFunction2DLattice.h"
#include "Layer.h"
#include "MultiLayer.h"
#include "Particle.h"
#include "ParticleComposition.h"
#include "ParticleLayout.h"
#include "RealParameter.h"
#include "Units.h"

// --- ParticleCompositionBuilder ---

MultiLayer* ParticleCompositionBuilder::buildSample() const
{
    MultiLayer* multi_layer = new MultiLayer();

    HomogeneousMaterial air_material("Air", 0.0, 0.0);
    HomogeneousMaterial substrate_material("Substrate", 6e-6, 2e-8);
    HomogeneousMaterial particle_material("Particle", 6e-4, 2e-8);

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
        InterferenceFunction2DLattice::createHexagonal(radius * 2.0)
    };
    FTDecayFunction2DCauchy pdf(10 * Units::nanometer, 10 * Units::nanometer);
    P_interference->setDecayFunction(pdf);

    particle_layout.addInterferenceFunction(*P_interference);

    air_layer.addLayout(particle_layout);
    multi_layer->addLayer(air_layer);
    multi_layer->addLayer(substrate_layer);

    return multi_layer;
}
