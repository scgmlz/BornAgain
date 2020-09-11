// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Intensity/AxisNames.h
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

#include "Core/Intensity/IUnitConverter.h"
#include <map>

//! Contains functions to create maps that give the right axis names for different
//! detector types and units
//! @ingroup detector

namespace AxisNames
{
BA_CORE_API_ std::map<AxesUnits, std::string> InitSphericalAxis0();
BA_CORE_API_ std::map<AxesUnits, std::string> InitSphericalAxis1();
BA_CORE_API_ std::map<AxesUnits, std::string> InitRectangularAxis0();
BA_CORE_API_ std::map<AxesUnits, std::string> InitRectangularAxis1();
BA_CORE_API_ std::map<AxesUnits, std::string> InitOffSpecAxis0();
BA_CORE_API_ std::map<AxesUnits, std::string> InitOffSpecAxis1();
BA_CORE_API_ std::map<AxesUnits, std::string> InitSpecAxis();
BA_CORE_API_ std::map<AxesUnits, std::string> InitSpecAxisQ();
BA_CORE_API_ std::map<AxesUnits, std::string> InitSampleDepthAxis();
} // namespace AxisNames

#endif // BORNAGAIN_CORE_INTENSITY_AXISNAMES_H
