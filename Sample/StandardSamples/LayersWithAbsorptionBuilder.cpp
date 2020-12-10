//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Sample/StandardSamples/LayersWithAbsorptionBuilder.cpp
//! @brief     Implements class LayersWithAbsorptionBuilder.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "Sample/StandardSamples/LayersWithAbsorptionBuilder.h"
#include "Base/Const/Units.h"
#include "Sample/Aggregate/ParticleLayout.h"
#include "Sample/HardParticle/FormFactorFullSphere.h"
#include "Sample/Multilayer/Layer.h"
#include "Sample/Multilayer/MultiLayer.h"
#include "Sample/Particle/Particle.h"
#include "Sample/SampleBuilderEngine/SampleComponents.h"
#include "Sample/Slice/LayerInterface.h"
#include "Sample/StandardSamples/ReferenceMaterials.h"

namespace {

static const FormFactorComponents ff_components;

} // namespace

LayersWithAbsorptionBuilder::LayersWithAbsorptionBuilder()
    : m_ff(new FormFactorFullSphere(5.0 * Units::nm)) {}

LayersWithAbsorptionBuilder::~LayersWithAbsorptionBuilder() = default;

MultiLayer* LayersWithAbsorptionBuilder::buildSample() const {
    const double middle_layer_thickness(60.0 * Units::nm);

    Particle particle(refMat::Ag, *m_ff);
    particle.setRotation(RotationZ(10.0 * Units::deg));
    particle.rotate(RotationY(10.0 * Units::deg));
    particle.rotate(RotationX(10.0 * Units::deg));
    particle.setPosition(kvector_t(0.0, 0.0, -middle_layer_thickness / 2.0));

    ParticleLayout layout;
    layout.addParticle(particle);

    Layer vacuum_layer(refMat::Vacuum);
    Layer middle_layer(refMat::Teflon, middle_layer_thickness);
    Layer substrate(refMat::Substrate2);

    middle_layer.addLayout(layout);

    MultiLayer* multi_layer = new MultiLayer();
    multi_layer->addLayer(vacuum_layer);
    multi_layer->addLayer(middle_layer);
    multi_layer->addLayer(substrate);
    return multi_layer;
}

MultiLayer* LayersWithAbsorptionBuilder::createSampleByIndex(size_t index) {
    const std::string name = ff_components.keys().at(index);
    m_ff.reset(ff_components.getItem(name)->clone());
    setName(name);
    return buildSample();
}

size_t LayersWithAbsorptionBuilder::size() {
    return ff_components.size();
}
