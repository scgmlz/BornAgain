// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/SampleView.h
//! @brief     Defines class SampleView
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_VIEWS_SAMPLEVIEW_H
#define BORNAGAIN_GUI_COREGUI_VIEWS_SAMPLEVIEW_H

#include "Wrap/WinDllMacros.h"
#include "fancymainwindow.h"

class MainWindow;
class SampleViewDocks;
class SampleDesigner;
class SampleToolBar;
class ApplicationModels;
class QItemSelectionModel;
class SampleViewStatusBar;
class QShowEvent;
class QHideEvent;
class SampleViewActions;

class BA_CORE_API_ SampleView : public Manhattan::FancyMainWindow
{
    Q_OBJECT

public:
    SampleView(MainWindow* mainWindow);

    ApplicationModels* models();

    SampleViewDocks* docks();

public slots:
    void onDockMenuRequest();

protected:
    virtual void showEvent(QShowEvent* event);
    virtual void hideEvent(QHideEvent* event);

private:
    void connectSignals();

    QItemSelectionModel* selectionModel();

    ApplicationModels* m_models;

    SampleViewDocks* m_docks;

    SampleDesigner* sampleDesigner();

    SampleViewActions* m_actions;

    SampleToolBar* m_toolBar;

    SampleViewStatusBar* m_statusBar;
};

#endif // BORNAGAIN_GUI_COREGUI_VIEWS_SAMPLEVIEW_H
