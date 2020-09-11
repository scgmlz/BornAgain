// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/mainwindow/StyledToolBar.h
//! @brief     Defines class StyledToolBar
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_MAINWINDOW_STYLEDTOOLBAR_H
#define BORNAGAIN_GUI_COREGUI_MAINWINDOW_STYLEDTOOLBAR_H

#include "Wrap/WinDllMacros.h"
#include <QToolBar>

//! The StyledToolBar class represents our standard narrow toolbar with the height 24 pixels.

class BA_CORE_API_ StyledToolBar : public QToolBar
{
    Q_OBJECT

public:
    explicit StyledToolBar(QWidget* parent = nullptr);
    void addStyledSeparator();
    void addSpacing(int width = 2);
    void addStyledExpand();

protected:
    void contextMenuEvent(QContextMenuEvent*);
};

#endif // BORNAGAIN_GUI_COREGUI_MAINWINDOW_STYLEDTOOLBAR_H
