//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Sample/FFCompute/ComputeBA.h
//! @brief     Defines class ComputeBA.
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
#ifndef BORNAGAIN_SAMPLE_FFCOMPUTE_COMPUTEBA_H
#define BORNAGAIN_SAMPLE_FFCOMPUTE_COMPUTEBA_H

#include "Sample/FFCompute/IComputeFF.h"
#include <memory>

//! Provides scalar form factor evaluation in Born Approximation for given IFormFactor.

//! @ingroup formfactors_internal

class ComputeBA : public IComputeFF {
public:
    ComputeBA(const IFormFactor& ff);
    ~ComputeBA() override;

    ComputeBA* clone() const override;

    //! Calculates and returns a form factor calculation in BA
    complex_t evaluate(const WavevectorInfo& wavevectors) const override;
};

#endif // BORNAGAIN_SAMPLE_FFCOMPUTE_COMPUTEBA_H
#endif // USER_API
