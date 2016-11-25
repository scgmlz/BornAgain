// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/StandardSamples/LayersWithAbsorptionBuilder.cpp
//! @brief     Implements class LayersWithAbsorptionBuilder.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "LayersWithAbsorptionBuilder.h"
#include "Exceptions.h"
#include "HomogeneousMaterial.h"
#include "Layer.h"
#include "LayerInterface.h"
#include "LayerRoughness.h"
#include "MultiLayer.h"
#include "Particle.h"
#include "ParticleLayout.h"
#include "RealParameter.h"
#include "Units.h"

MultiLayer* LayersWithAbsorptionBuilder::buildSample() const
{
    const IFormFactor* form_factor = getFormFactor();
    if (!form_factor)
        throw Exceptions::NullPointerException(
            "LayersWithAbsorptionBuilder::buildSample() -> Error. Form factor is not initialized.");

    HomogeneousMaterial mAmbience("Air", 0.0, 0.0);
    HomogeneousMaterial mMiddle("Teflon", 2.900e-6, 6.019e-9);
    HomogeneousMaterial mSubstrate("Substrate", 3.212e-6, 3.244e-8);
    HomogeneousMaterial mParticle("Ag", 1.245e-5, 5.419e-7);

    const double middle_layer_thickness(60.0 * Units::nanometer);

    Particle particle(mParticle, *form_factor);
    particle.setRotation(RotationZ(10.0 * Units::degree));
    particle.applyRotation(RotationY(10.0 * Units::degree));
    particle.applyRotation(RotationX(10.0 * Units::degree));
    particle.setPosition(kvector_t(0.0, 0.0, -middle_layer_thickness / 2.0));

    ParticleLayout layout;
    layout.addParticle(particle);

    Layer air_layer(mAmbience);
    Layer middle_layer(mMiddle, middle_layer_thickness);
    Layer substrate(mSubstrate);

    middle_layer.addLayout(layout);

    MultiLayer* multi_layer = new MultiLayer();
    multi_layer->addLayer(air_layer);
    multi_layer->addLayer(middle_layer);
    multi_layer->addLayer(substrate);
    return multi_layer;
}
