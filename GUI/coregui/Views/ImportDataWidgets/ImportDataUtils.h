// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/ImportDataWidgets/ImportDataUtils.h
//! @brief     Defines ImportDataUtils namespace
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_VIEWS_IMPORTDATAWIDGETS_IMPORTDATAUTILS_H
#define BORNAGAIN_GUI_COREGUI_VIEWS_IMPORTDATAWIDGETS_IMPORTDATAUTILS_H

#include "GUI/coregui/utils/ImportDataInfo.h"
#include <QString>
#include <memory>
#include <vector>

template <class T> class OutputData;
class RealDataItem;
class InstrumentItem;
class GISASInstrumentItem;

//! Provides utility methods to import data files.

namespace ImportDataUtils
{
std::unique_ptr<OutputData<double>> Import2dData(QString& baseNameOfLoadedFile);
ImportDataInfo Import1dData(QString& baseNameOfLoadedFile);
std::unique_ptr<OutputData<double>> ImportKnownData(QString& baseNameOfLoadedFile);
std::unique_ptr<OutputData<double>> ImportReflectometryData(QString& baseNameOfLoadedFile);
ImportDataInfo getFromImportAssistant(QString& fileName);

//! Creates OutputData with bin-valued axes.
std::unique_ptr<OutputData<double>> CreateSimplifiedOutputData(const OutputData<double>& data);

//! Returns true if data item is compatible with instrument.
bool Compatible(const InstrumentItem& instrumentItem, const RealDataItem& realDataItem);

//! Composes a message with the shapes of InstrumentItem and RealDataItem.
QString printShapeMessage(const std::vector<int>& instrument_shape,
                          const std::vector<int>& data_shape);
}; // namespace ImportDataUtils

#endif // BORNAGAIN_GUI_COREGUI_VIEWS_IMPORTDATAWIDGETS_IMPORTDATAUTILS_H
