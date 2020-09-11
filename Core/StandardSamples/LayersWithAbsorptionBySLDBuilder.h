// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/StandardSamples/LayersWithAbsorptionBySLDBuilder.h
//! @brief     Defines class LayersWithAbsorptionBySLDBuilder.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_CORE_STANDARDSAMPLES_LAYERSWITHABSORPTIONBYSLDBUILDER_H
#define BORNAGAIN_CORE_STANDARDSAMPLES_LAYERSWITHABSORPTIONBYSLDBUILDER_H

#include "Core/Multilayer/IMultiLayerBuilder.h"

//! The LayersWithAbsorptionBySLDBuilder class generates a multilayer with 3 layers with
//! absorption (refractive index has imaginary part). //! The middle layer is populated with
//! particles. MaterialBySLD is used to generate maaterials
//! @ingroup standard_samples

class BA_CORE_API_ LayersWithAbsorptionBySLDBuilder : public IMultiLayerBuilder
{
public:
    LayersWithAbsorptionBySLDBuilder();
    ~LayersWithAbsorptionBySLDBuilder();
    virtual MultiLayer* buildSample() const;
};

#endif // BORNAGAIN_CORE_STANDARDSAMPLES_LAYERSWITHABSORPTIONBYSLDBUILDER_H
