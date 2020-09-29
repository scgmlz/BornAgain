// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/StandardSamples/CylindersBuilder.h
//! @brief     Defines classes of CylindersBuilder family.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_CORE_STANDARDSAMPLES_CYLINDERSBUILDER_H
#define BORNAGAIN_CORE_STANDARDSAMPLES_CYLINDERSBUILDER_H

#include "Core/SampleBuilderEngine/ISampleBuilder.h"

//! Builds sample: cylinder form factor in DWBA (IsGISAXS example #3, part I).
//! @ingroup standard_samples

class CylindersInDWBABuilder : public ISampleBuilder
{
public:
    CylindersInDWBABuilder();
    MultiLayer* buildSample() const;

private:
    double m_height;
    double m_radius;
};

//! Builds sample: cylinder form factor in BA (IsGISAXS example #3, part II).
//! @ingroup standard_samples

class CylindersInBABuilder : public ISampleBuilder
{
public:
    CylindersInBABuilder();
    MultiLayer* buildSample() const;

private:
    double m_height;
    double m_radius;
};

//! Builds sample with large cylinders for MC integration tests.
//! @ingroup standard_samples

class LargeCylindersInDWBABuilder : public ISampleBuilder
{
public:
    LargeCylindersInDWBABuilder();
    MultiLayer* buildSample() const;

private:
    double m_height;
    double m_radius;
};

//! Builds sample: cylinder form factor in DWBA (IsGISAXS example #3, part I).
//! @ingroup standard_samples

class RotatedCylindersBuilder : public ISampleBuilder
{
public:
    RotatedCylindersBuilder();
    MultiLayer* buildSample() const;

private:
    double m_height;
    double m_radius;
};

#endif // BORNAGAIN_CORE_STANDARDSAMPLES_CYLINDERSBUILDER_H
