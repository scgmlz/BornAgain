// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/StandardSamples/LatticeBuilder.cpp
//! @brief     Implements class Lattice1DBuilder.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "LatticeBuilder.h"
#include "FTDecayFunctions.h"
#include "FormFactorCylinder.h"
#include "HomogeneousMaterial.h"
#include "InterferenceFunction1DLattice.h"
#include "Layer.h"
#include "MultiLayer.h"
#include "Particle.h"
#include "ParticleLayout.h"
#include "RealParameter.h"
#include "Units.h"

Lattice1DBuilder::Lattice1DBuilder()
    : m_length(20.0 * Units::nanometer)
    , m_xi(10.0 * Units::deg)
    , m_corr_length(1000.0 * Units::nanometer)
    , m_cylinder_height(5 * Units::nanometer)
    , m_cylinder_radius(5 * Units::nanometer)
{
    init_parameters();
}

MultiLayer* Lattice1DBuilder::buildSample() const
{
    MultiLayer* multi_layer = new MultiLayer();

    HomogeneousMaterial particle_material("Particle", 6e-4, 2e-8);
    HomogeneousMaterial air_material("Air", 0.0, 0.0);
    HomogeneousMaterial substrate_material("Substrate", 6e-6, 2e-8);

    Layer air_layer(air_material);
    Layer substrate_layer(substrate_material);

    InterferenceFunction1DLattice interference_function(m_length, m_xi);
    FTDecayFunction1DCauchy pdf(1000.0 * Units::nanometer);
    interference_function.setDecayFunction(pdf);

    FormFactorCylinder ff_cylinder(m_cylinder_radius, m_cylinder_height);
    Particle cylinder(particle_material, ff_cylinder);

    ParticleLayout particle_layout(cylinder);
    particle_layout.addInterferenceFunction(interference_function);

    air_layer.addLayout(particle_layout);

    multi_layer->addLayer(air_layer);
    multi_layer->addLayer(substrate_layer);

    return multi_layer;
}

void Lattice1DBuilder::init_parameters()
{
    registerParameter("lattice_length", &m_length).setUnit("nm").setNonnegative();
    registerParameter("lattice_rotation", &m_xi).setUnit("rad");
    registerParameter("corr_length", &m_corr_length).setUnit("nm").setNonnegative();
    registerParameter("cylinder_height", &m_cylinder_height).setUnit("nm").setNonnegative();
    registerParameter("cylinder_radius", &m_cylinder_radius).setUnit("nm").setNonnegative();
}
