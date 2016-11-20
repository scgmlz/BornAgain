// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/StandardSamples/CylindersBuilder.h
//! @brief     Defines classes of CylindersBuilder family.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef CYLINDERSBUILDER_H
#define CYLINDERSBUILDER_H

#include "IMultiLayerBuilder.h"

class ISample;

//! Builds sample: cylinder formfactor in DWBA (IsGISAXS example #3, part I).
//! @ingroup standard_samples

class BA_CORE_API_ CylindersInDWBABuilder : public IMultiLayerBuilder
{
public:
    CylindersInDWBABuilder();
    MultiLayer* buildSample() const;

protected:
    void init_parameters();

private:
    double m_height;
    double m_radius;
};

//! Builds sample: cylinder formfactor in BA (IsGISAXS example #3, part II).
//! @ingroup standard_samples

class BA_CORE_API_ CylindersInBABuilder : public IMultiLayerBuilder
{
public:
    CylindersInBABuilder();
    MultiLayer* buildSample() const;

protected:
    void init_parameters();

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

protected:
    void init_parameters();

private:
    double m_height;
    double m_radius;
};

#endif // CYLINDERSBUILDER_H
