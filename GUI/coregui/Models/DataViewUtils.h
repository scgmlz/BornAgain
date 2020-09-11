// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/DataViewUtils.h
//! @brief     Defines namespace DataViewUtils
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_MODELS_DATAVIEWUTILS_H
#define BORNAGAIN_GUI_COREGUI_MODELS_DATAVIEWUTILS_H

#include "Core/Intensity/IUnitConverter.h"
#include <QString>
#include <memory>

class DataItem;
class Data1DViewItem;
class JobItem;
template <class T> class OutputData;

namespace DataViewUtils
{
void updateAxesTitle(Data1DViewItem* view_item);

std::unique_ptr<OutputData<double>> getTranslatedData(Data1DViewItem* view_item,
                                                      DataItem* data_item);
}; // namespace DataViewUtils

#endif // BORNAGAIN_GUI_COREGUI_MODELS_DATAVIEWUTILS_H
