// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/StandardSamples/MultipleLayoutBuilder.h
//! @brief     Defines class MultipleLayoutBuilder.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_CORE_STANDARDSAMPLES_MULTIPLELAYOUTBUILDER_H
#define BORNAGAIN_CORE_STANDARDSAMPLES_MULTIPLELAYOUTBUILDER_H

#include "Core/SampleBuilderEngine/ISampleBuilder.h"

//! Builds sample: mixture of cylinders and prisms without interference,
//! using multiple particle layouts
//! @ingroup standard_samples

class MultipleLayoutBuilder : public ISampleBuilder
{
public:
    MultiLayer* buildSample() const;
};

#endif // BORNAGAIN_CORE_STANDARDSAMPLES_MULTIPLELAYOUTBUILDER_H
