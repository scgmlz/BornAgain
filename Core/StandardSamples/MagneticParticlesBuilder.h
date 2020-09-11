// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/StandardSamples/MagneticParticlesBuilder.h
//! @brief    Defines class to build magnetic samples
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_CORE_STANDARDSAMPLES_MAGNETICPARTICLESBUILDER_H
#define BORNAGAIN_CORE_STANDARDSAMPLES_MAGNETICPARTICLESBUILDER_H

#include "Core/Multilayer/IMultiLayerBuilder.h"

class ISample;

//! Builds sample: cylinders with magnetic material and zero magnetic field.
//! @ingroup standard_samples

class BA_CORE_API_ MagneticParticleZeroFieldBuilder : public IMultiLayerBuilder
{
public:
    MagneticParticleZeroFieldBuilder();
    MultiLayer* buildSample() const;

private:
    double m_cylinder_radius;
    double m_cylinder_height;
};

//! Builds sample: cylinders with magnetic material and non-zero magnetic field.
//! @ingroup standard_samples

class BA_CORE_API_ MagneticCylindersBuilder : public IMultiLayerBuilder
{
public:
    MagneticCylindersBuilder();
    MultiLayer* buildSample() const;

private:
    double m_cylinder_radius;
    double m_cylinder_height;
};

//! Builds sample: spheres with magnetization inside substrate.
//! @ingroup standard_samples

class BA_CORE_API_ MagneticSpheresBuilder : public IMultiLayerBuilder
{
public:
    MagneticSpheresBuilder();
    MultiLayer* buildSample() const;

private:
    double m_sphere_radius;
};

#endif // BORNAGAIN_CORE_STANDARDSAMPLES_MAGNETICPARTICLESBUILDER_H
