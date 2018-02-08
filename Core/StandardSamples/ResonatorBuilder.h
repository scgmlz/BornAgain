// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/StandardSamples/ResonatorBuilder.h
//! @brief     Defines ResonatorBuilder class.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef RESONATORBUILDER_H
#define RESONATORBUILDER_H

#include "IMultiLayerBuilder.h"

//! Builds sample: multilayer with Ti/Pt layers sequence.
//! @ingroup standard_samples

class BA_CORE_API_ ResonatorBuilder : public IMultiLayerBuilder
{
public:
    ResonatorBuilder() = default;
    MultiLayer* buildSample() const;
};

#endif  // RESONATORBUILDER_H
