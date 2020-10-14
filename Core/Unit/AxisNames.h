// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Unit/AxisNames.h
//! @brief     Defines namespace AxisNames.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_CORE_INTENSITY_AXISNAMES_H
#define BORNAGAIN_CORE_INTENSITY_AXISNAMES_H

#include "Core/Unit/IUnitConverter.h"
#include <map>

//! Contains functions to create maps that give the right axis names for different
//! detector types and units
//! @ingroup detector

namespace AxisNames
{
std::map<Axes::Units, std::string> InitSphericalAxis0();
std::map<Axes::Units, std::string> InitSphericalAxis1();
std::map<Axes::Units, std::string> InitRectangularAxis0();
std::map<Axes::Units, std::string> InitRectangularAxis1();
std::map<Axes::Units, std::string> InitOffSpecAxis0();
std::map<Axes::Units, std::string> InitOffSpecAxis1();
std::map<Axes::Units, std::string> InitSpecAxis();
std::map<Axes::Units, std::string> InitSpecAxisQ();
std::map<Axes::Units, std::string> InitSampleDepthAxis();
} // namespace AxisNames

#endif // BORNAGAIN_CORE_INTENSITY_AXISNAMES_H
