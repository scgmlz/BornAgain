// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/StandardSamples/PercusYevickBuilder.h
//! @brief     Defines classes of PercusYevickBuilder family.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_CORE_STANDARDSAMPLES_PERCUSYEVICKBUILDER_H
#define BORNAGAIN_CORE_STANDARDSAMPLES_PERCUSYEVICKBUILDER_H

#include "Core/Multilayer/IMultiLayerBuilder.h"
#include <memory>

class ISample;

//! @ingroup standard_samples
//! Builds sample: cylinders with hard disk Percus-Yevick interference.

class BA_CORE_API_ HardDiskBuilder : public IMultiLayerBuilder
{
public:
    HardDiskBuilder();
    MultiLayer* buildSample() const;

private:
    double m_cylinder_height;
    double m_cylinder_radius;
    double m_disk_radius;
    double m_density;
};

#endif // BORNAGAIN_CORE_STANDARDSAMPLES_PERCUSYEVICKBUILDER_H
