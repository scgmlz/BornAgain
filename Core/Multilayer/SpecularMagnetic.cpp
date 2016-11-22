// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Multilayer/SpecularMagnetic.cpp
//! @brief     Implements class SpecularMagnetic.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "SpecularMagnetic.h"
#include "Layer.h"
#include "LayerInterface.h"
#include "IMaterial.h"
#include "MultiLayer.h"
#include <Eigen/LU>

static complex_t I(0.,1.);

void SpecularMagnetic::execute(
    const MultiLayer& sample, const kvector_t k, MultiLayerCoeff_t& coeff)
{
    coeff.clear();
    coeff.resize(sample.getNumberOfLayers());

    calculateEigenvalues(sample, k, coeff);

    calculateTransferAndBoundary(sample, k, coeff);
}

void SpecularMagnetic::calculateEigenvalues(
    const MultiLayer& sample, const kvector_t k, MultiLayerCoeff_t& coeff)
{
    double mag_k = k.mag();
    double sign_kz = k.z() > 0.0 ? -1.0 : 1.0;
    for(size_t i=0; i<coeff.size(); ++i) {
        coeff[i].m_scatt_matrix = sample.getLayer(i)->getMaterial()->
                getSpecularScatteringMatrix(k);
        coeff[i].m_kt = mag_k*sample.getLayer(i)->getThickness();
        coeff[i].m_a = coeff[i].m_scatt_matrix.trace()/2.0;
        coeff[i].m_b_mag = sqrt(coeff[i].m_a*coeff[i].m_a -
                (complex_t)coeff[i].m_scatt_matrix.determinant());
        coeff[i].m_bz = ( coeff[i].m_scatt_matrix(0,0) -
                coeff[i].m_scatt_matrix(1,1) )/2.0;
        complex_t rad0 = coeff[i].m_a - coeff[i].m_b_mag;
        complex_t rad1 = coeff[i].m_a + coeff[i].m_b_mag;
        // use small absorptive component for layers with i>0 if radicand becomes very small:
        if (i>0) {
            if (std::abs(rad0)<1e-40) rad0 = I*1e-40;
            if (std::abs(rad1)<1e-40) rad1 = I*1e-40;
        }
        coeff[i].lambda(0) = sqrt(rad0);
        coeff[i].lambda(1) = sqrt(rad1);
        coeff[i].kz = mag_k * coeff[i].lambda * sign_kz;
    }
}

// todo: avoid overflows (see SpecularMatrix.cpp)
void SpecularMagnetic::calculateTransferAndBoundary(
    const MultiLayer& sample, const kvector_t k, MultiLayerCoeff_t& coeff)
{
    (void)k;
    size_t N = coeff.size();
    if (coeff[0].lambda == Eigen::Vector2cd::Zero() && N>1) {
        setForNoTransmission(coeff);
        return;
    }

    // First, initialize bottom layer values to have no reflection
    coeff[N-1].initializeBottomLayerPhiPsi();

    coeff[0].calculateTRMatrices();
    for (int i=(int)N-2; i>0; --i) {
        double t = sample.getLayer(i)->getThickness();
        coeff[i].calculateTRMatrices();
        Eigen::Matrix4cd l =
               coeff[i].R1m * getImExponential((complex_t)(coeff[i].kz(0)*t)) +
               coeff[i].T1m * getImExponential((complex_t)(-coeff[i].kz(0)*t)) +
               coeff[i].R2m * getImExponential((complex_t)(coeff[i].kz(1)*t)) +
               coeff[i].T2m * getImExponential((complex_t)(-coeff[i].kz(1)*t));
        coeff[i].phi_psi_plus = l * coeff[i+1].phi_psi_plus;
        coeff[i].phi_psi_min = l * coeff[i+1].phi_psi_min;
    }
    // If more than one layer, impose normalization and correct correspondence
    // for spin-z polarization in top layer
    if (N>1) {
        // First layer boundary is also top layer boundary:
        coeff[0].phi_psi_plus = coeff[1].phi_psi_plus;
        coeff[0].phi_psi_min = coeff[1].phi_psi_min;
        // Normalize all boundary values such that top layer has unit wave
        // amplitude for both spin up and down (and does not contain a
        // transmitted wave amplitude for the opposite polarization)
        Eigen::Vector2cd T0basisA = coeff[0].T1plus() + coeff[0].T2plus();
        Eigen::Vector2cd T0basisB = coeff[0].T1min() + coeff[0].T2min();
        complex_t cpA, cpB, cmA, cmB;
        cpA = T0basisB(1);
        cpB = -T0basisA(1);
        cmA = T0basisB(0);
        cmB = -T0basisA(0);
        Eigen::Vector4cd phipsitemp = cpA * coeff[0].phi_psi_plus +
                cpB * coeff[0].phi_psi_min;
        coeff[0].phi_psi_min = cmA * coeff[0].phi_psi_plus +
                cmB * coeff[0].phi_psi_min;
        coeff[0].phi_psi_plus = phipsitemp;
        Eigen::Vector2cd T0plusV = coeff[0].T1plus() + coeff[0].T2plus();
        Eigen::Vector2cd T0minV = coeff[0].T1min() + coeff[0].T2min();
        complex_t T0plus = T0plusV(0);
        complex_t T0min = T0minV(1);
        coeff[0].phi_psi_min = coeff[0].phi_psi_min / T0min;
        coeff[0].phi_psi_plus = coeff[0].phi_psi_plus / T0plus;
        for (size_t i=1; i<N; ++i) {
            phipsitemp = ( cpA * coeff[i].phi_psi_plus +
                    cpB * coeff[i].phi_psi_min ) / T0plus;
            coeff[i].phi_psi_min = ( cmA * coeff[i].phi_psi_plus +
                    cmB * coeff[i].phi_psi_min ) / T0min;
            coeff[i].phi_psi_plus = phipsitemp;
        }
    }
}

void SpecularMagnetic::setForNoTransmission(MultiLayerCoeff_t& coeff)
{
    size_t N = coeff.size();
    for (size_t i=0; i<N; ++i) {
        coeff[i].phi_psi_plus.setZero();
        coeff[i].phi_psi_min.setZero();
        coeff[i].T1m = Eigen::Matrix4cd::Identity()/4.0;
        coeff[i].R1m = coeff[i].T1m;
        coeff[i].T2m = coeff[i].T1m;
        coeff[i].R2m = coeff[i].T1m;
    }
}

complex_t SpecularMagnetic::getImExponential(complex_t exponent)
{
    if (exponent.imag() > -std::log(std::numeric_limits<double>::min()) )
        return 0.0;
    return std::exp(I*exponent);
}
