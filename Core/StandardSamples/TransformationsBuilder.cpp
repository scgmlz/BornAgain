// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/StandardSamples/TransformationsBuilder.cpp
//! @brief     Implements classes to build samples with different transformations.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "TransformationsBuilder.h"
#include "FormFactorBox.h"
#include "HomogeneousMaterial.h"
#include "Layer.h"
#include "MultiLayer.h"
#include "Particle.h"
#include "ParticleLayout.h"
#include "RealParameter.h"
#include "Units.h"

MultiLayer* TransformBoxBuilder::buildSample() const
{
    HomogeneousMaterial mAmbience("Air", 0.0, 0.0);
    HomogeneousMaterial mMiddle("Teflon", 2.900e-6, 6.019e-9);
    HomogeneousMaterial mSubstrate("Substrate", 3.212e-6, 3.244e-8);

    HomogeneousMaterial mParticle("Ag", 1.245e-5, 5.419e-7);

    double layer_thickness(100);
    double length(50);
    double width(20);
    double height(10);

    Particle box(mParticle, FormFactorBox(length, width, height));
    box.setRotation(RotationZ(90. * Units::degree));
    box.applyRotation(RotationY(90. * Units::degree));
    box.setPosition(kvector_t(0, 0, -layer_thickness / 2.));

    ParticleLayout layout;
    layout.addParticle(box);

    Layer air_layer(mAmbience);
    Layer middle_layer(mMiddle, layer_thickness);
    middle_layer.addLayout(layout);
    Layer substrate(mSubstrate);

    MultiLayer* multi_layer = new MultiLayer();
    multi_layer->addLayer(air_layer);
    multi_layer->addLayer(middle_layer);
    multi_layer->addLayer(substrate);

    return multi_layer;
}
