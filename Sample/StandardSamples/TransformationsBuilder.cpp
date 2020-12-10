//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Sample/StandardSamples/TransformationsBuilder.cpp
//! @brief     Implements classes to build samples with different transformations.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "Sample/StandardSamples/TransformationsBuilder.h"
#include "Base/Const/Units.h"
#include "Sample/Aggregate/ParticleLayout.h"
#include "Sample/HardParticle/FormFactorBox.h"
#include "Sample/Multilayer/Layer.h"
#include "Sample/Multilayer/MultiLayer.h"
#include "Sample/Particle/Particle.h"
#include "Sample/StandardSamples/ReferenceMaterials.h"

MultiLayer* TransformBoxBuilder::buildSample() const {
    const double layer_thickness(100);
    const double length(50);
    const double width(20);
    const double height(10);

    Particle box(refMat::Ag, FormFactorBox(length, width, height));
    box.setRotation(RotationZ(90. * Units::deg));
    box.rotate(RotationY(90. * Units::deg));
    box.setPosition(kvector_t(0, 0, -layer_thickness / 2.));

    ParticleLayout layout;
    layout.addParticle(box);

    Layer vacuum_layer(refMat::Vacuum);
    Layer middle_layer(refMat::Teflon, layer_thickness);
    middle_layer.addLayout(layout);
    Layer substrate(refMat::Substrate2);

    MultiLayer* multi_layer = new MultiLayer();
    multi_layer->addLayer(vacuum_layer);
    multi_layer->addLayer(middle_layer);
    multi_layer->addLayer(substrate);
    return multi_layer;
}
