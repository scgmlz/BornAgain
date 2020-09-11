// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/MaterialEditor/MaterialEditorToolBar.h
//! @brief     Defines class MaterialEditorToolBar
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_VIEWS_MATERIALEDITOR_MATERIALEDITORTOOLBAR_H
#define BORNAGAIN_GUI_COREGUI_VIEWS_MATERIALEDITOR_MATERIALEDITORTOOLBAR_H

#include "Wrap/WinDllMacros.h"
#include <QToolBar>

class QAction;
class MaterialModel;
class QItemSelectionModel;
class QPoint;
class QMenu;

//! Toolbar for MaterialEditor.

class BA_CORE_API_ MaterialEditorToolBar : public QToolBar
{
    Q_OBJECT
public:
    MaterialEditorToolBar(MaterialModel* materialModel, QWidget* parent = nullptr);

    void setSelectionModel(QItemSelectionModel* selectionModel);

public slots:
    void onCustomContextMenuRequested(const QPoint& point);

private slots:
    void onNewMaterialAction();
    void onCloneMaterialAction();
    void onRemoveMaterialAction();

private:
    void initItemContextMenu(QMenu& menu);

    MaterialModel* m_materialModel;
    QItemSelectionModel* m_selectionModel;
    QAction* m_newMaterialAction;
    QAction* m_cloneMaterialAction;
    QAction* m_removeMaterialAction;
};

#endif // BORNAGAIN_GUI_COREGUI_VIEWS_MATERIALEDITOR_MATERIALEDITORTOOLBAR_H
