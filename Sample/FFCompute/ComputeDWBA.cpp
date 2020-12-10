//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Sample/FFCompute/ComputeDWBA.cpp
//! @brief     Implements class ComputeDWBA.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "Sample/FFCompute/ComputeDWBA.h"
#include "Sample/Material/WavevectorInfo.h"
#include "Sample/RT/ILayerRTCoefficients.h"
#include "Sample/Scattering/IFormFactor.h"

ComputeDWBA::ComputeDWBA(const IFormFactor& ff) : IComputeFF(ff) {}

ComputeDWBA::~ComputeDWBA() = default;

ComputeDWBA* ComputeDWBA::clone() const {
    ComputeDWBA* result = new ComputeDWBA(*m_ff);
    std::unique_ptr<const ILayerRTCoefficients> p_in_coefs =
        m_in_coeffs ? std::unique_ptr<const ILayerRTCoefficients>(m_in_coeffs->clone()) : nullptr;
    std::unique_ptr<const ILayerRTCoefficients> p_out_coefs =
        m_out_coeffs ? std::unique_ptr<const ILayerRTCoefficients>(m_out_coeffs->clone()) : nullptr;
    result->setSpecularInfo(std::move(p_in_coefs), std::move(p_out_coefs));
    return result;
}

complex_t ComputeDWBA::evaluate(const WavevectorInfo& wavevectors) const {
    // Retrieve the two different incoming wavevectors in the layer
    cvector_t k_i_T = wavevectors.getKi();
    k_i_T.setZ(-m_in_coeffs->getScalarKz());
    cvector_t k_i_R = k_i_T;
    k_i_R.setZ(-k_i_T.z());

    // Retrieve the two different outgoing wavevector bins in the layer
    cvector_t k_f_T = wavevectors.getKf();
    k_f_T.setZ(m_out_coeffs->getScalarKz());
    cvector_t k_f_R = k_f_T;
    k_f_R.setZ(-k_f_T.z());

    // Construct the four different scattering contributions wavevector infos
    double wavelength = wavevectors.wavelength();
    WavevectorInfo k_TT(k_i_T, k_f_T, wavelength);
    WavevectorInfo k_RT(k_i_R, k_f_T, wavelength);
    WavevectorInfo k_TR(k_i_T, k_f_R, wavelength);
    WavevectorInfo k_RR(k_i_R, k_f_R, wavelength);

    // Get the four R,T coefficients
    complex_t T_in = m_in_coeffs->getScalarT();
    complex_t R_in = m_in_coeffs->getScalarR();
    complex_t T_out = m_out_coeffs->getScalarT();
    complex_t R_out = m_out_coeffs->getScalarR();

    // The four different scattering contributions; S stands for scattering
    // off the particle, R for reflection off the layer interface
    complex_t term_S = T_in * m_ff->evaluate(k_TT) * T_out;
    complex_t term_RS = R_in * m_ff->evaluate(k_RT) * T_out;
    complex_t term_SR = T_in * m_ff->evaluate(k_TR) * R_out;
    complex_t term_RSR = R_in * m_ff->evaluate(k_RR) * R_out;

    return term_S + term_RS + term_SR + term_RSR;
}

void ComputeDWBA::setSpecularInfo(std::unique_ptr<const ILayerRTCoefficients> p_in_coeffs,
                                  std::unique_ptr<const ILayerRTCoefficients> p_out_coeffs) {
    m_in_coeffs = std::move(p_in_coeffs);
    m_out_coeffs = std::move(p_out_coeffs);
}
