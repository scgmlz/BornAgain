//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Sample/FFCompute/ComputeDWBA.h
//! @brief     Defines class ComputeDWBA.
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
#ifndef BORNAGAIN_SAMPLE_FFCOMPUTE_COMPUTEDWBA_H
#define BORNAGAIN_SAMPLE_FFCOMPUTE_COMPUTEDWBA_H

#include "Sample/FFCompute/IComputeFF.h"
#include <memory>

class ILayerRTCoefficients;

//! Provides scalar DWBA computation for given IFormFactor.

//! @ingroup formfactors_internal

class ComputeDWBA : public IComputeFF {
public:
    ComputeDWBA(const IFormFactor& ff);
    ~ComputeDWBA() override;

    ComputeDWBA* clone() const override;

    //! Returns the coherent sum of the four DWBA terms for scalar scattering.
    complex_t evaluate(const WavevectorInfo& wavevectors) const override;

    void setSpecularInfo(std::unique_ptr<const ILayerRTCoefficients> p_in_coeffs,
                         std::unique_ptr<const ILayerRTCoefficients> p_out_coeffs) override;

    friend class TestPolarizedDWBATerms;

private:
    std::unique_ptr<const ILayerRTCoefficients> m_in_coeffs;
    std::unique_ptr<const ILayerRTCoefficients> m_out_coeffs;
};

#endif // BORNAGAIN_SAMPLE_FFCOMPUTE_COMPUTEDWBA_H
#endif // USER_API
