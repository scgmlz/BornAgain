//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Sample/FFCompute/ComputeDWBAPol.cpp
//! @brief     Defines class ComputeDWBAPol.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "Sample/FFCompute/ComputeDWBAPol.h"
#include "Sample/Material/WavevectorInfo.h"
#include "Sample/RT/ILayerRTCoefficients.h"
#include "Sample/Scattering/IFormFactor.h"

namespace {
complex_t VecMatVecProduct(const Eigen::Vector2cd& vec1, const Eigen::Matrix2cd& ff,
                           const Eigen::Vector2cd& vec2) {
    return vec1.transpose() * ff * vec2;
}
} // namespace

ComputeDWBAPol::ComputeDWBAPol(const IFormFactor& ff) : IComputeFF(ff) {}

ComputeDWBAPol::~ComputeDWBAPol() = default;

ComputeDWBAPol* ComputeDWBAPol::clone() const {
    ComputeDWBAPol* p_result = new ComputeDWBAPol(*m_ff);
    std::unique_ptr<const ILayerRTCoefficients> p_in_coefs =
        m_in_coeffs ? std::unique_ptr<const ILayerRTCoefficients>(m_in_coeffs->clone()) : nullptr;
    std::unique_ptr<const ILayerRTCoefficients> p_out_coefs =
        m_out_coeffs ? std::unique_ptr<const ILayerRTCoefficients>(m_out_coeffs->clone()) : nullptr;
    p_result->setSpecularInfo(std::move(p_in_coefs), std::move(p_out_coefs));
    return p_result;
}

complex_t ComputeDWBAPol::evaluate(const WavevectorInfo&) const {
    throw std::runtime_error("Bug: forbidden call of ComputeDWBAPol::evaluate");
}

Eigen::Matrix2cd ComputeDWBAPol::evaluatePol(const WavevectorInfo& wavevectors) const {
    // the required wavevectors inside the layer for
    // different eigenmodes and in- and outgoing wavevector;
    complex_t kix = wavevectors.getKi().x();
    complex_t kiy = wavevectors.getKi().y();
    cvector_t ki_1R(kix, kiy, m_in_coeffs->getKz()(0));
    cvector_t ki_1T(kix, kiy, -m_in_coeffs->getKz()(0));
    cvector_t ki_2R(kix, kiy, m_in_coeffs->getKz()(1));
    cvector_t ki_2T(kix, kiy, -m_in_coeffs->getKz()(1));

    cvector_t kf_1R = wavevectors.getKf();
    kf_1R.setZ(-(complex_t)m_out_coeffs->getKz()(0));
    cvector_t kf_1T = kf_1R;
    kf_1T.setZ((complex_t)m_out_coeffs->getKz()(0));
    cvector_t kf_2R = kf_1R;
    kf_2R.setZ(-(complex_t)m_out_coeffs->getKz()(1));
    cvector_t kf_2T = kf_1R;
    kf_2T.setZ((complex_t)m_out_coeffs->getKz()(1));
    // now each of the 16 matrix terms of the polarized DWBA is calculated:
    // NOTE: when the underlying reflection/transmission coefficients are
    // scalar, the eigenmodes have identical eigenvalues and spin polarization
    // is used as a basis; in this case however the matrices get mixed:
    //     real m_M11 = calculated m_M12
    //     real m_M12 = calculated m_M11
    //     real m_M21 = calculated m_M22
    //     real m_M22 = calculated m_M21
    // since both eigenvalues are identical, this does not influence the result.
    Eigen::Matrix2cd ff_BA;

    double wavelength = wavevectors.wavelength();

    // The following matrices each contain the four polarization conditions
    // (p->p, p->m, m->p, m->m)
    // The first two indices indicate a scattering from the 1/2 eigenstate into
    // the 1/2 eigenstate, while the capital indices indicate a reflection
    // before and/or after the scattering event (first index is in-state,
    // second is out-state; this also applies to the internal matrix indices)
    Eigen::Matrix2cd M11_S, M11_RS, M11_SR, M11_RSR, M12_S, M12_RS, M12_SR, M12_RSR, M21_S, M21_RS,
        M21_SR, M21_RSR, M22_S, M22_RS, M22_SR, M22_RSR;

    // eigenmode 1 -> eigenmode 1: direct scattering
    ff_BA = m_ff->evaluatePol(WavevectorInfo(ki_1T, kf_1T, wavelength));
    M11_S(0, 0) = -VecMatVecProduct(m_out_coeffs->T1min(), ff_BA, m_in_coeffs->T1plus());
    M11_S(0, 1) = VecMatVecProduct(m_out_coeffs->T1plus(), ff_BA, m_in_coeffs->T1plus());
    M11_S(1, 0) = -VecMatVecProduct(m_out_coeffs->T1min(), ff_BA, m_in_coeffs->T1min());
    M11_S(1, 1) = VecMatVecProduct(m_out_coeffs->T1plus(), ff_BA, m_in_coeffs->T1min());
    // eigenmode 1 -> eigenmode 1: reflection and then scattering
    ff_BA = m_ff->evaluatePol(WavevectorInfo(ki_1R, kf_1T, wavelength));
    M11_RS(0, 0) = -VecMatVecProduct(m_out_coeffs->T1min(), ff_BA, m_in_coeffs->R1plus());
    M11_RS(0, 1) = VecMatVecProduct(m_out_coeffs->T1plus(), ff_BA, m_in_coeffs->R1plus());
    M11_RS(1, 0) = -VecMatVecProduct(m_out_coeffs->T1min(), ff_BA, m_in_coeffs->R1min());
    M11_RS(1, 1) = VecMatVecProduct(m_out_coeffs->T1plus(), ff_BA, m_in_coeffs->R1min());
    // eigenmode 1 -> eigenmode 1: scattering and then reflection
    ff_BA = m_ff->evaluatePol(WavevectorInfo(ki_1T, kf_1R, wavelength));
    M11_SR(0, 0) = -VecMatVecProduct(m_out_coeffs->R1min(), ff_BA, m_in_coeffs->T1plus());
    M11_SR(0, 1) = VecMatVecProduct(m_out_coeffs->R1plus(), ff_BA, m_in_coeffs->T1plus());
    M11_SR(1, 0) = -VecMatVecProduct(m_out_coeffs->R1min(), ff_BA, m_in_coeffs->T1min());
    M11_SR(1, 1) = VecMatVecProduct(m_out_coeffs->R1plus(), ff_BA, m_in_coeffs->T1min());
    // eigenmode 1 -> eigenmode 1: reflection, scattering and again reflection
    ff_BA = m_ff->evaluatePol(WavevectorInfo(ki_1R, kf_1R, wavelength));
    M11_RSR(0, 0) = -VecMatVecProduct(m_out_coeffs->R1min(), ff_BA, m_in_coeffs->R1plus());
    M11_RSR(0, 1) = VecMatVecProduct(m_out_coeffs->R1plus(), ff_BA, m_in_coeffs->R1plus());
    M11_RSR(1, 0) = -VecMatVecProduct(m_out_coeffs->R1min(), ff_BA, m_in_coeffs->R1min());
    M11_RSR(1, 1) = VecMatVecProduct(m_out_coeffs->R1plus(), ff_BA, m_in_coeffs->R1min());

    // eigenmode 1 -> eigenmode 2: direct scattering
    ff_BA = m_ff->evaluatePol(WavevectorInfo(ki_1T, kf_2T, wavelength));
    M12_S(0, 0) = -VecMatVecProduct(m_out_coeffs->T2min(), ff_BA, m_in_coeffs->T1plus());
    M12_S(0, 1) = VecMatVecProduct(m_out_coeffs->T2plus(), ff_BA, m_in_coeffs->T1plus());
    M12_S(1, 0) = -VecMatVecProduct(m_out_coeffs->T2min(), ff_BA, m_in_coeffs->T1min());
    M12_S(1, 1) = VecMatVecProduct(m_out_coeffs->T2plus(), ff_BA, m_in_coeffs->T1min());
    // eigenmode 1 -> eigenmode 2: reflection and then scattering
    ff_BA = m_ff->evaluatePol(WavevectorInfo(ki_1R, kf_2T, wavelength));
    M12_RS(0, 0) = -VecMatVecProduct(m_out_coeffs->T2min(), ff_BA, m_in_coeffs->R1plus());
    M12_RS(0, 1) = VecMatVecProduct(m_out_coeffs->T2plus(), ff_BA, m_in_coeffs->R1plus());
    M12_RS(1, 0) = -VecMatVecProduct(m_out_coeffs->T2min(), ff_BA, m_in_coeffs->R1min());
    M12_RS(1, 1) = VecMatVecProduct(m_out_coeffs->T2plus(), ff_BA, m_in_coeffs->R1min());
    // eigenmode 1 -> eigenmode 2: scattering and then reflection
    ff_BA = m_ff->evaluatePol(WavevectorInfo(ki_1T, kf_2R, wavelength));
    M12_SR(0, 0) = -VecMatVecProduct(m_out_coeffs->R2min(), ff_BA, m_in_coeffs->T1plus());
    M12_SR(0, 1) = VecMatVecProduct(m_out_coeffs->R2plus(), ff_BA, m_in_coeffs->T1plus());
    M12_SR(1, 0) = -VecMatVecProduct(m_out_coeffs->R2min(), ff_BA, m_in_coeffs->T1min());
    M12_SR(1, 1) = VecMatVecProduct(m_out_coeffs->R2plus(), ff_BA, m_in_coeffs->T1min());
    // eigenmode 1 -> eigenmode 2: reflection, scattering and again reflection
    ff_BA = m_ff->evaluatePol(WavevectorInfo(ki_1R, kf_2R, wavelength));
    M12_RSR(0, 0) = -VecMatVecProduct(m_out_coeffs->R2min(), ff_BA, m_in_coeffs->R1plus());
    M12_RSR(0, 1) = VecMatVecProduct(m_out_coeffs->R2plus(), ff_BA, m_in_coeffs->R1plus());
    M12_RSR(1, 0) = -VecMatVecProduct(m_out_coeffs->R2min(), ff_BA, m_in_coeffs->R1min());
    M12_RSR(1, 1) = VecMatVecProduct(m_out_coeffs->R2plus(), ff_BA, m_in_coeffs->R1min());

    // eigenmode 2 -> eigenmode 1: direct scattering
    ff_BA = m_ff->evaluatePol(WavevectorInfo(ki_2T, kf_1T, wavelength));
    M21_S(0, 0) = -VecMatVecProduct(m_out_coeffs->T1min(), ff_BA, m_in_coeffs->T2plus());
    M21_S(0, 1) = VecMatVecProduct(m_out_coeffs->T1plus(), ff_BA, m_in_coeffs->T2plus());
    M21_S(1, 0) = -VecMatVecProduct(m_out_coeffs->T1min(), ff_BA, m_in_coeffs->T2min());
    M21_S(1, 1) = VecMatVecProduct(m_out_coeffs->T1plus(), ff_BA, m_in_coeffs->T2min());
    // eigenmode 2 -> eigenmode 1: reflection and then scattering
    ff_BA = m_ff->evaluatePol(WavevectorInfo(ki_2R, kf_1T, wavelength));
    M21_RS(0, 0) = -VecMatVecProduct(m_out_coeffs->T1min(), ff_BA, m_in_coeffs->R2plus());
    M21_RS(0, 1) = VecMatVecProduct(m_out_coeffs->T1plus(), ff_BA, m_in_coeffs->R2plus());
    M21_RS(1, 0) = -VecMatVecProduct(m_out_coeffs->T1min(), ff_BA, m_in_coeffs->R2min());
    M21_RS(1, 1) = VecMatVecProduct(m_out_coeffs->T1plus(), ff_BA, m_in_coeffs->R2min());
    // eigenmode 2 -> eigenmode 1: scattering and then reflection
    ff_BA = m_ff->evaluatePol(WavevectorInfo(ki_2T, kf_1R, wavelength));
    M21_SR(0, 0) = -VecMatVecProduct(m_out_coeffs->R1min(), ff_BA, m_in_coeffs->T2plus());
    M21_SR(0, 1) = VecMatVecProduct(m_out_coeffs->R1plus(), ff_BA, m_in_coeffs->T2plus());
    M21_SR(1, 0) = -VecMatVecProduct(m_out_coeffs->R1min(), ff_BA, m_in_coeffs->T2min());
    M21_SR(1, 1) = VecMatVecProduct(m_out_coeffs->R1plus(), ff_BA, m_in_coeffs->T2min());
    // eigenmode 2 -> eigenmode 1: reflection, scattering and again reflection
    ff_BA = m_ff->evaluatePol(WavevectorInfo(ki_2R, kf_1R, wavelength));
    M21_RSR(0, 0) = -VecMatVecProduct(m_out_coeffs->R1min(), ff_BA, m_in_coeffs->R2plus());
    M21_RSR(0, 1) = VecMatVecProduct(m_out_coeffs->R1plus(), ff_BA, m_in_coeffs->R2plus());
    M21_RSR(1, 0) = -VecMatVecProduct(m_out_coeffs->R1min(), ff_BA, m_in_coeffs->R2min());
    M21_RSR(1, 1) = VecMatVecProduct(m_out_coeffs->R1plus(), ff_BA, m_in_coeffs->R2min());

    // eigenmode 2 -> eigenmode 2: direct scattering
    ff_BA = m_ff->evaluatePol(WavevectorInfo(ki_2T, kf_2T, wavelength));
    M22_S(0, 0) = -VecMatVecProduct(m_out_coeffs->T2min(), ff_BA, m_in_coeffs->T2plus());
    M22_S(0, 1) = VecMatVecProduct(m_out_coeffs->T2plus(), ff_BA, m_in_coeffs->T2plus());
    M22_S(1, 0) = -VecMatVecProduct(m_out_coeffs->T2min(), ff_BA, m_in_coeffs->T2min());
    M22_S(1, 1) = VecMatVecProduct(m_out_coeffs->T2plus(), ff_BA, m_in_coeffs->T2min());
    // eigenmode 2 -> eigenmode 2: reflection and then scattering
    ff_BA = m_ff->evaluatePol(WavevectorInfo(ki_2R, kf_2T, wavelength));
    M22_RS(0, 0) = -VecMatVecProduct(m_out_coeffs->T2min(), ff_BA, m_in_coeffs->R2plus());
    M22_RS(0, 1) = VecMatVecProduct(m_out_coeffs->T2plus(), ff_BA, m_in_coeffs->R2plus());
    M22_RS(1, 0) = -VecMatVecProduct(m_out_coeffs->T2min(), ff_BA, m_in_coeffs->R2min());
    M22_RS(1, 1) = VecMatVecProduct(m_out_coeffs->T2plus(), ff_BA, m_in_coeffs->R2min());
    // eigenmode 2 -> eigenmode 2: scattering and then reflection
    ff_BA = m_ff->evaluatePol(WavevectorInfo(ki_2T, kf_2R, wavelength));
    M22_SR(0, 0) = -VecMatVecProduct(m_out_coeffs->R2min(), ff_BA, m_in_coeffs->T2plus());
    M22_SR(0, 1) = VecMatVecProduct(m_out_coeffs->R2plus(), ff_BA, m_in_coeffs->T2plus());
    M22_SR(1, 0) = -VecMatVecProduct(m_out_coeffs->R2min(), ff_BA, m_in_coeffs->T2min());
    M22_SR(1, 1) = VecMatVecProduct(m_out_coeffs->R2plus(), ff_BA, m_in_coeffs->T2min());
    // eigenmode 2 -> eigenmode 2: reflection, scattering and again reflection
    ff_BA = m_ff->evaluatePol(WavevectorInfo(ki_2R, kf_2R, wavelength));
    M22_RSR(0, 0) = -VecMatVecProduct(m_out_coeffs->R2min(), ff_BA, m_in_coeffs->R2plus());
    M22_RSR(0, 1) = VecMatVecProduct(m_out_coeffs->R2plus(), ff_BA, m_in_coeffs->R2plus());
    M22_RSR(1, 0) = -VecMatVecProduct(m_out_coeffs->R2min(), ff_BA, m_in_coeffs->R2min());
    M22_RSR(1, 1) = VecMatVecProduct(m_out_coeffs->R2plus(), ff_BA, m_in_coeffs->R2min());

    return M11_S + M11_RS + M11_SR + M11_RSR + M12_S + M12_RS + M12_SR + M12_RSR + M21_S + M21_RS
           + M21_SR + M21_RSR + M22_S + M22_RS + M22_SR + M22_RSR;
}

void ComputeDWBAPol::setSpecularInfo(std::unique_ptr<const ILayerRTCoefficients> p_in_coeffs,
                                     std::unique_ptr<const ILayerRTCoefficients> p_out_coeffs) {
    m_in_coeffs = std::move(p_in_coeffs);
    m_out_coeffs = std::move(p_out_coeffs);
}
