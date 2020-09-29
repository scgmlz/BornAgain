// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/StandardSamples/ParaCrystalBuilder.h
//! @brief     Defines classes of ParaCrystalBuilder family.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_CORE_STANDARDSAMPLES_PARACRYSTALBUILDER_H
#define BORNAGAIN_CORE_STANDARDSAMPLES_PARACRYSTALBUILDER_H

#include "Core/SampleBuilderEngine/ISampleBuilder.h"
#include <memory>

class IFTDistribution2D;
class FTDistribution2DComponents;

//! @ingroup standard_samples
//! Builds sample: cylinders with 1DDL structure factor (IsGISAXS example #4).

class RadialParaCrystalBuilder : public ISampleBuilder
{
public:
    MultiLayer* buildSample() const;
};

//! Builds sample: basic two dimensional paracrystal with various probability
//! distribution functions (PDF's). They are initialized via component service.
//! @ingroup standard_samples

class Basic2DParaCrystalBuilder : public ISampleBuilder
{
public:
    Basic2DParaCrystalBuilder();
    ~Basic2DParaCrystalBuilder();
    MultiLayer* buildSample() const;

    MultiLayer* createSampleByIndex(size_t index);

private:
    std::unique_ptr<IFTDistribution2D> m_pdf1;
    std::unique_ptr<IFTDistribution2D> m_pdf2;
};

//! Builds sample: cylinders with 2DDL structure factor (IsGISAXS example #4).
//! @ingroup standard_samples

class HexParaCrystalBuilder : public ISampleBuilder
{
public:
    MultiLayer* buildSample() const;
};

//! @ingroup standard_samples
//! Builds sample: 2D paracrystal lattice (IsGISAXS example #8).

class RectParaCrystalBuilder : public ISampleBuilder
{
public:
    MultiLayer* buildSample() const;
};

#endif // BORNAGAIN_CORE_STANDARDSAMPLES_PARACRYSTALBUILDER_H
