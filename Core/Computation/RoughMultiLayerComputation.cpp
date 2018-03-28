// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Computation/RoughMultiLayerComputation.cpp
//! @brief     Implements class RoughMultiLayerComputation.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "RoughMultiLayerComputation.h"
#include "DelayedProgressCounter.h"
#include "ILayerRTCoefficients.h"
#include "IFresnelMap.h"
#include "Faddeeva.hh"
#include "Layer.h"
#include "LayerInterface.h"
#include "LayerRoughness.h"
#include "MultiLayer.h"
#include "MathConstants.h"
#include "ProgressHandler.h"
#include "SimulationElement.h"

// Diffuse scattering from rough interfaces is modelled after
// Phys. Rev. B, vol. 51 (4), p. 2311 (1995)

namespace {
    complex_t h_plus(complex_t z)
    {
        return 0.5*Faddeeva::erfcx(-mul_I(z)/std::sqrt(2.0));
    }
    complex_t h_min(complex_t z)
    {
        return 0.5*Faddeeva::erfcx(mul_I(z)/std::sqrt(2.0));
    }
}

RoughMultiLayerComputation::RoughMultiLayerComputation(const MultiLayer *p_multi_layer,
                                                       const IFresnelMap* p_fresnel_map)
    : IComputationTerm(p_multi_layer, p_fresnel_map)
{}

RoughMultiLayerComputation::~RoughMultiLayerComputation()
{}

void RoughMultiLayerComputation::eval(ProgressHandler* progress,
    const std::vector<SimulationElement>::iterator& begin_it,
    const std::vector<SimulationElement>::iterator& end_it) const
{
    if (mp_multilayer->requiresMatrixRTCoefficients()) {
        return;
    }
    DelayedProgressCounter counter(100);
    for (std::vector<SimulationElement>::iterator it = begin_it; it != end_it; ++it) {
        if (!progress->alive())
            return;
        it->addIntensity(evaluate(*it));
        counter.stepProgress(progress);
    }
}

double RoughMultiLayerComputation::evaluate(const SimulationElement& sim_element) const
{
    if (sim_element.getAlphaMean()<0.0)
        return 0.0;
    kvector_t q = sim_element.getMeanQ();
    double wavelength = sim_element.getWavelength();
    double autocorr(0.0);
    complex_t crosscorr(0.0, 0.0);

    std::vector<complex_t > rterm( mp_multilayer->numberOfLayers()-1 );
    std::vector<complex_t > sterm( mp_multilayer->numberOfLayers()-1 );

    for (size_t i=0; i<mp_multilayer->numberOfLayers()-1; i++){
        rterm[i] = get_refractive_term(i, wavelength);
        sterm[i] = get_sum8terms(i, sim_element);
    }

    for (size_t i=0; i<mp_multilayer->numberOfLayers()-1; i++) {
        const LayerRoughness *rough =
            mp_multilayer->layerBottomInterface(i)->getRoughness();
        if(rough)
            autocorr += std::norm( rterm[i] ) * std::norm( sterm[i] ) * rough->getSpectralFun(q);
    }

    // cross correlation between layers
    if (mp_multilayer->crossCorrLength() != 0.0) {
        for(size_t j=0; j<mp_multilayer->numberOfLayers()-1; j++){
            for(size_t k=0; k<mp_multilayer->numberOfLayers()-1; k++) {
                if(j==k) continue;
                crosscorr += rterm[j]*sterm[j]*
                    mp_multilayer->crossCorrSpectralFun(q,j,k)*
                    std::conj(rterm[k])*std::conj(sterm[k]);
            }
        }
    }

    //! @TODO clarify complex vs double
    return (autocorr+crosscorr.real())*M_PI/4./wavelength/wavelength;
}

complex_t RoughMultiLayerComputation::get_refractive_term(size_t ilayer, double wavelength) const
{
    return mp_multilayer->layer(ilayer  )->material()->refractiveIndex2(wavelength) -
           mp_multilayer->layer(ilayer+1)->material()->refractiveIndex2(wavelength);
}

complex_t RoughMultiLayerComputation::get_sum8terms(
    size_t ilayer, const SimulationElement& sim_element) const
{
    const auto P_in_plus = mp_fresnel_map->getInCoefficients(sim_element, ilayer);
    const auto P_out_plus = mp_fresnel_map->getOutCoefficients(sim_element, ilayer);

    const auto P_in_minus = mp_fresnel_map->getInCoefficients(sim_element, ilayer+1);
    const auto P_out_minus = mp_fresnel_map->getOutCoefficients(sim_element, ilayer+1);

    complex_t kiz_plus = P_in_plus->getScalarKz();
    complex_t kfz_plus = P_out_plus->getScalarKz();
    complex_t qz1_plus = - kiz_plus - kfz_plus;
    complex_t qz2_plus = - kiz_plus + kfz_plus;
    complex_t qz3_plus = - qz2_plus;
    complex_t qz4_plus = - qz1_plus;
    double thickness = mp_multilayer->layerThickness(ilayer);
    complex_t T_in_plus  = P_in_plus ->getScalarT()*exp_I( kiz_plus*thickness);
    complex_t R_in_plus  = P_in_plus ->getScalarR()*exp_I(-kiz_plus*thickness);
    complex_t T_out_plus = P_out_plus->getScalarT()*exp_I( kfz_plus*thickness);
    complex_t R_out_plus = P_out_plus->getScalarR()*exp_I(-kfz_plus*thickness);

    complex_t kiz_minus = P_in_minus->getScalarKz();
    complex_t kfz_minus = P_out_minus->getScalarKz();
    complex_t qz1_minus = - kiz_minus - kfz_minus;
    complex_t qz2_minus = - kiz_minus + kfz_minus;
    complex_t qz3_minus = - qz2_minus;
    complex_t qz4_minus = - qz1_minus;

    double sigma(0.0);
    if (const LayerRoughness* roughness
        = mp_multilayer->layerBottomInterface(ilayer)->getRoughness())
        sigma = roughness->getSigma();
    complex_t term1 = T_in_plus * T_out_plus * h_plus(qz1_plus*sigma);
    complex_t term2 = T_in_plus * R_out_plus * h_plus(qz2_plus*sigma);
    complex_t term3 = R_in_plus * T_out_plus * h_plus(qz3_plus*sigma);
    complex_t term4 = R_in_plus * R_out_plus * h_plus(qz4_plus*sigma);
    complex_t term5 = P_in_minus->getScalarT() * P_out_minus->getScalarT()
                      * h_min(qz1_minus*sigma);
    complex_t term6 = P_in_minus->getScalarT() * P_out_minus->getScalarR()
                      * h_min(qz2_minus*sigma);
    complex_t term7 = P_in_minus->getScalarR() * P_out_minus->getScalarT()
                      * h_min(qz3_minus*sigma);
    complex_t term8 = P_in_minus->getScalarR() * P_out_minus->getScalarR()
                      * h_min(qz4_minus*sigma);

    return term1 + term2 + term3 + term4 + term5 + term6 + term7 + term8;
}
