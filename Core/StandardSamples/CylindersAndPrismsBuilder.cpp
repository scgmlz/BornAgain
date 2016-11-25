// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/StandardSamples/CylindersAndPrismsBuilder.cpp
//! @brief     Implements class CylindersAndPrismsBuilder.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "CylindersAndPrismsBuilder.h"
#include "FormFactorCylinder.h"
#include "FormFactorPrism3.h"
#include "HomogeneousMaterial.h"
#include "Layer.h"
#include "MultiLayer.h"
#include "Particle.h"
#include "ParticleLayout.h"
#include "RealParameter.h"
#include "Units.h"

CylindersAndPrismsBuilder::CylindersAndPrismsBuilder()
    : m_cylinder_height(5 * Units::nanometer)
    , m_cylinder_radius(5 * Units::nanometer)
    , m_prism_height(5 * Units::nanometer)
    , m_prism_length(10 * Units::nanometer)
    , m_cylinder_weight(0.5)
{
    init_parameters();
}

void CylindersAndPrismsBuilder::init_parameters()
{

    registerParameter("cylinder_height", &m_cylinder_height).setUnit("nm").setNonnegative();
    registerParameter("cylinder_radius", &m_cylinder_radius).setUnit("nm").setNonnegative();
    registerParameter("prism_height", &m_prism_height).setUnit("nm").setNonnegative();
    registerParameter("prism_length", &m_prism_length).setUnit("nm").setNonnegative();
    registerParameter("cylinder_weight", &m_cylinder_weight).setNonnegative();
}

MultiLayer* CylindersAndPrismsBuilder::buildSample() const
{
    MultiLayer* multi_layer = new MultiLayer();

    HomogeneousMaterial air_material("Air", 0., 0.);
    HomogeneousMaterial substrate_material("Substrate", 6e-6, 2e-8);
    HomogeneousMaterial particle_material("Particle", 6e-4, 2e-8);

    Layer air_layer(air_material);
    Layer substrate_layer(substrate_material);

    ParticleLayout particle_layout;

    FormFactorCylinder ff_cylinder(m_cylinder_radius, m_cylinder_height);
    Particle cylinder(particle_material, ff_cylinder);

    FormFactorPrism3 ff_prism3(m_prism_length, m_prism_height);
    Particle prism3(particle_material, ff_prism3);

    particle_layout.addParticle(cylinder, m_cylinder_weight);
    particle_layout.addParticle(prism3, 1.0 - m_cylinder_weight);

    air_layer.addLayout(particle_layout);

    multi_layer->addLayer(air_layer);
    multi_layer->addLayer(substrate_layer);
    return multi_layer;
}
