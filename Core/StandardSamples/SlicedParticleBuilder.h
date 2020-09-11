// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/StandardSamples/SlicedParticleBuilder.h
//! @brief     Defines classes to build various particles crossing interfaces.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_CORE_STANDARDSAMPLES_SLICEDPARTICLEBUILDER_H
#define BORNAGAIN_CORE_STANDARDSAMPLES_SLICEDPARTICLEBUILDER_H

#include "Core/Multilayer/IMultiLayerBuilder.h"

//! Builds sample: spherical composition made of top+bottom spherical cups
//! @ingroup standard_samples

class BA_CORE_API_ SlicedCompositionBuilder : public IMultiLayerBuilder
{
public:
    SlicedCompositionBuilder() {}
    MultiLayer* buildSample() const;
};

#endif // BORNAGAIN_CORE_STANDARDSAMPLES_SLICEDPARTICLEBUILDER_H
