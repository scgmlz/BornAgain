// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Multilayer/DWBADiffuseReflection.h
//! @brief     Defines class DWBADiffuseReflection.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef DWBADIFFUSEREFLECTION_H
#define DWBADIFFUSEREFLECTION_H

#include "SpecularMatrix.h"

class MultiLayer;

//! Calculation of diffuse (aka off-specular) reflection from multilayers.
//! @ingroup algorithms_internal

class BA_CORE_API_ DWBADiffuseReflection
{
public:
    DWBADiffuseReflection();

    void execute(const MultiLayer& sample, const kvector_t ki, const kvector_t kf);

    void setSample(const MultiLayer& sample) { m_sample = &sample; }

    double getDiffuseAutocorr() const { return m_diffuse_autocorr; }

    double getDiffuseCrosscorr() const { return m_diffuse_crosscorr; }

    void setKvectors(const kvector_t ki, const kvector_t kf);

private:
    void diffuse_autocorr();

    void diffuse_crosscorr();

    complex_t get_refractive_term(size_t ilayer) const;

    complex_t get_sum4terms(size_t ilayer);

    const MultiLayer* m_sample;
    SpecularMatrix::MultiLayerCoeff_t m_fcoeff_i;
    SpecularMatrix::MultiLayerCoeff_t m_fcoeff_f;
    double m_diffuse_autocorr;
    double m_diffuse_crosscorr;

    kvector_t m_ki;
    kvector_t m_kf;
    kvector_t m_q;
    double m_qz1;
    double m_qz2;
    double m_qz3;
    double m_qz4;
};

#endif // DWBADIFFUSEREFLECTION_H
