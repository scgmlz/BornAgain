// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/SampleDesigner/SampleTreeWidget.cpp
//! @brief     Implements class SampleTreeWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/coregui/Views/SampleDesigner/SampleTreeWidget.h"
#include "GUI/coregui/Models/FilterPropertyProxy.h"
#include "GUI/coregui/Models/ItemFactory.h"
#include "GUI/coregui/Models/SampleModel.h"
#include "GUI/coregui/Views/SampleDesigner/ItemTreeView.h"
#include <QAction>
#include <QMenu>
#include <QVBoxLayout>

SampleTreeWidget::SampleTreeWidget(QWidget* parent, SampleModel* model)
    : QWidget(parent), m_treeView(new ItemTreeView), m_sampleModel(model)
{
    setWindowTitle("Sample Tree");
    setObjectName(QLatin1String("SampleTreeWidget"));

    auto mainLayout = new QVBoxLayout;
    mainLayout->setMargin(0);
    mainLayout->setSpacing(0);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->addWidget(m_treeView);
    setLayout(mainLayout);

    FilterPropertyProxy* proxy = new FilterPropertyProxy(1, parent);
    proxy->setSourceModel(m_sampleModel);
    m_treeView->setModel(proxy);
    m_treeView->setAttribute(Qt::WA_MacShowFocusRect, false);

    connect(m_treeView, SIGNAL(customContextMenuRequested(const QPoint&)), this,
            SLOT(showContextMenu(const QPoint&)));

    m_delete_item_action = new QAction("Delete", this);
    m_delete_item_action->setStatusTip("Delete current object");
    connect(m_delete_item_action, SIGNAL(triggered()), this, SLOT(deleteItem()));

    m_treeView->expandAll();
    connect(m_treeView->model(), SIGNAL(rowsInserted(QModelIndex, int, int)), m_treeView,
            SLOT(expandAll()));
}

QTreeView* SampleTreeWidget::treeView()
{
    return m_treeView;
}

void SampleTreeWidget::showContextMenu(const QPoint& pnt)
{
    QMenu menu;
    QMenu add_menu("Add");
    QVector<QString> addItemNames;
    QModelIndex parent_index = FilterPropertyProxy::toSourceIndex(treeView()->indexAt(pnt));
    treeView()->setCurrentIndex(parent_index);
    if (!parent_index.isValid()) {
        addItemNames = ItemFactory::ValidTopItemTypes().toVector();
    } else {
        addItemNames = m_sampleModel->acceptableDefaultItemTypes(parent_index);
    }
    if (addItemNames.size() > 0) {
        for (QString item_name : addItemNames) {
            QAction* add_action = nullptr;
            if (m_add_action_map.contains(item_name)) {
                add_action = m_add_action_map[item_name];
            } else {
                add_action = new QAction(item_name, this);
                m_add_action_map[item_name] = add_action;
                connect(add_action, &QAction::triggered, [=] { addItem(item_name); });
            }
            add_menu.addAction(add_action);
        }
        menu.addMenu(&add_menu);
    }
    if (parent_index.isValid()) {
        menu.addAction(m_delete_item_action);
    }
    if (!menu.isEmpty()) {
        menu.exec(treeView()->mapToGlobal(pnt));
    }
}

void SampleTreeWidget::addItem(const QString& item_name)
{
    QModelIndex currentIndex = FilterPropertyProxy::toSourceIndex(treeView()->currentIndex());

    QModelIndex currentIndexAtColumnZero = getIndexAtColumnZero(currentIndex);
    SessionItem* new_item = m_sampleModel->insertNewItem(item_name, currentIndexAtColumnZero);
    if (new_item) {
        QModelIndex new_index = m_sampleModel->indexOfItem(new_item);
        scrollToIndex(new_index);
    }
}

void SampleTreeWidget::deleteItem()
{
    QModelIndex currentIndex = FilterPropertyProxy::toSourceIndex(treeView()->currentIndex());

    if (!currentIndex.isValid())
        return;
    QModelIndex parent_index = m_sampleModel->parent(currentIndex);
    int row = currentIndex.row();
    if (currentIndex.isValid()) {
        m_sampleModel->removeRows(row, 1, parent_index);
    }
}

void SampleTreeWidget::scrollToIndex(const QModelIndex& index)
{
    if (index.isValid()) {
        treeView()->scrollTo(index);
    }
}

QModelIndex SampleTreeWidget::getIndexAtColumnZero(const QModelIndex& index)
{
    if (index == QModelIndex() || index.column() == 0)
        return index;
    QModelIndex parent_index = m_sampleModel->parent(index);
    return m_sampleModel->index(index.row(), 0, parent_index);
}
