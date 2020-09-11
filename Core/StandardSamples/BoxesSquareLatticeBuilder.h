// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/StandardSamples/BoxesSquareLatticeBuilder.h
//! @brief     Defines class BoxesSquareLatticeBuilder.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_CORE_STANDARDSAMPLES_BOXESSQUARELATTICEBUILDER_H
#define BORNAGAIN_CORE_STANDARDSAMPLES_BOXESSQUARELATTICEBUILDER_H

#include "Core/Multilayer/IMultiLayerBuilder.h"

class ISample;

//! Builds sample: square boxes in a square lattice
//! @ingroup standard_samples

class BA_CORE_API_ BoxesSquareLatticeBuilder : public IMultiLayerBuilder
{
public:
    BoxesSquareLatticeBuilder();
    MultiLayer* buildSample() const;

private:
    double m_length;
    double m_height;
};

#endif // BORNAGAIN_CORE_STANDARDSAMPLES_BOXESSQUARELATTICEBUILDER_H
