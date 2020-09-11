// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Multilayer/SSCAHelper.cpp
//! @brief     Implements class SSCAHelper.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Core/Multilayer/SSCAHelper.h"
#include "Core/Aggregate/InterferenceFunctionRadialParaCrystal.h"
#include "Core/Basics/Exceptions.h"
#include "Core/Multilayer/FormFactorCoherentSum.h"

SSCAHelper::SSCAHelper(double kappa) : m_kappa(kappa), m_mean_radius{} {}

void SSCAHelper::init(const std::vector<FormFactorCoherentSum>& ff_wrappers)
{
    m_mean_radius = 0.0;
    for (auto& ffw : ff_wrappers)
        m_mean_radius += ffw.relativeAbundance() * ffw.radialExtension();
}

complex_t SSCAHelper::getCharacteristicSizeCoupling(
    double qp, const std::vector<FormFactorCoherentSum>& ff_wrappers) const
{
    complex_t result{};
    for (auto& ffw : ff_wrappers) {
        double radial_extension = ffw.radialExtension();
        result +=
            ffw.relativeAbundance() * calculatePositionOffsetPhase(2.0 * qp, radial_extension);
    }
    return result;
}

complex_t SSCAHelper::getCharacteristicDistribution(double qp,
                                                    const IInterferenceFunction* p_iff) const
{
    const InterferenceFunctionRadialParaCrystal* p_iff_radial =
        dynamic_cast<const InterferenceFunctionRadialParaCrystal*>(p_iff);
    if (!p_iff_radial)
        throw Exceptions::ClassInitializationException("Wrong interference function for SSCA");
    return p_iff_radial->FTPDF(qp);
}

complex_t SSCAHelper::calculatePositionOffsetPhase(double qp, double radial_extension) const
{
    return exp_I(m_kappa * qp * (radial_extension - m_mean_radius));
}

complex_t
SSCAHelper::getMeanFormfactorNorm(double qp, const std::vector<complex_t>& precomputed_ff,
                                  const std::vector<FormFactorCoherentSum>& ff_wrappers) const
{
    complex_t ff_orig = 0., ff_conj = 0.; // original and conjugated mean formfactor
    for (size_t i = 0; i < ff_wrappers.size(); ++i) {
        double radial_extension = ff_wrappers[i].radialExtension();
        complex_t prefac =
            ff_wrappers[i].relativeAbundance() * calculatePositionOffsetPhase(qp, radial_extension);
        ff_orig += prefac * precomputed_ff[i];
        ff_conj += prefac * std::conj(precomputed_ff[i]);
    }
    return ff_orig * ff_conj;
}

void SSCAHelper::getMeanFormfactors(
    double qp, Eigen::Matrix2cd& ff_orig, Eigen::Matrix2cd& ff_conj,
    const InterferenceFunctionUtils::matrixFFVector_t& precomputed_ff,
    const std::vector<FormFactorCoherentSum>& ff_wrappers) const
{
    ff_orig = Eigen::Matrix2cd::Zero();
    ff_conj = Eigen::Matrix2cd::Zero();
    for (size_t i = 0; i < ff_wrappers.size(); ++i) {
        double radial_extension = ff_wrappers[i].radialExtension();
        complex_t prefac =
            ff_wrappers[i].relativeAbundance() * calculatePositionOffsetPhase(qp, radial_extension);
        ff_orig += prefac * precomputed_ff[i];
        ff_conj += prefac * precomputed_ff[i].adjoint();
    }
}
