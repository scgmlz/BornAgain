// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/ImportDataWidgets/RealDataSelectorHBar.h
//! @brief     Defines class RealDataSelectorToolBar
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef REALDATASELECTORHBAR_H
#define REALDATASELECTORHBAR_H

#include "WinDllMacros.h"
#include <QToolBar>

class RealDataSelectorActions;
class QToolButton;

//! Toolbar on top of selector tree with hamburger-like menu button.

class BA_CORE_API_ RealDataSelectorHBar : public QToolBar
{
    Q_OBJECT
public:
    RealDataSelectorHBar(RealDataSelectorActions* actions, QWidget* parent = nullptr);

private slots:
    void onDropDownMenuRequest();

private:
    QToolButton* m_dropDownMenuButton;
    RealDataSelectorActions* m_actions;
};

#endif // REALDATASELECTORHBAR_H
