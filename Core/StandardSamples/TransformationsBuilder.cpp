// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/StandardSamples/TransformationsBuilder.cpp
//! @brief     Implements classes to build samples with different transformations.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Core/StandardSamples/TransformationsBuilder.h"
#include "Core/Aggregate/ParticleLayout.h"
#include "Core/Basics/Units.h"
#include "Core/HardParticle/FormFactorBox.h"
#include "Core/Multilayer/Layer.h"
#include "Core/Multilayer/MultiLayer.h"
#include "Core/Particle/Particle.h"
#include "Core/StandardSamples/ReferenceMaterials.h"

MultiLayer* TransformBoxBuilder::buildSample() const
{
    const double layer_thickness(100);
    const double length(50);
    const double width(20);
    const double height(10);

    Particle box(refMat::Ag, FormFactorBox(length, width, height));
    box.setRotation(RotationZ(90. * Units::degree));
    box.rotate(RotationY(90. * Units::degree));
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
