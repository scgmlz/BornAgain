//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Sample/StandardSamples/ReferenceMaterials.h
//! @brief     Defines materials in namespace refMat.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifdef SWIG
#error no need to expose this header to Swig
#endif

#ifndef USER_API
#ifndef BORNAGAIN_SAMPLE_STANDARDSAMPLES_REFERENCEMATERIALS_H
#define BORNAGAIN_SAMPLE_STANDARDSAMPLES_REFERENCEMATERIALS_H

#include "Sample/Material/MaterialFactoryFuncs.h"

//! Reference materials for use in tests and exemplary samples.

namespace refMat {

static const Material Vacuum = HomogeneousMaterial("Vacuum", 0.0, 0.0);
static const Material Substrate = HomogeneousMaterial("Substrate", 6e-6, 2e-8);
static const Material Particle = HomogeneousMaterial("Particle", 6e-4, 2e-8);

static const Material Ag = HomogeneousMaterial("Ag", 1.245e-5, 5.419e-7);
static const Material AgO2 = HomogeneousMaterial("AgO2", 8.600e-6, 3.442e-7);
static const Material Teflon = HomogeneousMaterial("Teflon", 2.900e-6, 6.019e-9);

static const Material Substrate2 = HomogeneousMaterial("Substrate2", 3.212e-6, 3.244e-8);

} // namespace refMat

#endif // BORNAGAIN_SAMPLE_STANDARDSAMPLES_REFERENCEMATERIALS_H
#endif // USER_API
