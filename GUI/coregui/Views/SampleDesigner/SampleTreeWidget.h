// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/SampleDesigner/SampleTreeWidget.h
//! @brief     Defines class SampleTreeWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_VIEWS_SAMPLEDESIGNER_SAMPLETREEWIDGET_H
#define BORNAGAIN_GUI_COREGUI_VIEWS_SAMPLEDESIGNER_SAMPLETREEWIDGET_H

#include "Wrap/WinDllMacros.h"
#include <QMap>
#include <QWidget>

class ItemTreeView;
class SampleModel;
class QTreeView;
class QPoint;
class QAction;

//! Holds tree to select top level sample items. Part of SampleView.

class BA_CORE_API_ SampleTreeWidget : public QWidget
{
    Q_OBJECT
public:
    SampleTreeWidget(QWidget* parent, SampleModel* model);

    QTreeView* treeView();

protected slots:
    void showContextMenu(const QPoint& pnt);
    void addItem(const QString& item_name);
    void deleteItem();

private:
    void scrollToIndex(const QModelIndex& index);
    QModelIndex getIndexAtColumnZero(const QModelIndex& index);

    QMap<QString, QAction*> m_add_action_map;
    QAction* m_delete_item_action;

    ItemTreeView* m_treeView;
    SampleModel* m_sampleModel;
};

#endif // BORNAGAIN_GUI_COREGUI_VIEWS_SAMPLEDESIGNER_SAMPLETREEWIDGET_H
