// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/StandardSamples/SlicedCylindersBuilder.cpp
//! @brief     Implements classes for testing slicing machinery.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Core/StandardSamples/SlicedCylindersBuilder.h"
#include "Core/Aggregate/ParticleLayout.h"
#include "Core/Basics/MathConstants.h"
#include "Core/Basics/Units.h"
#include "Core/HardParticle/FormFactorCylinder.h"
#include "Core/Material/MaterialFactoryFuncs.h"
#include "Core/Multilayer/Layer.h"
#include "Core/Multilayer/MultiLayer.h"
#include "Core/Particle/Particle.h"

namespace
{
//! Returns SLD input (in inverse square Angstroms) for MaterialBySLD from _delta_ and _beta_,
//! i.e. the input for HomogeneousMaterial.
complex_t getSLDFromN(double wavelength, double delta, double beta);
complex_t averageSLD(complex_t sld_p, complex_t sld_l, double eff_vol);
} // namespace

SlicedCylindersBuilder::SlicedCylindersBuilder()
    : m_height(5 * Units::nanometer), m_radius(5 * Units::nanometer), m_wavelength(0.154) // nm
      ,
      m_n_slices(3)
{
}

MultiLayer* SlicedCylindersBuilder::buildSample() const
{
    MultiLayer* multi_layer = new MultiLayer();

    Material air_material = HomogeneousMaterial("Air", 0.0, 0.0);
    Material substrate_material = HomogeneousMaterial("Substrate", 6e-6, 2e-8);
    Material particle_material = HomogeneousMaterial("Particle", 6e-4, 2e-8);

    Layer air_layer(air_material);
    Layer substrate_layer(substrate_material);

    FormFactorCylinder ff_cylinder(m_radius, m_height);

    Particle particle(particle_material, ff_cylinder);
    ParticleLayout particle_layout(particle);

    air_layer.addLayout(particle_layout);
    air_layer.setNumberOfSlices(m_n_slices);

    multi_layer->addLayer(air_layer);
    multi_layer->addLayer(substrate_layer);

    return multi_layer;
}

SLDSlicedCylindersBuilder::SLDSlicedCylindersBuilder() : SlicedCylindersBuilder() {}

MultiLayer* SLDSlicedCylindersBuilder::buildSample() const
{
    MultiLayer* multi_layer = new MultiLayer();

    Material air_material = MaterialBySLD("Air", 0.0, 0.0);
    complex_t sub_sld = getSLDFromN(m_wavelength, 6e-6, 2e-8);
    Material substrate_material = MaterialBySLD("Substrate", sub_sld.real(), sub_sld.imag());
    complex_t par_sld = getSLDFromN(m_wavelength, 6e-4, 2e-8);
    Material particle_material = MaterialBySLD("Particle", par_sld.real(), par_sld.imag());

    Layer air_layer(air_material);
    Layer substrate_layer(substrate_material);

    FormFactorCylinder ff_cylinder(m_radius, m_height);

    Particle particle(particle_material, ff_cylinder);
    ParticleLayout particle_layout(particle);

    air_layer.addLayout(particle_layout);
    air_layer.setNumberOfSlices(m_n_slices);

    multi_layer->addLayer(air_layer);
    multi_layer->addLayer(substrate_layer);

    return multi_layer;
}

AveragedSlicedCylindersBuilder::AveragedSlicedCylindersBuilder()
    : SlicedCylindersBuilder(), m_par_surf_density(ParticleLayout().totalParticleSurfaceDensity())
{
}

MultiLayer* AveragedSlicedCylindersBuilder::buildSample() const
{
    MultiLayer* multi_layer = new MultiLayer();

    complex_t air_sld{0.0, 0.0};
    Material air_material = MaterialBySLD("Air", air_sld.real(), air_sld.imag());
    complex_t sub_sld = getSLDFromN(m_wavelength, 6e-6, 2e-8);
    Material substrate_material = MaterialBySLD("Substrate", sub_sld.real(), sub_sld.imag());

    double eff_vol = m_par_surf_density * M_PI * m_radius * m_radius;
    complex_t par_sld = getSLDFromN(m_wavelength, 6e-4, 2e-8);
    complex_t avr_sld = averageSLD(par_sld, air_sld, eff_vol);
    Material avr_material = MaterialBySLD("Avr", avr_sld.real(), avr_sld.imag());

    Layer air_layer(air_material);
    Layer avr_layer(avr_material, m_height / m_n_slices);
    Layer substrate_layer(substrate_material);

    multi_layer->addLayer(air_layer);
    for (size_t i = 0; i < m_n_slices; ++i)
        multi_layer->addLayer(avr_layer);
    multi_layer->addLayer(substrate_layer);

    return multi_layer;
}

namespace
{
complex_t getSLDFromN(double wavelength, double delta, double beta)
{
    complex_t result{2 * delta - delta * delta + beta * beta, 2 * beta - 2 * delta * beta};
    return result * M_PI / (wavelength * wavelength) * (Units::angstrom * Units::angstrom);
}

complex_t averageSLD(complex_t sld_p, complex_t sld_l, double eff_vol)
{
    return sld_l + eff_vol * (sld_p - sld_l);
}
} // namespace
