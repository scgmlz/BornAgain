// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/CommonWidgets/InfoPanel.cpp
//! @brief     Declares class InfoPanel
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/coregui/Views/CommonWidgets/InfoPanel.h"
#include "GUI/coregui/Views/CommonWidgets/InfoPanelToolBar.h"
#include <QBoxLayout>
#include <QResizeEvent>
#include <QStackedWidget>

namespace
{
const int minimum_widget_height = 25; // height of toolbar
const int minimum_height_before_collapse = 50;
const int default_height = 200;
} // namespace

InfoPanel::InfoPanel(QWidget* parent)
    : QFrame(parent), m_toolBar(new InfoPanelToolBar), m_stackedWidget(new QStackedWidget),
      m_cached_height(default_height)
{
    auto mainLayout = new QVBoxLayout;
    mainLayout->addWidget(m_toolBar);
    mainLayout->addWidget(m_stackedWidget);

    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setMargin(0);
    mainLayout->setSpacing(0);

    setLayout(mainLayout);

    connect(m_toolBar, &InfoPanelToolBar::expandButtonClicked, this,
            &InfoPanel::onExpandButtonClicked);
    connect(m_toolBar, &InfoPanelToolBar::closeButtonClicked, this,
            &InfoPanel::onCloseButtonClicked);
}

QSize InfoPanel::sizeHint() const
{
    QSize result = m_toolBar->sizeHint();

    if (QWidget* widget = m_stackedWidget->currentWidget()) {
        if (widget->isVisible())
            result.setHeight(widget->height() + m_toolBar->height());
    } else {
        result.setHeight(m_toolBar->height());
    }

    return result;
}

QSize InfoPanel::minimumSizeHint() const
{
    return QSize(minimum_widget_height, minimum_widget_height);
}

void InfoPanel::onExpandButtonClicked()
{
    setContentVisible(!isContentVisible(), true);
}

void InfoPanel::onCloseButtonClicked()
{
    emit widgetCloseRequest();
}

void InfoPanel::setContentVisible(bool editor_status, bool dock_notify)
{
    m_toolBar->setExpandStatus(editor_status);
    if (editor_status) {
        if (m_cached_height)
            if (dock_notify)
                emit widgetHeightRequest(m_cached_height);

        if (m_stackedWidget->currentWidget())
            m_stackedWidget->currentWidget()->show();

    } else {
        m_cached_height = (height() < minimum_height_before_collapse ? default_height : height());
        if (m_stackedWidget->currentWidget())
            m_stackedWidget->currentWidget()->hide();

        if (dock_notify)
            emit widgetHeightRequest(minimum_widget_height);
    }
}

bool InfoPanel::isContentVisible()
{
    if (m_stackedWidget->currentWidget())
        return m_stackedWidget->currentWidget()->isVisible();

    return false;
}

void InfoPanel::resizeEvent(QResizeEvent* event)
{
    // widget is schrinking in height
    if (event->oldSize().height() > event->size().height()) {
        if (event->size().height() <= minimum_height_before_collapse && isContentVisible())
            setContentVisible(false);
    }

    // widget is growing in height
    if (event->oldSize().height() < event->size().height()) {
        if (event->size().height() > minimum_height_before_collapse && !isContentVisible())
            setContentVisible(true);
    }

    QWidget::resizeEvent(event);
}
