// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/StandardSamples/ParticleDistributionsBuilder.h
//! @brief     Defines classes of with different types of particle distributions.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_CORE_STANDARDSAMPLES_PARTICLEDISTRIBUTIONSBUILDER_H
#define BORNAGAIN_CORE_STANDARDSAMPLES_PARTICLEDISTRIBUTIONSBUILDER_H

#include "Core/Multilayer/IMultiLayerBuilder.h"

//! Cylinders in BA with size distributions (IsGISAXS example #3, part II).
//! @ingroup standard_samples

class CylindersWithSizeDistributionBuilder : public IMultiLayerBuilder
{
public:
    CylindersWithSizeDistributionBuilder();
    MultiLayer* buildSample() const;

private:
    double m_height;
    double m_radius;
};

//! Builds mixture of cylinder particles with different size distribution (IsGISAXS example #2)
//! @ingroup standard_samples

class BA_CORE_API_ TwoTypesCylindersDistributionBuilder : public IMultiLayerBuilder
{
public:
    TwoTypesCylindersDistributionBuilder();
    MultiLayer* buildSample() const;

private:
    double m_radius1;
    double m_radius2;
    double m_height1;
    double m_height2;
    double m_sigma1_ratio;
    double m_sigma2_ratio;
};

//! Rotated Pyramids with the distribution applied to the rotation angle.
//! @ingroup standard_samples

class RotatedPyramidsDistributionBuilder : public IMultiLayerBuilder
{
public:
    RotatedPyramidsDistributionBuilder();
    MultiLayer* buildSample() const;

private:
    double m_length;
    double m_height;
    double m_alpha;
    double m_zangle;
};

//! Spherical particles with the distribution applied to the radius and RealLimits defined.
//! @ingroup standard_samples

class SpheresWithLimitsDistributionBuilder : public IMultiLayerBuilder
{
public:
    SpheresWithLimitsDistributionBuilder() {}
    MultiLayer* buildSample() const;
};

//! Cones with the distribution applied to the angle and RealLimits defined.
//! @ingroup standard_samples

class ConesWithLimitsDistributionBuilder : public IMultiLayerBuilder
{
public:
    ConesWithLimitsDistributionBuilder() {}
    MultiLayer* buildSample() const;
};

//! Distribution of boxes with main parameter and two linked parameters.
//! @ingroup standard_samples

class LinkedBoxDistributionBuilder : public IMultiLayerBuilder
{
public:
    LinkedBoxDistributionBuilder() = default;
    MultiLayer* buildSample() const;
};

#endif // BORNAGAIN_CORE_STANDARDSAMPLES_PARTICLEDISTRIBUTIONSBUILDER_H
