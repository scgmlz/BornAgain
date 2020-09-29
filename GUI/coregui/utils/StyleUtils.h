// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/utils/StyleUtils.h
//! @brief     DefinesStyleUtils namespace
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_UTILS_STYLEUTILS_H
#define BORNAGAIN_GUI_COREGUI_UTILS_STYLEUTILS_H

#include <QFont>
#include <QString>

class QTreeView;
class QWidget;
class QLayout;
class QWidget;

namespace StyleUtils
{

//! Sets style for the tree to use in property editors.
void setPropertyStyle(QTreeView* tree);

//! Returns string representing the style of QTreeView intended for property editor.
QString propertyTreeStyle();

//! Returns font for sections.
QFont sectionFont(bool bold = false);

//! Returns font for labels.
QFont labelFont(bool bold = false);

//! Make modal dialog resizable.
void setResizable(QDialog* dialog);

//! Creates details widget holding user content inside.
QWidget* createDetailsWidget(QWidget* content, const QString& name, bool expanded = true);

//! Creates details widget holding user layout inside.
QWidget* createDetailsWidget(QLayout* content, const QString& name, bool expanded = true);

//! Returns size of largest letter of default system font.
QSize SizeOfLetterM(const QWidget* widget = nullptr);

//! Returns size in points of default system font.
int SystemPointSize();

//! Returns typical width of the vertical property panel.

int PropertyPanelWidth();

} // namespace StyleUtils

#endif // BORNAGAIN_GUI_COREGUI_UTILS_STYLEUTILS_H
