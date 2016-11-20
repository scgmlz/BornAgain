// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/StandardSamples/CustomMorphologyBuilder.h
//! @brief     Defines class CustomMorphologyBuilder.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef CUSTOMMORPHOLOGYBUILDER_H
#define CUSTOMMORPHOLOGYBUILDER_H

#include "IMultiLayerBuilder.h"

class ISample;

//! Builds sample: mixture of different particles (IsGISAXS example #7).
//! @ingroup standard_samples

class BA_CORE_API_ CustomMorphologyBuilder : public IMultiLayerBuilder
{
public:
    CustomMorphologyBuilder() {}
    MultiLayer* buildSample() const;
};

#endif // CUSTOMMORPHOLOGYBUILDER_H
