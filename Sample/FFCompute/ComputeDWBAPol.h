//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Sample/FFCompute/ComputeDWBAPol.h
//! @brief     Defines class ComputeDWBAPol.
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
#ifndef BORNAGAIN_SAMPLE_FFCOMPUTE_COMPUTEDWBAPOL_H
#define BORNAGAIN_SAMPLE_FFCOMPUTE_COMPUTEDWBAPOL_H

#include "Sample/FFCompute/IComputeFF.h"
#include <memory>

class ILayerRTCoefficients;

//! Provides polarized DWBA computation for given IFormFactor.

//! @ingroup formfactors_internal

class ComputeDWBAPol : public IComputeFF {
public:
    ComputeDWBAPol(const IFormFactor& ff);
    ~ComputeDWBAPol() override;

    ComputeDWBAPol* clone() const override;

    //! Throws not-implemented exception.
    complex_t evaluate(const WavevectorInfo& wavevectors) const override;

    //! Returns the coherent sum of the four DWBA terms for polarized scattering.
    Eigen::Matrix2cd evaluatePol(const WavevectorInfo& wavevectors) const override;

    void setSpecularInfo(std::unique_ptr<const ILayerRTCoefficients> p_in_coeffs,
                         std::unique_ptr<const ILayerRTCoefficients> p_out_coeffs) override;

    friend class TestPolarizedDWBATerms;

private:
    std::unique_ptr<const ILayerRTCoefficients> m_in_coeffs;
    std::unique_ptr<const ILayerRTCoefficients> m_out_coeffs;
};

#endif // BORNAGAIN_SAMPLE_FFCOMPUTE_COMPUTEDWBAPOL_H
#endif // USER_API
