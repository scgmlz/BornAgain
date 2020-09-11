// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/ImportDataWidgets/RealDataSelectorToolBar.h
//! @brief     Defines class RealDataSelectorToolBar
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_VIEWS_IMPORTDATAWIDGETS_REALDATASELECTORTOOLBAR_H
#define BORNAGAIN_GUI_COREGUI_VIEWS_IMPORTDATAWIDGETS_REALDATASELECTORTOOLBAR_H

#include "GUI/coregui/mainwindow/StyledToolBar.h"

class RealDataSelectorActions;
class QToolButton;

//! The RealDataSelectorToolBar class represents a narrow toolbar on top of
//! RealDataSelectorWidget (ImportDataView)

class BA_CORE_API_ RealDataSelectorToolBar : public StyledToolBar
{
    Q_OBJECT
public:
    RealDataSelectorToolBar(RealDataSelectorActions* actions, QWidget* parent = nullptr);

private:
    QToolButton* m_import2dDataButton;
    QToolButton* m_import1dDataButton;
    QToolButton* m_removeDataButton;
};

#endif // BORNAGAIN_GUI_COREGUI_VIEWS_IMPORTDATAWIDGETS_REALDATASELECTORTOOLBAR_H
