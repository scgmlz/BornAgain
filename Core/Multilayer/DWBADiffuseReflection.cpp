// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Multilayer/DWBADiffuseReflection.cpp
//! @brief     Implements class DWBADiffuseReflection.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "DWBADiffuseReflection.h"
#include "Layer.h"
#include "LayerInterface.h"
#include "LayerRoughness.h"
#include "MathConstants.h"
#include "MultiLayer.h"

DWBADiffuseReflection::DWBADiffuseReflection()
    : m_sample(0)
    , m_diffuse_autocorr(0)
    , m_diffuse_crosscorr(0)
    , m_qz1(0)
    , m_qz2(0)
    , m_qz3(0)
    , m_qz4(0)
{
}

void DWBADiffuseReflection::execute(
    const MultiLayer& sample, const kvector_t ki, const kvector_t kf)
{
    setSample(sample);
    setKvectors(ki, kf);
    diffuse_autocorr();
    if (m_sample->getCrossCorrLength() != 0)
        diffuse_crosscorr();
    else
        m_diffuse_crosscorr = 0;
}

void DWBADiffuseReflection::setKvectors(const kvector_t ki, const kvector_t kf)
{
    m_ki = ki;
    m_kf = kf;
    m_q = kf - ki;
    m_qz1 = std::pow(ki.z() + kf.z(), 2);
    m_qz2 = std::pow(ki.z() - kf.z(), 2);
    m_qz3 = std::pow(-ki.z() + kf.z(), 2);
    m_qz4 = std::pow(-ki.z() - kf.z(), 2);
    SpecularMatrix::execute(*m_sample, ki, m_fcoeff_i);
    SpecularMatrix::execute(*m_sample, kf, m_fcoeff_f);
}

void DWBADiffuseReflection::diffuse_autocorr()
{
    double autocorr(0);
    for (size_t i = 0; i < m_sample->getNumberOfLayers() - 1; i++)
        autocorr += std::norm(get_refractive_term(i)) * std::norm(get_sum4terms(i))
            * m_sample->getLayerBottomInterface(i)->getRoughness()->getSpectralFun(m_q);
    m_diffuse_autocorr = autocorr * m_ki.mag2() / 16. / M_PI;
}

void DWBADiffuseReflection::diffuse_crosscorr()
{
    complex_t crosscorr(0);

    std::vector<complex_t> rterm;
    rterm.resize(m_sample->getNumberOfLayers());
    std::vector<complex_t> sterm;
    sterm.resize(m_sample->getNumberOfLayers());

    for (size_t j = 0; j < m_sample->getNumberOfLayers() - 1; j++) {
        rterm[j] = get_refractive_term(j);
        sterm[j] = get_sum4terms(j);
    }

    for (size_t j = 0; j < m_sample->getNumberOfLayers() - 1; j++) {
        for (size_t k = 0; k < m_sample->getNumberOfLayers() - 1; k++) {
            if (j == k)
                continue;
            crosscorr += rterm[j] * sterm[j] * rterm[k]
                * m_sample->getCrossCorrSpectralFun(m_q, j, k) * std::conj(sterm[k]);
        }
    }
    m_diffuse_crosscorr = crosscorr.real() * m_ki.mag2() / 16. / M_PI;
}

complex_t DWBADiffuseReflection::get_refractive_term(size_t ilayer) const
{
    return m_sample->getLayer(ilayer)->getRefractiveIndex2()
        - m_sample->getLayer(ilayer + 1)->getRefractiveIndex2();
}

complex_t DWBADiffuseReflection::get_sum4terms(size_t ilayer)
{
    double sigma2 =
        -0.5 * std::pow(m_sample->getLayerBottomInterface(ilayer)->getRoughness()->getSigma(), 2);
    complex_t term1 = m_fcoeff_i[ilayer + 1].getScalarT() * m_fcoeff_f[ilayer + 1].getScalarT()
        * std::exp(sigma2 * m_qz1);
    complex_t term2 = m_fcoeff_i[ilayer + 1].getScalarT() * m_fcoeff_f[ilayer + 1].getScalarR()
        * std::exp(sigma2 * m_qz2);
    complex_t term3 = m_fcoeff_i[ilayer + 1].getScalarR() * m_fcoeff_f[ilayer + 1].getScalarT()
        * std::exp(sigma2 * m_qz3);
    complex_t term4 = m_fcoeff_i[ilayer + 1].getScalarR() * m_fcoeff_f[ilayer + 1].getScalarR()
        * std::exp(sigma2 * m_qz4);

    return term1 + term2 + term3 + term4;
}
