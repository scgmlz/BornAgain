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
#include "Core/Basics/Exceptions.h"
#include "Core/Basics/Units.h"
#include "Core/Material/MaterialFactoryFuncs.h"
#include "Core/Multilayer/Layer.h"
#include "Core/Multilayer/LayerInterface.h"
#include "Core/Multilayer/LayerRoughness.h"
#include "Core/Multilayer/MultiLayer.h"
#include "Core/Parametrization/RealParameter.h"
#include "Core/Particle/Particle.h"
#include "Core/StandardSamples/SampleComponents.h"
#include "Core/includeIncludes/FormFactors.h"

LayersWithAbsorptionBuilder::LayersWithAbsorptionBuilder()
    : m_ff(new FormFactorFullSphere(5.0 * Units::nanometer))
{
}

LayersWithAbsorptionBuilder::~LayersWithAbsorptionBuilder() = default;

MultiLayer* LayersWithAbsorptionBuilder::buildSample() const
{
    Material mAmbience = HomogeneousMaterial("Air", 0.0, 0.0);
    Material mMiddle = HomogeneousMaterial("Teflon", 2.900e-6, 6.019e-9);
    Material mSubstrate = HomogeneousMaterial("Substrate", 3.212e-6, 3.244e-8);
    Material mParticle = HomogeneousMaterial("Ag", 1.245e-5, 5.419e-7);

    const double middle_layer_thickness(60.0 * Units::nanometer);

    Particle particle(mParticle, *m_ff);
    particle.setRotation(RotationZ(10.0 * Units::degree));
    particle.rotate(RotationY(10.0 * Units::degree));
    particle.rotate(RotationX(10.0 * Units::degree));
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

MultiLayer* LayersWithAbsorptionBuilder::createSample(size_t index)
{
    if (index >= size())
        throw std::runtime_error("ParticleInTheAirBuilder::createSample() -> Error. "
                                 "Sample index is out of range.");

    auto ff_names = ff_components().keys();
    m_ff.reset(ff_components().getItem(ff_names[index])->clone());

    setName(ff_names[index]);

    return buildSample();
}

size_t LayersWithAbsorptionBuilder::size()
{
    return ff_components().size();
}

FormFactorComponents& LayersWithAbsorptionBuilder::ff_components()
{
    static FormFactorComponents result = {};
    return result;
}
