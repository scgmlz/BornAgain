// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Aggregate/FormFactorWrapper.cpp
//! @brief     Implements class FormFactorWrapper.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "FormFactorWrapper.h"
#include "IFormFactor.h"
#include "SimulationElement.h"
#include "WavevectorPair.h"
#include "LayerSpecularInfo.h"
#include "ILayerRTCoefficients.h"
#include "Exceptions.h"

FormFactorWrapper::FormFactorWrapper(IFormFactor* ff, double abundance)
: mP_ff(ff), m_abundance(abundance)
{
}

FormFactorWrapper::~FormFactorWrapper() {}

FormFactorWrapper* FormFactorWrapper::clone() const
{
    auto clone = new FormFactorWrapper(mP_ff->clone(), m_abundance);
    clone->setSpecularInfo(*mP_specular_info);
    return clone;
}

complex_t FormFactorWrapper::evaluate(const SimulationElement& sim_element) const
{
    WavevectorPair wavevectors(sim_element.getKi(), sim_element.getMeanKf());

    const std::unique_ptr<const ILayerRTCoefficients> P_in_coeffs(
        mP_specular_info->getInCoefficients(sim_element));
    const std::unique_ptr<const ILayerRTCoefficients> P_out_coeffs(
        mP_specular_info->getOutCoefficients(sim_element));
    mP_ff->setSpecularInfo(P_in_coeffs.get(), P_out_coeffs.get());
    return sim_element.getKi().mag2() / 4 /M_PI * mP_ff->evaluate(wavevectors);
}

Eigen::Matrix2cd FormFactorWrapper::evaluatePol(const SimulationElement& sim_element) const
{
    WavevectorPair wavevectors(sim_element.getKi(), sim_element.getMeanKf());

    const std::unique_ptr<const ILayerRTCoefficients> P_in_coeffs(
        mP_specular_info->getInCoefficients(sim_element));
    const std::unique_ptr<const ILayerRTCoefficients> P_out_coeffs(
        mP_specular_info->getOutCoefficients(sim_element));
    mP_ff->setSpecularInfo(P_in_coeffs.get(), P_out_coeffs.get());
    return sim_element.getKi().mag2() / 4 /M_PI * mP_ff->evaluatePol(wavevectors);
}

IFormFactor* FormFactorWrapper::formfactor()
{
    return mP_ff.get();
}

const IFormFactor* FormFactorWrapper::formfactor() const
{
    return mP_ff.get();
}

void FormFactorWrapper::setSpecularInfo(const LayerSpecularInfo& specular_info)
{
    mP_specular_info.reset(specular_info.clone());
}

void FormFactorWrapper::scaleRelativeAbundance(double total_abundance)
{
    if (total_abundance>0.0) {
        m_abundance /= total_abundance;
        return;
    }
    throw Exceptions::LogicErrorException("FormFactorWrapper::scaleRelativeAbundance: "
                                          "Trying to scale with non strictly positive factor.");
}

double FormFactorWrapper::radialExtension() const
{
    return mP_ff->getRadialExtension();
}
