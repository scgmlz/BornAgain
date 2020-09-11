// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/CommonWidgets/ItemStackWidget.cpp
//! @brief     Implements class ItemStackWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/coregui/Views/CommonWidgets/ItemStackWidget.h"
#include "GUI/coregui/Models/SessionModel.h"
#include "GUI/coregui/utils/GUIHelpers.h"
#include <QStackedWidget>
#include <QVBoxLayout>

ItemStackWidget::ItemStackWidget(QWidget* parent)
    : QWidget(parent), m_stackedWidget(new QStackedWidget), m_model(nullptr),
      m_size_hint(QSize(1024, 1024))
{
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_stackedWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    QVBoxLayout* layout = new QVBoxLayout;
    layout->setMargin(0);
    layout->setSpacing(0);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(m_stackedWidget);
    setLayout(layout);
}

void ItemStackWidget::setModel(SessionModel* model)
{
    if (model == m_model)
        return;

    disconnectModel();
    m_model = model;
    connectModel();
}

QSize ItemStackWidget::sizeHint() const
{
    return m_size_hint;
}

QSize ItemStackWidget::minimumSizeHint() const
{
    return QSize(25, 25);
}

void ItemStackWidget::setSizeHint(const QSize& size_hint)
{
    m_size_hint = size_hint;
}

void ItemStackWidget::onModelAboutToBeReset()
{
    removeWidgets();
}

void ItemStackWidget::onRowsAboutToBeRemoved(const QModelIndex& parent, int first, int)
{
    SessionItem* item = m_model->itemForIndex(m_model->index(first, 0, parent));
    removeWidgetForItem(item);
}

void ItemStackWidget::connectModel()
{
    if (!m_model)
        return;

    connect(m_model, SIGNAL(modelAboutToBeReset()), this, SLOT(onModelAboutToBeReset()),
            Qt::UniqueConnection);

    connect(m_model, SIGNAL(rowsAboutToBeRemoved(QModelIndex, int, int)), this,
            SLOT(onRowsAboutToBeRemoved(QModelIndex, int, int)), Qt::UniqueConnection);
}

void ItemStackWidget::disconnectModel()
{
    if (!m_model)
        return;

    disconnect(m_model, SIGNAL(modelAboutToBeReset()), this, SLOT(onModelAboutToBeReset()));

    disconnect(m_model, SIGNAL(rowsAboutToBeRemoved(QModelIndex, int, int)), this,
               SLOT(onRowsAboutToBeRemoved(QModelIndex, int, int)));
}

//! Checks if model was set correctly.

void ItemStackWidget::validateItem(SessionItem* item)
{
    if (!item)
        return;

    if (m_model) {
        if (m_model != item->model())
            // in principle it should be possible, but should be tested
            throw GUIHelpers::Error("ItemStackWidget::validateItem() -> Error. "
                                    "Attempt to use items from different models.");
    } else {
        setModel(item->model());
    }
}
