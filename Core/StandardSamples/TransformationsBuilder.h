// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/StandardSamples/TransformationsBuilder.h
//! @brief     Defines classes to build samples with different transformations.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef TRANSFORMATIONSBUILDER_H
#define TRANSFORMATIONSBUILDER_H

#include "IMultiLayerBuilder.h"

//! Rotated box in 3 layers system.
//! @ingroup standard_samples

class BA_CORE_API_ TransformBoxBuilder : public IMultiLayerBuilder
{
public:
    TransformBoxBuilder() {}
    MultiLayer* buildSample() const;
};

#endif // TRANSFORMATIONSBUILDER_H
