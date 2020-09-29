// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/StandardSamples/SlicedCompositionBuilder.h
//! @brief     Defines classes to build various particles crossing interfaces.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_CORE_STANDARDSAMPLES_SLICEDCOMPOSITIONBUILDER_H
#define BORNAGAIN_CORE_STANDARDSAMPLES_SLICEDCOMPOSITIONBUILDER_H

#include "Core/SampleBuilderEngine/ISampleBuilder.h"

//! Builds sample: spherical composition made of top+bottom spherical cups
//! @ingroup standard_samples

class SlicedCompositionBuilder : public ISampleBuilder
{
public:
    MultiLayer* buildSample() const;
};

#endif // BORNAGAIN_CORE_STANDARDSAMPLES_SLICEDCOMPOSITIONBUILDER_H
