//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Sample/StandardSamples/RotatedPyramidsBuilder.cpp
//! @brief     Implements classe RotatedPyramidsBuilder
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "Sample/StandardSamples/RotatedPyramidsBuilder.h"
#include "Base/Const/Units.h"
#include "Sample/Aggregate/ParticleLayout.h"
#include "Sample/HardParticle/FormFactorPyramid.h"
#include "Sample/Multilayer/Layer.h"
#include "Sample/Multilayer/MultiLayer.h"
#include "Sample/Particle/Particle.h"
#include "Sample/StandardSamples/ReferenceMaterials.h"

MultiLayer* RotatedPyramidsBuilder::buildSample() const {
    const double m_length(10 * Units::nm);
    const double m_height(5 * Units::nm);
    const double m_alpha(Units::deg2rad(54.73));
    const double m_zangle(45. * Units::deg);

    Layer vacuum_layer(refMat::Vacuum);
    Layer substrate_layer(refMat::Substrate);

    FormFactorPyramid ff_pyramid(m_length, m_height, m_alpha);

    Particle pyramid(refMat::Particle, ff_pyramid);

    RotationZ z_rotation(m_zangle);

    ParticleLayout particle_layout;
    particle_layout.addParticle(pyramid, 1.0, kvector_t(0, 0, 0), z_rotation);

    vacuum_layer.addLayout(particle_layout);

    MultiLayer* multi_layer = new MultiLayer();
    multi_layer->addLayer(vacuum_layer);
    multi_layer->addLayer(substrate_layer);
    return multi_layer;
}
