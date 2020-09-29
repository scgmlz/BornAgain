// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/StandardSamples/RotatedPyramidsBuilder.h
//! @brief     Defines class RotatedPyramidsBuilder.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_CORE_STANDARDSAMPLES_ROTATEDPYRAMIDSBUILDER_H
#define BORNAGAIN_CORE_STANDARDSAMPLES_ROTATEDPYRAMIDSBUILDER_H

#include "Core/SampleBuilderEngine/ISampleBuilder.h"

//! Builds sample: Pyramids, rotated pyramids on top of substrate (IsGISAXS example #9)
//! @ingroup standard_samples

class RotatedPyramidsBuilder : public ISampleBuilder
{
public:
    MultiLayer* buildSample() const;
};

#endif // BORNAGAIN_CORE_STANDARDSAMPLES_ROTATEDPYRAMIDSBUILDER_H
