// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/StandardSamples/MultiLayerWithRoughnessBuilder.h
//! @brief     Defines class MultiLayerWithRoughnessBuilder.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_CORE_STANDARDSAMPLES_MULTILAYERWITHROUGHNESSBUILDER_H
#define BORNAGAIN_CORE_STANDARDSAMPLES_MULTILAYERWITHROUGHNESSBUILDER_H

#include "Core/Multilayer/IMultiLayerBuilder.h"

class ISample;

//! Builds sample: layers with correlated roughness.
//! @ingroup standard_samples

class BA_CORE_API_ MultiLayerWithRoughnessBuilder : public IMultiLayerBuilder
{
public:
    MultiLayerWithRoughnessBuilder();
    virtual MultiLayer* buildSample() const;

private:
    double m_thicknessA;
    double m_thicknessB;
    double m_sigma;
    double m_hurst;
    double m_lateralCorrLength;
    double m_crossCorrLength;
};

#endif // BORNAGAIN_CORE_STANDARDSAMPLES_MULTILAYERWITHROUGHNESSBUILDER_H
