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

#include "Core/Multilayer/IMultiLayerBuilder.h"
#include <memory>

class IFTDistribution2D;
class ISample;
class FTDistribution2DComponents;

//! @ingroup standard_samples
//! Builds sample: cylinders with 1DDL structure factor (IsGISAXS example #4).

class BA_CORE_API_ RadialParaCrystalBuilder : public IMultiLayerBuilder
{
public:
    RadialParaCrystalBuilder();
    MultiLayer* buildSample() const;

private:
    double m_corr_peak_distance;
    double m_corr_width;
    double m_corr_length;
    double m_cylinder_height;
    double m_cylinder_radius;
};

//! Builds sample: basic two dimensional paracrystal with various probability
//! distribution functions (PDF's). They are initialized via component service.
//! @ingroup standard_samples

class BA_CORE_API_ Basic2DParaCrystalBuilder : public IMultiLayerBuilder
{
public:
    Basic2DParaCrystalBuilder();
    ~Basic2DParaCrystalBuilder();
    virtual MultiLayer* buildSample() const;

    MultiLayer* createSample(size_t index = 0);

private:
    std::unique_ptr<IFTDistribution2D> m_pdf1;
    std::unique_ptr<IFTDistribution2D> m_pdf2;
};

//! Builds sample: cylinders with 2DDL structure factor (IsGISAXS example #4).
//! @ingroup standard_samples

class BA_CORE_API_ HexParaCrystalBuilder : public IMultiLayerBuilder
{
public:
    HexParaCrystalBuilder();
    virtual MultiLayer* buildSample() const;

private:
    double m_peak_distance;
    double m_corr_length;
    double m_domain_size_1;
    double m_domain_size_2;
    double m_cylinder_height;
    double m_cylinder_radius;
};

//! @ingroup standard_samples
//! Builds sample: 2D paracrystal lattice (IsGISAXS example #8).

class BA_CORE_API_ RectParaCrystalBuilder : public IMultiLayerBuilder
{
public:
    RectParaCrystalBuilder() {}
    virtual MultiLayer* buildSample() const;
};

#endif // BORNAGAIN_CORE_STANDARDSAMPLES_PARACRYSTALBUILDER_H
