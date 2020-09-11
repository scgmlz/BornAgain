// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/PropertyEditor/ComponentTreeView.cpp
//! @brief     Implements class ComponentTreeView
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/coregui/Views/PropertyEditor/ComponentTreeView.h"
#include "GUI/coregui/Models/ComponentProxyModel.h"
#include "GUI/coregui/Models/SessionModel.h"
#include "GUI/coregui/Models/SessionModelDelegate.h"
#include "GUI/coregui/Views/PropertyEditor/ComponentTreeActions.h"
#include "GUI/coregui/utils/CustomEventFilters.h"
#include "GUI/coregui/utils/StyleUtils.h"
#include <QBoxLayout>
#include <QStandardItemModel>
#include <QTreeView>

ComponentTreeView::ComponentTreeView(QWidget* parent)
    : ComponentView(parent), m_tree(new QTreeView), m_delegate(new SessionModelDelegate(this)),
      m_proxyModel(new ComponentProxyModel(this)), m_placeHolderModel(new QStandardItemModel(this)),
      m_eventFilter(new RightMouseButtonEater), m_actions(new ComponentTreeActions(this)),
      m_show_root_item(false)
{
    auto layout = new QVBoxLayout;

    layout->setMargin(0);
    layout->setSpacing(0);
    layout->addWidget(m_tree);

    setLayout(layout);

    QStringList labels = {"Name", "Value"};
    m_placeHolderModel->setHorizontalHeaderLabels(labels);

    StyleUtils::setPropertyStyle(m_tree);
    m_tree->setRootIsDecorated(false);
    m_tree->setModel(m_placeHolderModel);
    m_tree->setItemDelegate(m_delegate);

    // provide one click editing, but still keeping custom context menu alive
    m_tree->setEditTriggers(QAbstractItemView::AllEditTriggers);
    m_tree->viewport()->installEventFilter(m_eventFilter.get());

    // custom context menu setup
    m_tree->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(m_tree, &QTreeView::customContextMenuRequested, this,
            &ComponentTreeView::onCustomContextMenuRequested);
}

ComponentTreeView::~ComponentTreeView() = default;

void ComponentTreeView::setItem(SessionItem* item)
{
    if (!item) {
        setModel(nullptr);
        return;
    }
    setModel(item->model());
    setRootIndex(item->index(), m_show_root_item);
    m_tree->expandAll();
}

void ComponentTreeView::clearEditor()
{
    m_tree->setModel(m_placeHolderModel);
}

void ComponentTreeView::setModel(SessionModel* model)
{
    m_proxyModel->setSessionModel(model);
    if (model)
        m_tree->setModel(m_proxyModel);
    else
        m_tree->setModel(m_placeHolderModel);
}

void ComponentTreeView::setRootIndex(const QModelIndex& index, bool show_root_item)
{
    if (QWidget* editor = m_tree->indexWidget(m_tree->currentIndex()))
        m_delegate->closeEditor(editor, QAbstractItemDelegate::NoHint);
    ASSERT(m_proxyModel);
    m_proxyModel->setRootIndex(index);
    if (!show_root_item)
        m_tree->setRootIndex(m_proxyModel->mapFromSource(index));
}

void ComponentTreeView::setShowHeader(bool show)
{
    m_tree->setHeaderHidden(!show);
}

void ComponentTreeView::setShowRootItem(bool show)
{
    m_show_root_item = show;
}

void ComponentTreeView::onCustomContextMenuRequested(const QPoint& pos)
{
    auto point = m_tree->mapToGlobal(pos);
    auto treeIndex = m_tree->indexAt(pos);
    if (!treeIndex.isValid())
        return;

    auto index = m_proxyModel->mapToSource(treeIndex);

    SessionItem* item = static_cast<SessionItem*>(index.internalPointer());
    if (item->value().type() != QVariant::Double)
        return;

    m_actions->onCustomContextMenuRequested(point, *item);
}
