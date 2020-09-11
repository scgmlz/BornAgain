// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/StandardSamples/MesoCrystalBuilder.h
//! @brief     Defines class MesoCrystalBuilder.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_CORE_STANDARDSAMPLES_MESOCRYSTALBUILDER_H
#define BORNAGAIN_CORE_STANDARDSAMPLES_MESOCRYSTALBUILDER_H

#include "Core/Basics/Complex.h"
#include "Core/Multilayer/IMultiLayerBuilder.h"

class IFormFactor;
class ISample;
class Lattice;
class MesoCrystal;

//! Builds sample: cylindrical mesocrystal composed of spheres in a cubic lattice.
//! @ingroup standard_samples

class BA_CORE_API_ MesoCrystalBuilder : public IMultiLayerBuilder
{
public:
    MesoCrystalBuilder();
    MultiLayer* buildSample() const;
};

#endif // BORNAGAIN_CORE_STANDARDSAMPLES_MESOCRYSTALBUILDER_H
