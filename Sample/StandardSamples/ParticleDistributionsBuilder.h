//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Sample/StandardSamples/ParticleDistributionsBuilder.h
//! @brief     Defines classes of with different types of particle distributions.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifdef SWIG
#error no need to expose this header to Swig
#endif

#ifndef USER_API
#ifndef BORNAGAIN_SAMPLE_STANDARDSAMPLES_PARTICLEDISTRIBUTIONSBUILDER_H
#define BORNAGAIN_SAMPLE_STANDARDSAMPLES_PARTICLEDISTRIBUTIONSBUILDER_H

#include "Sample/SampleBuilderEngine/ISampleBuilder.h"

//! Cylinders in BA with size distributions (IsGISAXS example #3, part II).
//! @ingroup standard_samples

class CylindersWithSizeDistributionBuilder : public ISampleBuilder {
public:
    MultiLayer* buildSample() const;
};

//! Builds mixture of cylinder particles with different size distribution (IsGISAXS example #2)
//! @ingroup standard_samples

class TwoTypesCylindersDistributionBuilder : public ISampleBuilder {
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

class RotatedPyramidsDistributionBuilder : public ISampleBuilder {
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

class SpheresWithLimitsDistributionBuilder : public ISampleBuilder {
public:
    SpheresWithLimitsDistributionBuilder() {}
    MultiLayer* buildSample() const;
};

//! Cones with the distribution applied to the angle and RealLimits defined.
//! @ingroup standard_samples

class ConesWithLimitsDistributionBuilder : public ISampleBuilder {
public:
    ConesWithLimitsDistributionBuilder() {}
    MultiLayer* buildSample() const;
};

//! Distribution of boxes with main parameter and two linked parameters.
//! @ingroup standard_samples

class LinkedBoxDistributionBuilder : public ISampleBuilder {
public:
    LinkedBoxDistributionBuilder() = default;
    MultiLayer* buildSample() const;
};

#endif // BORNAGAIN_SAMPLE_STANDARDSAMPLES_PARTICLEDISTRIBUTIONSBUILDER_H
#endif // USER_API
