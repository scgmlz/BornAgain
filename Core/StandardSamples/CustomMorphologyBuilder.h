// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/StandardSamples/CustomMorphologyBuilder.h
//! @brief     Defines class CustomMorphologyBuilder.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_CORE_STANDARDSAMPLES_CUSTOMMORPHOLOGYBUILDER_H
#define BORNAGAIN_CORE_STANDARDSAMPLES_CUSTOMMORPHOLOGYBUILDER_H

#include "Core/SampleBuilderEngine/ISampleBuilder.h"

//! Builds sample: mixture of different particles (IsGISAXS example #7).
//! @ingroup standard_samples

class CustomMorphologyBuilder : public ISampleBuilder
{
public:
    MultiLayer* buildSample() const;
};

#endif // BORNAGAIN_CORE_STANDARDSAMPLES_CUSTOMMORPHOLOGYBUILDER_H
