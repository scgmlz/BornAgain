// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/CommonWidgets/ItemSelectorWidget.cpp
//! @brief     Implements class ItemSelectorWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/coregui/Views/CommonWidgets/ItemSelectorWidget.h"
#include "GUI/coregui/Models/SessionDecorationModel.h"
#include "GUI/coregui/Models/SessionItem.h"
#include "GUI/coregui/Models/SessionModel.h"
#include "GUI/coregui/mainwindow/mainwindow_constants.h"
#include <QListView>
#include <QVBoxLayout>

ItemSelectorWidget::ItemSelectorWidget(QWidget* parent)
    : QWidget(parent), m_listView(new QListView), m_model(nullptr)
{
    setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);

    QVBoxLayout* layout = new QVBoxLayout;
    layout->setMargin(0);

    layout->addWidget(m_listView);
    setLayout(layout);

    m_listView->setContextMenuPolicy(Qt::CustomContextMenu);
    m_listView->setAttribute(Qt::WA_MacShowFocusRect, false);

    connect(m_listView, SIGNAL(customContextMenuRequested(const QPoint&)), this,
            SLOT(onCustomContextMenuRequested(const QPoint&)));
}

ItemSelectorWidget::~ItemSelectorWidget() {}

QSize ItemSelectorWidget::sizeHint() const
{
    return QSize(Constants::ITEM_SELECTOR_WIDGET_WIDTH, Constants::ITEM_SELECTOR_WIDGET_HEIGHT);
}

QSize ItemSelectorWidget::minimumSizeHint() const
{
    return QSize(25, 25);
}

void ItemSelectorWidget::setModel(SessionModel* model)
{
    if (model == m_model)
        return;

    disconnectModel();
    m_model = model;
    connectModel();
}

void ItemSelectorWidget::setItemDelegate(QAbstractItemDelegate* delegate)
{
    m_listView->setItemDelegate(delegate);
}

QItemSelectionModel* ItemSelectorWidget::selectionModel()
{
    return m_listView->selectionModel();
}

QListView* ItemSelectorWidget::listView()
{
    return m_listView;
}

void ItemSelectorWidget::select(const QModelIndex& index,
                                QItemSelectionModel::SelectionFlags command)
{
    selectionModel()->select(index, command);
}

//! select last item if no selection exists

void ItemSelectorWidget::updateSelection()
{
    if (!selectionModel()->hasSelection())
        selectLast();
}

void ItemSelectorWidget::selectLast()
{
    QModelIndex itemIndex = m_model->index(m_model->rowCount(QModelIndex()) - 1, 0, QModelIndex());
    selectionModel()->select(itemIndex, QItemSelectionModel::ClearAndSelect);
}

void ItemSelectorWidget::onSelectionChanged(const QItemSelection& selected, const QItemSelection&)
{
    QModelIndexList indexes = selected.indexes();
    SessionItem* selectedItem(0);

    if (indexes.size())
        selectedItem = m_model->itemForIndex(indexes.back());

    emit selectionChanged(selectedItem);
}

void ItemSelectorWidget::onCustomContextMenuRequested(const QPoint& point)
{
    emit contextMenuRequest(m_listView->mapToGlobal(point), m_listView->indexAt(point));
}

void ItemSelectorWidget::connectModel()
{
    if (!m_model)
        return;

    m_decorationModel.reset(new SessionDecorationModel(nullptr, m_model));
    m_listView->setModel(m_decorationModel.get());

    connect(m_listView->selectionModel(),
            SIGNAL(selectionChanged(const QItemSelection&, const QItemSelection&)), this,
            SLOT(onSelectionChanged(const QItemSelection&, const QItemSelection&)),
            Qt::UniqueConnection);
}

void ItemSelectorWidget::disconnectModel()
{
    m_listView->setModel(nullptr);
    m_model = nullptr;
}

//! provide default selection when widget is shown
void ItemSelectorWidget::showEvent(QShowEvent*)
{
    if (!m_model || !selectionModel())
        return;

    if (selectionModel()->selectedIndexes().isEmpty() && m_model->rowCount(QModelIndex()) != 0)
        selectionModel()->select(m_model->index(0, 0, QModelIndex()), QItemSelectionModel::Select);
}
