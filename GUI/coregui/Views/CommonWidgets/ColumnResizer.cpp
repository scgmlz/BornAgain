// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/CommonWidgets/ColumnResizer.cpp
//! @brief     Implements class ColumnResizer
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

/*
 * Copyright 2011 Aurélien Gâteau <agateau@kde.org>
 * License: LGPL v2.1 or later (see COPYING)
 */
#include "GUI/coregui/Views/CommonWidgets/ColumnResizer.h"
#include "Core/Basics/Assert.h"

#include <QDebug>
#include <QEvent>
#include <QFormLayout>
#include <QGridLayout>
#include <QTimer>
#include <QWidget>

class FormLayoutWidgetItem : public QWidgetItem
{
public:
    FormLayoutWidgetItem(QWidget* widget, QFormLayout* formLayout, QFormLayout::ItemRole itemRole)
        : QWidgetItem(widget), m_width(-1), m_formLayout(formLayout), m_itemRole(itemRole)
    {
    }

    QSize sizeHint() const
    {
        QSize size = QWidgetItem::sizeHint();
        if (m_width != -1) {
            size.setWidth(m_width);
        }
        return size;
    }

    QSize minimumSize() const
    {
        QSize size = QWidgetItem::minimumSize();
        if (m_width != -1) {
            size.setWidth(m_width);
        }
        return size;
    }

    QSize maximumSize() const
    {
        QSize size = QWidgetItem::maximumSize();
        if (m_width != -1) {
            size.setWidth(m_width);
        }
        return size;
    }

    void setWidth(int width)
    {
        if (width != m_width) {
            m_width = width;
            invalidate();
        }
    }

    void setGeometry(const QRect& _rect)
    {
        QRect rect = _rect;
        int width = widget()->sizeHint().width();
        if (m_itemRole == QFormLayout::LabelRole
            && m_formLayout->labelAlignment() & Qt::AlignRight) {
            rect.setLeft(rect.right() - width);
        }
        QWidgetItem::setGeometry(rect);
    }

    QFormLayout* formLayout() const { return m_formLayout; }

private:
    int m_width;
    QFormLayout* m_formLayout;
    QFormLayout::ItemRole m_itemRole;
};

typedef QPair<QGridLayout*, int> GridColumnInfo;

class ColumnResizerPrivate
{
public:
    ColumnResizerPrivate(ColumnResizer* q_ptr)
        : q(q_ptr), m_updateTimer(new QTimer(q)), block_update(false)
    {
        m_updateTimer->setSingleShot(true);
        m_updateTimer->setInterval(0);
        QObject::connect(m_updateTimer, SIGNAL(timeout()), q, SLOT(updateWidth()));
    }

    void scheduleWidthUpdate()
    {
        if (block_update)
            return;
        m_updateTimer->start();
    }

    ColumnResizer* q;
    QTimer* m_updateTimer;
    QList<QWidget*> m_widgets;
    QList<FormLayoutWidgetItem*> m_wrWidgetItemList;
    QList<GridColumnInfo> m_gridColumnInfoList;
    bool block_update;
};

ColumnResizer::ColumnResizer(QObject* parent) : QObject(parent), d(new ColumnResizerPrivate(this))
{
}

ColumnResizer::~ColumnResizer()
{
    delete d;
}

void ColumnResizer::addWidget(QWidget* widget)
{
    d->m_widgets.append(widget);
    widget->installEventFilter(this);
    //    connect(widget, SIGNAL(destroyed(QObject*)), this, SLOT(onObjectDestroyed(QObject*)));
    d->scheduleWidthUpdate();
}

void ColumnResizer::updateWidth()
{
    if (d->block_update)
        return;
    int width = 0;
    for (auto widget : d->m_widgets) {
        width = qMax(widget->sizeHint().width(), width);
    }
    for (auto item : d->m_wrWidgetItemList) {
        item->setWidth(width);
        item->formLayout()->update();
    }
    for (auto info : d->m_gridColumnInfoList) {
        info.first->setColumnMinimumWidth(info.second, width);
    }
}

void ColumnResizer::removeWidget(QWidget* widget)
{
    if (d->m_widgets.contains(widget)) {
        d->m_widgets.removeAll(widget);
        widget->removeEventFilter(this);
    }
}

bool ColumnResizer::eventFilter(QObject*, QEvent* event)
{
    if (event->type() == QEvent::Resize) {
        d->scheduleWidthUpdate();
    }
    return false;
}

void ColumnResizer::addWidgetsFromLayout(QLayout* layout, int column)
{
    ASSERT(column >= 0);
    QGridLayout* gridLayout = qobject_cast<QGridLayout*>(layout);
    QFormLayout* formLayout = qobject_cast<QFormLayout*>(layout);
    if (gridLayout) {
        addWidgetsFromGridLayout(gridLayout, column);
    } else if (formLayout) {
        if (column > QFormLayout::SpanningRole) {
            qCritical() << "column should not be more than" << QFormLayout::SpanningRole
                        << "for QFormLayout";
            return;
        }
        QFormLayout::ItemRole role = static_cast<QFormLayout::ItemRole>(column);
        addWidgetsFromFormLayout(formLayout, role);
    } else {
        qCritical() << "Don't know how to handle layout" << layout;
    }
}

void ColumnResizer::addWidgetsFromGridLayout(QGridLayout* layout, int column)
{
    for (int row = 0; row < layout->rowCount(); ++row) {
        QLayoutItem* item = layout->itemAtPosition(row, column);
        if (!item) {
            continue;
        }
        QWidget* widget = item->widget();
        if (!widget) {
            continue;
        }
        addWidget(widget);
    }
    d->m_gridColumnInfoList << GridColumnInfo(layout, column);
    //    connect(layout, SIGNAL(destroyed(QObject*)), this, SLOT(onObjectDestroyed(QObject*)));
}

void ColumnResizer::addWidgetsFromFormLayout(QFormLayout* layout, QFormLayout::ItemRole role)
{
    for (int row = 0; row < layout->rowCount(); ++row) {
        QLayoutItem* item = layout->itemAt(row, role);
        if (!item) {
            continue;
        }
        QWidget* widget = item->widget();
        if (!widget) {
            continue;
        }
        layout->removeItem(item);
        delete item;
        FormLayoutWidgetItem* newItem = new FormLayoutWidgetItem(widget, layout, role);
        layout->setItem(row, role, newItem);
        addWidget(widget);
        d->m_wrWidgetItemList << newItem;
    }
}

void ColumnResizer::dropWidgetsFromGridLayout(QGridLayout* layout)
{
    //    d->block_update = true;
    // removing all widgets from being supervised
    for (int row = 0; row < layout->rowCount(); ++row) {
        for (int column = 0; column < layout->columnCount(); ++column) {
            QLayoutItem* item = layout->itemAtPosition(row, column);
            if (!item) {
                continue;
            }
            QWidget* widget = item->widget();
            if (!widget) {
                continue;
            }
            removeWidget(widget);
        }
    }

    // removing their layout
    QMutableListIterator<GridColumnInfo> it(d->m_gridColumnInfoList);
    while (it.hasNext()) {
        GridColumnInfo ci = it.next();
        if (ci.first == layout) {
            it.remove();
        }
    }

    //    d->block_update = false;
    // d->scheduleWidthUpdate();
}

// void ColumnResizer::onObjectDestroyed(QObject *object)
//{
//    qDebug() << "================================";
//    qDebug() << "ColumnResizer::onObjectDestroyed" << object;
//    d->block_update = true;
//    if(QWidget *widget = dynamic_cast<QWidget *>(object)) {
//        ASSERT(0);
//        if(d->m_widgets.contains(widget)) {
//            d->m_widgets.removeAll(widget);
//        }
//    }
//    else if(QGridLayout *layout = qobject_cast<QGridLayout *>(object)) {
//        QMutableListIterator<GridColumnInfo> it(d->m_gridColumnInfoList);
//        while (it.hasNext()) {
//            GridColumnInfo ci = it.next();
//            if(ci.first == layout) {
//                it.remove();
//            }
//        }
//    }
//    d->block_update = false;
//}

//#include <columnresizer.moc>
// vi: ts=4 sw=4 et
