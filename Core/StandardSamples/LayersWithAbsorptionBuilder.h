// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/StandardSamples/LayersWithAbsorptionBuilder.h
//! @brief     Defines class LayersWithAbsorptionBuilder.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_CORE_STANDARDSAMPLES_LAYERSWITHABSORPTIONBUILDER_H
#define BORNAGAIN_CORE_STANDARDSAMPLES_LAYERSWITHABSORPTIONBUILDER_H

#include "Core/Multilayer/IMultiLayerBuilder.h"
#include <memory>

class FormFactorComponents;
class IFormFactor;

//! The LayersWithAbsorptionBuilder class generates a multilayer with 3 layers with
//! absorption (refractive index has imaginary part).
//! @ingroup standard_samples

//! The middle layer is populated with particles.
//! Requires IComponentService which generates form factors, used for bulk form factors testing.

class BA_CORE_API_ LayersWithAbsorptionBuilder : public IMultiLayerBuilder
{
public:
    LayersWithAbsorptionBuilder();
    ~LayersWithAbsorptionBuilder();
    virtual MultiLayer* buildSample() const;

    MultiLayer* createSample(size_t index = 0);
    size_t size();

private:
    FormFactorComponents& ff_components();
    std::unique_ptr<IFormFactor> m_ff;
};

#endif // BORNAGAIN_CORE_STANDARDSAMPLES_LAYERSWITHABSORPTIONBUILDER_H
