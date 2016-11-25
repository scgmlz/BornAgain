// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/StandardSamples/RotatedPyramidsBuilder.cpp
//! @brief     Implements classe RotatedPyramidsBuilder
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "RotatedPyramidsBuilder.h"
#include "FormFactorPyramid.h"
#include "HomogeneousMaterial.h"
#include "Layer.h"
#include "MultiLayer.h"
#include "Particle.h"
#include "ParticleLayout.h"
#include "RealParameter.h"
#include "Units.h"

RotatedPyramidsBuilder::RotatedPyramidsBuilder()
    : m_length(10 * Units::nanometer)
    , m_height(5 * Units::nanometer)
    , m_alpha(Units::deg2rad(54.73))
    , m_zangle(45. * Units::degree)
{
    init_parameters();
}

void RotatedPyramidsBuilder::init_parameters()
{
    registerParameter("length", &m_length).setUnit("nm").setNonnegative();
    registerParameter("height", &m_height).setUnit("nm").setNonnegative();
    registerParameter("alpha", &m_alpha).setUnit("rad");
    registerParameter("zangle", &m_zangle).setUnit("rad");
}

MultiLayer* RotatedPyramidsBuilder::buildSample() const
{
    MultiLayer* multi_layer = new MultiLayer();

    HomogeneousMaterial air_material("Air", 0.0, 0.0);
    HomogeneousMaterial substrate_material("Substrate", 6e-6, 2e-8);
    HomogeneousMaterial particle_material("Particle", 6e-4, 2e-8);

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
