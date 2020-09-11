// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/utils/LayoutUtils.h
//! @brief     Defines LayoutUtils namespace
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_UTILS_LAYOUTUTILS_H
#define BORNAGAIN_GUI_COREGUI_UTILS_LAYOUTUTILS_H

#include "Wrap/WinDllMacros.h"

class QLayout;
class QGridLayout;
class QWidget;

//! Utility functions to add/remove widgets to the layout on the fly.
//! Taken from https://stackoverflow.com/questions/5395266/removing-widgets-from-qgridlayout

namespace LayoutUtils
{

//! Removes content from box layout.
BA_CORE_API_ void clearLayout(QLayout* layout, bool deleteWidgets = true);

//! Removes row from grid layout (important: doesn't change row count).
BA_CORE_API_ void removeRow(QGridLayout* layout, int row, bool deleteWidgets = true);

//! Removes column from grid layout.
BA_CORE_API_ void removeColumn(QGridLayout* layout, int column, bool deleteWidgets = true);

//! Clear layout completely.
BA_CORE_API_ void clearGridLayout(QGridLayout* layout, bool deleteWidgets = true);

//! Returns empty widget to occupy place in layout.
BA_CORE_API_ QWidget* placeHolder();
} // namespace LayoutUtils

#endif // BORNAGAIN_GUI_COREGUI_UTILS_LAYOUTUTILS_H
