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

#ifndef IMPORTDATAUTILS_H
#define IMPORTDATAUTILS_H

#include "WinDllMacros.h"
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

BA_CORE_API_ std::unique_ptr<OutputData<double>> ImportData(QString& baseNameOfLoadedFile);
BA_CORE_API_ bool UseImportAssistant(QString& dirname, QString& fileName, std::unique_ptr<OutputData<double>>& result);


//! Creates OutputData with bin-valued axes.
BA_CORE_API_ std::unique_ptr<OutputData<double>>
CreateSimplifiedOutputData(const OutputData<double>& data);

//! Returns true if data item is compatible with instrument.
BA_CORE_API_ bool Compatible(const InstrumentItem& instrumentItem,
                             const RealDataItem& realDataItem);

//! Composes a message with the shapes of InstrumentItem and RealDataItem.
BA_CORE_API_ QString printShapeMessage(const std::vector<int>& instrument_shape,
                                           const std::vector<int>& data_shape);
};

#endif // IMPORTDATAUTILS_H
