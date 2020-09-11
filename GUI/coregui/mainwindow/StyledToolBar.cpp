// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/mainwindow/StyledToolBar.cpp
//! @brief     Implements class StyledToolBar
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/coregui/mainwindow/StyledToolBar.h"
#include <QLabel>
#include <QStyle>

StyledToolBar::StyledToolBar(QWidget* parent) : QToolBar(parent)
{
    setMovable(false);
    const int size = style()->pixelMetric(QStyle::PM_ToolBarIconSize);
    setIconSize(QSize(size, size));
    setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
    setContentsMargins(0, 0, 0, 0);
}

void StyledToolBar::addStyledSeparator()
{
    addWidget(new QLabel(" "));
    addSeparator();
    addWidget(new QLabel(" "));
}

//! Width of the spacing between buttons

void StyledToolBar::addSpacing(int width)
{
    QString space;
    space.fill(' ', width);
    addWidget(new QLabel(space));
}

void StyledToolBar::addStyledExpand()
{
    QWidget* empty = new QWidget();
    empty->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    addWidget(empty);
}

void StyledToolBar::contextMenuEvent(QContextMenuEvent*)
{
    // Context menu reimplemented to suppress the default one
}
