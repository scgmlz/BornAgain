// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Computation/RoughMultiLayerComputation.cpp
//! @brief     Implements class RoughMultiLayerComputation.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "RoughMultiLayerComputation.h"
#include "Faddeeva.hh"
#include "ILayerRTCoefficients.h"
#include "Layer.h"
#include "LayerInterface.h"
#include "LayerRoughness.h"
#include "LayerSpecularInfo.h"
#include "MathConstants.h"
#include "MultiLayer.h"
#include "ProgressHandler.h"
#include "SimulationElement.h"

// Diffuse scattering from rough interfaces is modelled after
// Phys. Rev. B, vol. 51 (4), p. 2311 (1995)

namespace
{
complex_t h_plus(complex_t z) { return 0.5 * Faddeeva::erfcx(-mul_I(z) / std::sqrt(2.0)); }
complex_t h_min(complex_t z) { return 0.5 * Faddeeva::erfcx(mul_I(z) / std::sqrt(2.0)); }
}

RoughMultiLayerComputation::RoughMultiLayerComputation(const MultiLayer* p_multi_layer)
    : mp_multi_layer(p_multi_layer)
{
    mp_specular_info_vector.resize(p_multi_layer->getNumberOfLayers(), 0);
}

RoughMultiLayerComputation::~RoughMultiLayerComputation()
{
    for (size_t i = 0; i < mp_specular_info_vector.size(); ++i)
        delete mp_specular_info_vector[i];
}

//! Calls evaluate on range of simulation elements; returns true if computation shall continue
void RoughMultiLayerComputation::eval(
    ProgressHandler* progress, const std::vector<SimulationElement>::iterator& begin_it,
    const std::vector<SimulationElement>::iterator& end_it)
{
    InnerCounter counter;
    for (std::vector<SimulationElement>::iterator it = begin_it; it != end_it; ++it) {
        if (!progress->alive())
            return;
        it->setIntensity(evaluate(*it));
        counter.stepProgress(progress);
    }
}

double RoughMultiLayerComputation::evaluate(const SimulationElement& sim_element)
{
    if (sim_element.getAlphaMean() < 0.0)
        return 0.0;
    kvector_t q = sim_element.getMeanQ();
    double wavelength = sim_element.getWavelength();
    double autocorr(0.0);
    complex_t crosscorr(0.0, 0.0);

    std::vector<complex_t> rterm(mp_multi_layer->getNumberOfLayers() - 1);
    std::vector<complex_t> sterm(mp_multi_layer->getNumberOfLayers() - 1);

    for (size_t i = 0; i < mp_multi_layer->getNumberOfLayers() - 1; i++) {
        rterm[i] = get_refractive_term(i);
        sterm[i] = get_sum8terms(i, sim_element);
    }

    for (size_t i = 0; i < mp_multi_layer->getNumberOfLayers() - 1; i++) {
        const LayerRoughness* rough = mp_multi_layer->getLayerBottomInterface(i)->getRoughness();
        if (rough)
            autocorr += std::norm(rterm[i]) * std::norm(sterm[i]) * rough->getSpectralFun(q);
    }

    // cross correlation between layers
    if (mp_multi_layer->getCrossCorrLength() != 0.0) {
        for (size_t j = 0; j < mp_multi_layer->getNumberOfLayers() - 1; j++) {
            for (size_t k = 0; k < mp_multi_layer->getNumberOfLayers() - 1; k++) {
                if (j == k)
                    continue;
                crosscorr += rterm[j] * sterm[j] * mp_multi_layer->getCrossCorrSpectralFun(q, j, k)
                    * std::conj(rterm[k]) * std::conj(sterm[k]);
            }
        }
    }

    //! @TODO clarify complex vs double
    return (autocorr + crosscorr.real()) * M_PI / 4. / wavelength / wavelength;
}

complex_t RoughMultiLayerComputation::get_refractive_term(size_t ilayer) const
{
    return mp_multi_layer->getLayer(ilayer)->getRefractiveIndex2()
        - mp_multi_layer->getLayer(ilayer + 1)->getRefractiveIndex2();
}

complex_t
RoughMultiLayerComputation::get_sum8terms(size_t ilayer, const SimulationElement& sim_element)
{
    const std::unique_ptr<const ILayerRTCoefficients> P_in_plus(
        mp_specular_info_vector[ilayer]->getInCoefficients(sim_element));
    const std::unique_ptr<const ILayerRTCoefficients> P_out_plus(
        mp_specular_info_vector[ilayer]->getOutCoefficients(sim_element));

    const std::unique_ptr<const ILayerRTCoefficients> P_in_minus(
        mp_specular_info_vector[ilayer + 1]->getInCoefficients(sim_element));
    const std::unique_ptr<const ILayerRTCoefficients> P_out_minus(
        mp_specular_info_vector[ilayer + 1]->getOutCoefficients(sim_element));

    complex_t kiz_plus = P_in_plus->getScalarKz();
    complex_t kfz_plus = P_out_plus->getScalarKz();
    complex_t qz1_plus = -kiz_plus - kfz_plus;
    complex_t qz2_plus = -kiz_plus + kfz_plus;
    complex_t qz3_plus = -qz2_plus;
    complex_t qz4_plus = -qz1_plus;
    double thickness = mp_multi_layer->getLayerThickness(ilayer);
    complex_t T_in_plus = P_in_plus->getScalarT() * exp_I(kiz_plus * thickness);
    complex_t R_in_plus = P_in_plus->getScalarR() * exp_I(-kiz_plus * thickness);
    complex_t T_out_plus = P_out_plus->getScalarT() * exp_I(kfz_plus * thickness);
    complex_t R_out_plus = P_out_plus->getScalarR() * exp_I(-kfz_plus * thickness);

    complex_t kiz_minus = P_in_minus->getScalarKz();
    complex_t kfz_minus = P_out_minus->getScalarKz();
    complex_t qz1_minus = -kiz_minus - kfz_minus;
    complex_t qz2_minus = -kiz_minus + kfz_minus;
    complex_t qz3_minus = -qz2_minus;
    complex_t qz4_minus = -qz1_minus;

    double sigma(0.0);
    if (const LayerRoughness* roughness =
            mp_multi_layer->getLayerBottomInterface(ilayer)->getRoughness())
        sigma = roughness->getSigma();
    complex_t term1 = T_in_plus * T_out_plus * h_plus(qz1_plus * sigma);
    complex_t term2 = T_in_plus * R_out_plus * h_plus(qz2_plus * sigma);
    complex_t term3 = R_in_plus * T_out_plus * h_plus(qz3_plus * sigma);
    complex_t term4 = R_in_plus * R_out_plus * h_plus(qz4_plus * sigma);
    complex_t term5 =
        P_in_minus->getScalarT() * P_out_minus->getScalarT() * h_min(qz1_minus * sigma);
    complex_t term6 =
        P_in_minus->getScalarT() * P_out_minus->getScalarR() * h_min(qz2_minus * sigma);
    complex_t term7 =
        P_in_minus->getScalarR() * P_out_minus->getScalarT() * h_min(qz3_minus * sigma);
    complex_t term8 =
        P_in_minus->getScalarR() * P_out_minus->getScalarR() * h_min(qz4_minus * sigma);

    return term1 + term2 + term3 + term4 + term5 + term6 + term7 + term8;
}

void RoughMultiLayerComputation::setSpecularInfo(
    size_t i_layer, const LayerSpecularInfo& specular_info)
{
    delete mp_specular_info_vector[i_layer];
    mp_specular_info_vector[i_layer] = specular_info.clone();
}
