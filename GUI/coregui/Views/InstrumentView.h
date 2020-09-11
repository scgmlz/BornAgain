// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/InstrumentView.h
//! @brief     Defines class InstrumentView
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_VIEWS_INSTRUMENTVIEW_H
#define BORNAGAIN_GUI_COREGUI_VIEWS_INSTRUMENTVIEW_H

#include "GUI/coregui/Views/CommonWidgets/ItemStackPresenter.h"
#include "Wrap/WinDllMacros.h"
#include <QWidget>

class MainWindow;
class DetectorItem;
class InstrumentViewActions;
class InstrumentViewToolBar;
class InstrumentSelectorWidget;
class InstrumentEditorWidget;
class InstrumentModel;

class BA_CORE_API_ InstrumentView : public QWidget
{
    Q_OBJECT

public:
    InstrumentView(MainWindow* mainWindow);

public slots:
    void onExtendedDetectorEditorRequest(DetectorItem* detectorItem);

private slots:
    void onItemSelectionChanged(SessionItem* instrumentItem);

protected:
    void showEvent(QShowEvent*);

private:
    InstrumentViewActions* m_actions;
    InstrumentViewToolBar* m_toolBar;
    InstrumentSelectorWidget* m_instrumentSelector;
    ItemStackPresenter<InstrumentEditorWidget>* m_instrumentEditor;
    InstrumentModel* m_instrumentModel;
};

#endif // BORNAGAIN_GUI_COREGUI_VIEWS_INSTRUMENTVIEW_H
