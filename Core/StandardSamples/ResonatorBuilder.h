// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/StandardSamples/ResonatorBuilder.h
//! @brief     Defines ResonatorBuilder class.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_CORE_STANDARDSAMPLES_RESONATORBUILDER_H
#define BORNAGAIN_CORE_STANDARDSAMPLES_RESONATORBUILDER_H

#include "Core/SampleBuilderEngine/ISampleBuilder.h"

//! Builds sample: multilayer with Ti/Pt layers sequence.
//! @ingroup standard_samples

class ResonatorBuilder : public ISampleBuilder
{
public:
    ResonatorBuilder();
    MultiLayer* buildSample() const;

private:
    double m_l_ti; // titanium layer thickness
};

#endif // BORNAGAIN_CORE_STANDARDSAMPLES_RESONATORBUILDER_H
