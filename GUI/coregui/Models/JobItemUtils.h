// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/JobItemUtils.h
//! @brief     Defines class JobItemUtils
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_MODELS_JOBITEMUTILS_H
#define BORNAGAIN_GUI_COREGUI_MODELS_JOBITEMUTILS_H

#include "Core/Detector/IDetector.h"
#include "GUI/coregui/Models/ComboProperty.h"
#include <QMap>

class DataItem;
class InstrumentItem;
class JobItem;
class Simulation;

//! Contains set of convenience methods to set data to the IntensityDataItem from domain simulation.
//! Used to modify OutputData's axes units as requested by IntensityDataItem.

namespace JobItemUtils
{
//! updates axes of OutputData in IntensityData item
BA_CORE_API_ void updateDataAxes(DataItem* intensityItem, const InstrumentItem* instrumentItem);

//! returns axes units names from their domain counterpart
BA_CORE_API_ QString nameFromAxesUnits(AxesUnits units);

//! returns domain axes units type from their GUI name
BA_CORE_API_ AxesUnits axesUnitsFromName(const QString& name);

BA_CORE_API_ void setIntensityItemAxesUnits(DataItem* intensityItem,
                                            const InstrumentItem* instrumentItem);

BA_CORE_API_ void setIntensityItemAxesUnits(DataItem* intensityItem,
                                            const IUnitConverter& converter);

BA_CORE_API_ void createDefaultDetectorMap(DataItem* intensityItem,
                                           const InstrumentItem* instrumentItem);

//! Sets simulation results into the DataItem
BA_CORE_API_ void setResults(DataItem* intensityItem, const Simulation* simulation);

BA_CORE_API_ ComboProperty availableUnits(const IUnitConverter& converter);
} // namespace JobItemUtils

#endif // BORNAGAIN_GUI_COREGUI_MODELS_JOBITEMUTILS_H
