// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/StandardSamples/CoreShellParticleBuilder.h
//! @brief     Declares class CoreShellParticleBuilder.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef CORESHELLPARTICLEBUILDER_H
#define CORESHELLPARTICLEBUILDER_H


//! @class CoreShellParticleBuilder
//! @ingroup standard_samples
//! @brief Builds sample: Core Shell Nanoparticles (IsGISAXS example #11).

class BA_CORE_API_ CoreShellParticleBuilder : public ISampleBuilder
{
public:
    CoreShellParticleBuilder(){}
    ISample *buildSample() const;
};


//! @class CoreShellBoxRotateZandYBuilder
//! @ingroup standard_samples
//! @brief Rotation and translation of core shell box particle in 3 layers system.

class BA_CORE_API_ CoreShellBoxRotateZandYBuilder : public ISampleBuilder
{
public:
    CoreShellBoxRotateZandYBuilder(){}
    ISample *buildSample() const;
};

#endif // CORESHELLPARTICLEBUILDER_H
