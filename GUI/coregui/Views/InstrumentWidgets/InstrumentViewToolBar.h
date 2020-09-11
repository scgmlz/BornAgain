// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/InstrumentWidgets/InstrumentViewToolBar.h
//! @brief     Defines class InstrumentViewToolBar
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_VIEWS_INSTRUMENTWIDGETS_INSTRUMENTVIEWTOOLBAR_H
#define BORNAGAIN_GUI_COREGUI_VIEWS_INSTRUMENTWIDGETS_INSTRUMENTVIEWTOOLBAR_H

#include "GUI/coregui/mainwindow/StyledToolBar.h"
#include <QList>

class QAction;
class QToolButton;
class InstrumentViewActions;
class QMenu;

//! Styled tool bar on top of InstrumentView with add/remove/clone instrument buttons.

class BA_CORE_API_ InstrumentViewToolBar : public StyledToolBar
{
    Q_OBJECT

public:
    explicit InstrumentViewToolBar(InstrumentViewActions* actions, QWidget* parent = nullptr);

private slots:
    void onAddInstrument();

private:
    QToolButton* m_addInstrumentButton;
    QToolButton* m_removeInstrumentButton;
    QToolButton* m_cloneInstrumentButton;
    QMenu* m_addInstrumentMenu;
};

#endif // BORNAGAIN_GUI_COREGUI_VIEWS_INSTRUMENTWIDGETS_INSTRUMENTVIEWTOOLBAR_H
