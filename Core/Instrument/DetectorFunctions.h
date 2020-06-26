// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Instrument/DetectorFunctions.h
//! @brief     Defines namespace DetectorFunctions.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef DETECTORFUNCTIONS_H
#define DETECTORFUNCTIONS_H

#include "IDetector.h"
#include "WinDllMacros.h"
#include <functional>
#include <memory>
#include <string>
template <class T> class OutputData;
class Instrument;
class IDetector;
class SimulationAreaIterator;

//! Contains set of detector-related convenience functions.
//! @ingroup detector

namespace DetectorFunctions
{

//! Returns true if the data has same axes size (nx,ny) with the detector.
BA_CORE_API_ bool hasSameDimensions(const IDetector& detector, const OutputData<double>& data);

// TODO replace two functions below with the template function after change of
// OutputData::getAxis signature

//! Returns string representation of axes dimension in the form "(nx,ny)"
BA_CORE_API_ std::string axesToString(const IDetector& detector);

//! Returns string representation of axes dimension in the form "(nx,ny)"
BA_CORE_API_ std::string axesToString(const OutputData<double>& data);

} // namespace DetectorFunctions

#endif // DETECTORFUNCTIONS_H
