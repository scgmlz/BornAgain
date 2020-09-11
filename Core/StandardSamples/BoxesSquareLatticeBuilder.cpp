// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/StandardSamples/BoxesSquareLatticeBuilder.cpp
//! @brief     Implements class BoxesSquareLatticeBuilder.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Core/StandardSamples/BoxesSquareLatticeBuilder.h"
#include "Core/Aggregate/InterferenceFunction2DLattice.h"
#include "Core/Aggregate/ParticleLayout.h"
#include "Core/Basics/Units.h"
#include "Core/HardParticle/FormFactorBox.h"
#include "Core/Material/MaterialFactoryFuncs.h"
#include "Core/Multilayer/Layer.h"
#include "Core/Multilayer/MultiLayer.h"
#include "Core/Parametrization/RealParameter.h"
#include "Core/Particle/Particle.h"

// -----------------------------------------------------------------------------
// Boxes in square lattice
// -----------------------------------------------------------------------------

BoxesSquareLatticeBuilder::BoxesSquareLatticeBuilder()
    : m_length(5 * Units::nanometer), m_height(10 * Units::nanometer)
{
}

MultiLayer* BoxesSquareLatticeBuilder::buildSample() const
{
    MultiLayer* multi_layer = new MultiLayer();

    Material particle_material = HomogeneousMaterial("Particle", 6e-4, 2e-8);
    Material air_material = HomogeneousMaterial("Air", 0.0, 0.0);
    Material substrate_material = HomogeneousMaterial("Substrate", 6e-6, 2e-8);

    Layer air_layer(air_material);
    Layer substrate_layer(substrate_material);

    std::unique_ptr<InterferenceFunction2DLattice> P_interference_function(
        InterferenceFunction2DLattice::createSquare(8 * Units::nanometer, 0));

    FTDecayFunction2DCauchy pdf(100.0 * Units::nanometer, 100.0 * Units::nanometer, 0);
    P_interference_function->setDecayFunction(pdf);

    // particles
    ParticleLayout particle_layout;
    FormFactorBox ff_box(m_length, m_length, m_height);
    Particle particle(particle_material, ff_box);
    particle_layout.addParticle(particle, 1.0);

    particle_layout.setInterferenceFunction(*P_interference_function);

    air_layer.addLayout(particle_layout);

    multi_layer->addLayer(air_layer);
    multi_layer->addLayer(substrate_layer);

    return multi_layer;
}
