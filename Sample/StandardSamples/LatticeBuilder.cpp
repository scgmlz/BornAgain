//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Sample/StandardSamples/LatticeBuilder.cpp
//! @brief     Implements class Lattice1DBuilder.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "Sample/StandardSamples/LatticeBuilder.h"
#include "Base/Const/Units.h"
#include "Sample/Aggregate/InterferenceFunction1DLattice.h"
#include "Sample/Aggregate/ParticleLayout.h"
#include "Sample/Correlations/FTDecay1D.h"
#include "Sample/Correlations/FTDecay2D.h"
#include "Sample/HardParticle/FormFactorCylinder.h"
#include "Sample/Multilayer/Layer.h"
#include "Sample/Multilayer/MultiLayer.h"
#include "Sample/Particle/Particle.h"
#include "Sample/StandardSamples/ReferenceMaterials.h"

MultiLayer* Lattice1DBuilder::buildSample() const {
    const double length(20.0 * Units::nm);
    const double xi(10.0 * Units::deg);
    const double corr_length(1000.0 * Units::nm);
    const double cylinder_height(5 * Units::nm);
    const double cylinder_radius(5 * Units::nm);

    Layer vacuum_layer(refMat::Vacuum);
    Layer substrate_layer(refMat::Substrate);

    InterferenceFunction1DLattice interference_function(length, xi);
    FTDecayFunction1DCauchy pdf(corr_length);
    interference_function.setDecayFunction(pdf);

    FormFactorCylinder ff_cylinder(cylinder_radius, cylinder_height);
    Particle cylinder(refMat::Particle, ff_cylinder);

    ParticleLayout particle_layout(cylinder);
    particle_layout.setInterferenceFunction(interference_function);

    vacuum_layer.addLayout(particle_layout);

    MultiLayer* multi_layer = new MultiLayer();
    multi_layer->addLayer(vacuum_layer);
    multi_layer->addLayer(substrate_layer);
    return multi_layer;
}
