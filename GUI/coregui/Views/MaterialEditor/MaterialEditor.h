// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/MaterialEditor/MaterialEditor.h
//! @brief     Defines class MaterialEditor
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_VIEWS_MATERIALEDITOR_MATERIALEDITOR_H
#define BORNAGAIN_GUI_COREGUI_VIEWS_MATERIALEDITOR_MATERIALEDITOR_H

#include "Wrap/WinDllMacros.h"
#include <QWidget>

class MaterialModel;
class MaterialEditorToolBar;
class QSplitter;
class QListView;
class ComponentEditor;
class QItemSelection;
class QItemSelectionModel;
class MaterialItem;
class ExternalProperty;

//! Main widget of MaterialEditor

class BA_CORE_API_ MaterialEditor : public QWidget
{
    Q_OBJECT

public:
    MaterialEditor(MaterialModel* materialModel, QWidget* parent = nullptr);

    QItemSelectionModel* selectionModel();

    MaterialItem* selectedMaterial();

    void setInitialMaterialProperty(const ExternalProperty& matProperty);

    bool modelWasChanged() const;

private slots:
    void onSelectionChanged(const QItemSelection& selected, const QItemSelection&);
    void onDataChanged(const QModelIndex&, const QModelIndex&, const QVector<int>&);
    void onRowsInserted(const QModelIndex&, int, int);
    void onRowsRemoved(const QModelIndex&, int, int);

protected:
    void contextMenuEvent(QContextMenuEvent* event);

private:
    void init_views();

    MaterialModel* m_materialModel;
    MaterialEditorToolBar* m_toolBar;
    QSplitter* m_splitter;
    QListView* m_listView;
    ComponentEditor* m_componentEditor;
    bool m_model_was_modified;
};

#endif // BORNAGAIN_GUI_COREGUI_VIEWS_MATERIALEDITOR_MATERIALEDITOR_H
