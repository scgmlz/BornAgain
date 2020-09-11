// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/CommonWidgets/InfoPanelToolBar.cpp
//! @brief     Declares class InfoPanelToolBar
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/coregui/Views/CommonWidgets/InfoPanelToolBar.h"
#include <QAction>
#include <QHBoxLayout>
#include <QToolButton>

namespace
{
const int minimum_size = 25;
const QString icon_up = ":/images/dark-angle-up.svg";
const QString icon_down = ":/images/dark-angle-down.svg";
const QString icon_close = ":/images/dark-close.svg";
const QString expand_text = "Collapse/expand view";
const QString close_text = "Close view";
} // namespace

InfoPanelToolBar::InfoPanelToolBar(QWidget* parent)
    : QToolBar(parent), m_expandAction(new QAction(expand_text, this)),
      m_closeAction(new QAction(close_text, this)), m_expanded(false)
{
    setMinimumSize(minimum_size, minimum_size);
    setProperty("_q_custom_style_disabled", QVariant(true));

    m_expandAction->setIcon(QIcon(icon_up));
    m_expandAction->setToolTip(expand_text);
    connect(m_expandAction, &QAction::triggered, this, &InfoPanelToolBar::onExpandButtonClicked);

    m_closeAction->setIcon(QIcon(icon_close));
    m_closeAction->setToolTip(close_text);
    connect(m_closeAction, &QAction::triggered, this, &InfoPanelToolBar::closeButtonClicked);

    auto empty = new QWidget();
    empty->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    addWidget(empty);

    addAction(m_expandAction);
    addAction(m_closeAction);
}

void InfoPanelToolBar::setExpandStatus(bool status)
{
    m_expanded = status;
    if (m_expanded)
        m_expandAction->setIcon(QIcon(icon_down));
    else
        m_expandAction->setIcon(QIcon(icon_up));
}

void InfoPanelToolBar::onExpandButtonClicked()
{
    m_expanded = !m_expanded;
    setExpandStatus(m_expanded);
    emit expandButtonClicked();
}
