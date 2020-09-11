// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/CommonWidgets/ItemComboWidget.cpp
//! @brief     Implements class ItemComboWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/coregui/Views/CommonWidgets/ItemComboWidget.h"
#include "Core/Basics/Assert.h"
#include "GUI/coregui/Views/CommonWidgets/ItemComboToolBar.h"
#include "GUI/coregui/Views/CommonWidgets/SessionItemWidget.h"
#include "GUI/coregui/utils/GUIHelpers.h"
#include <QComboBox>
#include <QEvent>
#include <QStackedWidget>
#include <QVBoxLayout>

ItemComboWidget::ItemComboWidget(QWidget* parent)
    : SessionItemWidget(parent), m_toolBar(new ItemComboToolBar),
      m_stackedWidget(new QStackedWidget)
{
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_stackedWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    QVBoxLayout* layout = new QVBoxLayout;
    layout->setMargin(0);
    layout->setSpacing(0);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(m_toolBar);
    layout->addWidget(m_stackedWidget);
    setLayout(layout);

    connect(m_toolBar, SIGNAL(comboChanged(QString)), this, SLOT(onComboChanged(QString)));
}

void ItemComboWidget::registerWidget(const QString& presentationType, factory_function_t f)
{
    m_widgetFactory.registerItem(presentationType, f);
}

//! Sets stack to show widget corresponding to given presentation

void ItemComboWidget::setPresentation(const QString& presentationType)
{
    if (!activePresentationList(currentItem()).contains(presentationType))
        return;

    m_toolBar->setPresentation(presentationType);

    ASSERT(currentItem());

    SessionItemWidget* widget = m_presentationTypeToWidget[presentationType];

    if (!widget) {
        widget = m_widgetFactory.createItemPtr(presentationType).release();
        m_stackedWidget->addWidget(widget);
        m_presentationTypeToWidget[presentationType] = widget;
    }
    ASSERT(widget);
    widget->setItem(currentItem());
    m_toolBar->setActionList(widget->actionList());
    m_stackedWidget->setCurrentWidget(widget);
    if (widget->isHidden())
        widget->show();

    setSizeToCurrentWidget();
}

void ItemComboWidget::setToolBarVisible(bool value)
{
    m_toolBar->setVisible(value);
}

//! Returns list of active presentations for given item. Active presentation is the one
//! which is present in QComboBox selector and can be selected. For example, if JobItem
//! is fittable, the list will contain "FitComparisonWidgetName".

QStringList ItemComboWidget::activePresentationList(SessionItem* item)
{
    Q_UNUSED(item);
    return QStringList();
}

//! Returns full list of presentations available for given item.

QStringList ItemComboWidget::presentationList(SessionItem* item)
{
    return activePresentationList(item);
}

//! Presentation which should be shown for current item.

QString ItemComboWidget::itemPresentation() const
{
    return selectedPresentation();
}

//! Presentation selected in combo selector.

QString ItemComboWidget::selectedPresentation() const
{
    return m_toolBar->currentPresentation();
}

void ItemComboWidget::subscribeToItem()
{
    m_toolBar->setPresentationList(presentationList(currentItem()),
                                   activePresentationList(currentItem()));
    setPresentation(itemPresentation());
}

void ItemComboWidget::onComboChanged(const QString&)
{
    setPresentation(selectedPresentation());
}

//! Resizes QStackedWidget to currently active page.

void ItemComboWidget::setSizeToCurrentWidget()
{
    for (int i = 0; i < m_stackedWidget->count(); ++i) {
        // determine the vertical size policy
        QSizePolicy::Policy policy = QSizePolicy::Ignored;
        if (i == m_stackedWidget->currentIndex())
            policy = QSizePolicy::Expanding;

        // update the size policy
        auto page = m_stackedWidget->widget(i);
        page->setSizePolicy(policy, policy);
    }
}
