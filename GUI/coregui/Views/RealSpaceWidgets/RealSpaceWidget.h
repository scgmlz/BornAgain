// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/RealSpaceWidgets/RealSpaceWidget.h
//! @brief     Defines class RealSpaceWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_VIEWS_REALSPACEWIDGETS_REALSPACEWIDGET_H
#define BORNAGAIN_GUI_COREGUI_VIEWS_REALSPACEWIDGETS_REALSPACEWIDGET_H

#include "Wrap/WinDllMacros.h"
#include <QWidget>

#include <QTreeView>

class RealSpaceToolBar;
class RealSpaceCanvas;
class RealSpaceActions;
class SampleModel;

//! Prototype of real space widget to present sample structure in 3D view.

class BA_CORE_API_ RealSpaceWidget : public QWidget
{
    Q_OBJECT

public:
    RealSpaceWidget(SampleModel* sampleModel = nullptr,
                    QItemSelectionModel* selectionModel = nullptr, QWidget* parent = nullptr);

protected:
    void showEvent(QShowEvent*) override;
    void hideEvent(QHideEvent*) override;

private:
    RealSpaceActions* m_actions;
    RealSpaceToolBar* m_toolBar;
    RealSpaceCanvas* m_canvas;
    SampleModel* m_sampleModel;
    QItemSelectionModel* m_selectionModel;
};

#endif // BORNAGAIN_GUI_COREGUI_VIEWS_REALSPACEWIDGETS_REALSPACEWIDGET_H
