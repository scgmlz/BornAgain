//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Sample/StandardSamples/TwoDimLatticeBuilder.h
//! @brief     Defines class IsGISAXS06Builder.
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
#ifndef BORNAGAIN_SAMPLE_STANDARDSAMPLES_TWODIMLATTICEBUILDER_H
#define BORNAGAIN_SAMPLE_STANDARDSAMPLES_TWODIMLATTICEBUILDER_H

#include "Sample/SampleBuilderEngine/ISampleBuilder.h"

//! Builds sample: 2D lattice with arbitrary angle and different lattice length_1 and length_2.
//! @ingroup standard_samples

class Basic2DLatticeBuilder : public ISampleBuilder {
public:
    Basic2DLatticeBuilder() {}
    MultiLayer* buildSample() const;
};

//! Builds sample: 2D lattice with different disorder (IsGISAXS example #6).
//! @ingroup standard_samples

class SquareLattice2DBuilder : public ISampleBuilder {
public:
    SquareLattice2DBuilder() {}
    MultiLayer* buildSample() const;
};

//! Builds sample: 2D lattice with different disorder (IsGISAXS example #6).
//! @ingroup standard_samples

class CenteredSquareLattice2DBuilder : public ISampleBuilder {
public:
    MultiLayer* buildSample() const;
};

//! Builds sample: 2D lattice with different disorder (IsGISAXS example #6).
//! @ingroup standard_samples

class RotatedSquareLattice2DBuilder : public ISampleBuilder {
public:
    MultiLayer* buildSample() const;
};

//! Builds sample: 2D finite lattice with thermal disorder.
//! @ingroup standard_samples

class FiniteSquareLattice2DBuilder : public ISampleBuilder {
public:
    MultiLayer* buildSample() const;
};

//! Builds sample: 2D finite lattice of 2D finite lattices (superlattice).
//! @ingroup standard_samples

class SuperLatticeBuilder : public ISampleBuilder {
public:
    MultiLayer* buildSample() const;
};

#endif // BORNAGAIN_SAMPLE_STANDARDSAMPLES_TWODIMLATTICEBUILDER_H
#endif // USER_API
