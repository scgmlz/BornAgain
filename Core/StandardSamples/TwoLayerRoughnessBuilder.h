// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/StandardSamples/TwoLayerRoughnessBuilder.h
//! @brief     Defines class TwoLayerRoughnessBuilder.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_CORE_STANDARDSAMPLES_TWOLAYERROUGHNESSBUILDER_H
#define BORNAGAIN_CORE_STANDARDSAMPLES_TWOLAYERROUGHNESSBUILDER_H

#include "Core/Multilayer/IMultiLayerBuilder.h"

class ISample;

//! Builds sample: two layers with rough interface.
//! @ingroup standard_samples

class BA_CORE_API_ TwoLayerRoughnessBuilder : public IMultiLayerBuilder
{
public:
    TwoLayerRoughnessBuilder();
    MultiLayer* buildSample() const;

private:
    double m_sigma;
    double m_hurst;
    double m_lateralCorrLength;
};

#endif // BORNAGAIN_CORE_STANDARDSAMPLES_TWOLAYERROUGHNESSBUILDER_H
