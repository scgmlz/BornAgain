// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/StandardSamples/RotatedPyramidsBuilder.cpp
//! @brief     Implements classe RotatedPyramidsBuilder
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Core/StandardSamples/RotatedPyramidsBuilder.h"
#include "Core/Aggregate/ParticleLayout.h"
#include "Core/Basics/Units.h"
#include "Core/HardParticle/FormFactorPyramid.h"
#include "Core/Material/MaterialFactoryFuncs.h"
#include "Core/Multilayer/Layer.h"
#include "Core/Multilayer/MultiLayer.h"
#include "Core/Parametrization/RealParameter.h"
#include "Core/Particle/Particle.h"

RotatedPyramidsBuilder::RotatedPyramidsBuilder()
    : m_length(10 * Units::nanometer), m_height(5 * Units::nanometer),
      m_alpha(Units::deg2rad(54.73)), m_zangle(45. * Units::degree)
{
}

MultiLayer* RotatedPyramidsBuilder::buildSample() const
{
    MultiLayer* multi_layer = new MultiLayer();

    Material air_material = HomogeneousMaterial("Air", 0.0, 0.0);
    Material substrate_material = HomogeneousMaterial("Substrate", 6e-6, 2e-8);
    Material particle_material = HomogeneousMaterial("Particle", 6e-4, 2e-8);

    Layer air_layer(air_material);
    Layer substrate_layer(substrate_material);

    FormFactorPyramid ff_pyramid(m_length, m_height, m_alpha);

    Particle pyramid(particle_material, ff_pyramid);

    RotationZ z_rotation(m_zangle);

    ParticleLayout particle_layout;
    particle_layout.addParticle(pyramid, 1.0, kvector_t(0, 0, 0), z_rotation);

    air_layer.addLayout(particle_layout);

    multi_layer->addLayer(air_layer);
    multi_layer->addLayer(substrate_layer);

    return multi_layer;
}
