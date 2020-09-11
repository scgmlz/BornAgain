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

#include "Core/Multilayer/IMultiLayerBuilder.h"

class ISample;

//! Builds sample: cylinder form factor in DWBA (IsGISAXS example #3, part I).
//! @ingroup standard_samples

class BA_CORE_API_ CylindersInDWBABuilder : public IMultiLayerBuilder
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

class BA_CORE_API_ CylindersInBABuilder : public IMultiLayerBuilder
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

class BA_CORE_API_ LargeCylindersInDWBABuilder : public IMultiLayerBuilder
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

class BA_CORE_API_ RotatedCylindersBuilder : public IMultiLayerBuilder
{
public:
    RotatedCylindersBuilder();
    MultiLayer* buildSample() const;

private:
    double m_height;
    double m_radius;
};

#endif // BORNAGAIN_CORE_STANDARDSAMPLES_CYLINDERSBUILDER_H
