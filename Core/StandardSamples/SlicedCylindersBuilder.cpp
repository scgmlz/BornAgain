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
const double height(5 * Units::nanometer);
const double radius(5 * Units::nanometer);
const double wavelength(0.154); // nm
const int n_slices(3);

//! Returns SLD input (in inverse square Angstroms) for MaterialBySLD from _delta_ and _beta_,
//! i.e. the input for HomogeneousMaterial.
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

MultiLayer* SlicedCylindersBuilder::buildSample() const
{
    Material vacuum_material = HomogeneousMaterial("Vacuum", 0.0, 0.0);
    Material substrate_material = HomogeneousMaterial("Substrate", 6e-6, 2e-8);
    Material particle_material = HomogeneousMaterial("Particle", 6e-4, 2e-8);

    Layer vacuum_layer(vacuum_material);
    Layer substrate_layer(substrate_material);

    FormFactorCylinder ff_cylinder(radius, height);

    Particle particle(particle_material, ff_cylinder);
    ParticleLayout particle_layout(particle);

    vacuum_layer.addLayout(particle_layout);
    vacuum_layer.setNumberOfSlices(n_slices);

    MultiLayer* multi_layer = new MultiLayer();
    multi_layer->addLayer(vacuum_layer);
    multi_layer->addLayer(substrate_layer);
    return multi_layer;
}

MultiLayer* SLDSlicedCylindersBuilder::buildSample() const
{
    Material vacuum_material = MaterialBySLD("Vacuum", 0.0, 0.0);
    complex_t sub_sld = getSLDFromN(wavelength, 6e-6, 2e-8);
    Material substrate_material = MaterialBySLD("Substrate", sub_sld.real(), sub_sld.imag());
    complex_t par_sld = getSLDFromN(wavelength, 6e-4, 2e-8);
    Material particle_material = MaterialBySLD("Particle", par_sld.real(), par_sld.imag());

    Layer vacuum_layer(vacuum_material);
    Layer substrate_layer(substrate_material);

    FormFactorCylinder ff_cylinder(radius, height);

    Particle particle(particle_material, ff_cylinder);
    ParticleLayout particle_layout(particle);

    vacuum_layer.addLayout(particle_layout);
    vacuum_layer.setNumberOfSlices(n_slices);

    MultiLayer* multi_layer = new MultiLayer();
    multi_layer->addLayer(vacuum_layer);
    multi_layer->addLayer(substrate_layer);
    return multi_layer;
}

MultiLayer* AveragedSlicedCylindersBuilder::buildSample() const
{
    const auto par_surf_density = ParticleLayout().totalParticleSurfaceDensity();

    complex_t vacuum_sld{0.0, 0.0};
    Material vacuum_material = MaterialBySLD("Vacuum", vacuum_sld.real(), vacuum_sld.imag());
    complex_t sub_sld = getSLDFromN(wavelength, 6e-6, 2e-8);
    Material substrate_material = MaterialBySLD("Substrate", sub_sld.real(), sub_sld.imag());

    double eff_vol = par_surf_density * M_PI * radius * radius;
    complex_t par_sld = getSLDFromN(wavelength, 6e-4, 2e-8);
    complex_t avr_sld = averageSLD(par_sld, vacuum_sld, eff_vol);
    Material avr_material = MaterialBySLD("Avr", avr_sld.real(), avr_sld.imag());

    Layer vacuum_layer(vacuum_material);
    Layer avr_layer(avr_material, height / n_slices);
    Layer substrate_layer(substrate_material);

    MultiLayer* multi_layer = new MultiLayer();
    multi_layer->addLayer(vacuum_layer);
    for (size_t i = 0; i < n_slices; ++i)
        multi_layer->addLayer(avr_layer);
    multi_layer->addLayer(substrate_layer);
    return multi_layer;
}
