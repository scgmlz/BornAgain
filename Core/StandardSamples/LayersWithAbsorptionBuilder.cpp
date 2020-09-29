// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/StandardSamples/LayersWithAbsorptionBuilder.cpp
//! @brief     Implements class LayersWithAbsorptionBuilder.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Core/StandardSamples/LayersWithAbsorptionBuilder.h"
#include "Core/Aggregate/ParticleLayout.h"
#include "Core/Basics/Units.h"
#include "Core/HardParticle/FormFactorFullSphere.h"
#include "Core/Multilayer/Layer.h"
#include "Core/Multilayer/LayerInterface.h"
#include "Core/Multilayer/MultiLayer.h"
#include "Core/Particle/Particle.h"
#include "Core/SampleBuilderEngine/SampleComponents.h"
#include "Core/StandardSamples/ReferenceMaterials.h"

namespace
{

static const FormFactorComponents ff_components;

} // namespace

LayersWithAbsorptionBuilder::LayersWithAbsorptionBuilder()
    : m_ff(new FormFactorFullSphere(5.0 * Units::nanometer))
{
}

LayersWithAbsorptionBuilder::~LayersWithAbsorptionBuilder() = default;

MultiLayer* LayersWithAbsorptionBuilder::buildSample() const
{
    const double middle_layer_thickness(60.0 * Units::nanometer);

    Particle particle(refMat::Ag, *m_ff);
    particle.setRotation(RotationZ(10.0 * Units::degree));
    particle.rotate(RotationY(10.0 * Units::degree));
    particle.rotate(RotationX(10.0 * Units::degree));
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

MultiLayer* LayersWithAbsorptionBuilder::createSampleByIndex(size_t index)
{
    const std::string name = ff_components.keys().at(index);
    m_ff.reset(ff_components.getItem(name)->clone());
    setName(name);
    return buildSample();
}

size_t LayersWithAbsorptionBuilder::size()
{
    return ff_components.size();
}
