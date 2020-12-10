//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Sample/StandardSamples/MesoCrystalBuilder.cpp
//! @brief     Implements class MesoCrystalBuilder.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "Sample/StandardSamples/MesoCrystalBuilder.h"
#include "Base/Const/Units.h"
#include "Sample/Aggregate/ParticleLayout.h"
#include "Sample/HardParticle/FormFactorCylinder.h"
#include "Sample/HardParticle/FormFactorFullSphere.h"
#include "Sample/Multilayer/Layer.h"
#include "Sample/Multilayer/MultiLayer.h"
#include "Sample/Particle/Crystal.h"
#include "Sample/Particle/MesoCrystal.h"
#include "Sample/Particle/Particle.h"
#include "Sample/StandardSamples/ReferenceMaterials.h"

MultiLayer* MesoCrystalBuilder::buildSample() const {
    // mesocrystal lattice
    kvector_t lattice_basis_a(5.0, 0.0, 0.0);
    kvector_t lattice_basis_b(0.0, 5.0, 0.0);
    kvector_t lattice_basis_c(0.0, 0.0, 5.0);
    Lattice3D lattice(lattice_basis_a, lattice_basis_b, lattice_basis_c);

    // spherical particle that forms the base of the mesocrystal
    FormFactorFullSphere sphere_ff(2.0);
    Particle sphere(refMat::Particle, sphere_ff);

    // crystal structure
    Crystal crystal(sphere, lattice);

    // mesocrystal
    FormFactorCylinder meso_ff(20.0, 50.0);
    MesoCrystal meso(crystal, meso_ff);

    ParticleLayout particle_layout;
    particle_layout.addParticle(meso);

    Layer vacuum_layer(refMat::Vacuum);
    vacuum_layer.addLayout(particle_layout);
    Layer substrate_layer(refMat::Substrate);

    MultiLayer* multi_layer = new MultiLayer();
    multi_layer->addLayer(vacuum_layer);
    multi_layer->addLayer(substrate_layer);
    return multi_layer;
}
