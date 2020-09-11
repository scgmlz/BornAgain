// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/InstrumentWidgets/InstrumentSelectorWidget.cpp
//! @brief     Implements class InstrumentSelectorWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/coregui/Views/InstrumentWidgets/InstrumentSelectorWidget.h"
#include "GUI/coregui/Models/InstrumentModel.h"
#include "GUI/coregui/Models/SessionItem.h"
#include <QAction>
#include <QListView>
#include <QMenu>
#include <QPushButton>
#include <QVBoxLayout>

InstrumentSelectorWidget::InstrumentSelectorWidget(InstrumentModel* model, QWidget* parent)
    : ItemSelectorWidget(parent)
{
    setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);

    listView()->setViewMode(QListView::IconMode);
    listView()->setIconSize(QSize(96, 84));
    listView()->setMovement(QListView::Static);
    listView()->setMaximumWidth(200);
    listView()->setSpacing(12);

    listView()->setObjectName("listView");
    listView()->setStyleSheet(
        QString::fromUtf8("QListView#listView\n"
                          "{\n"
                          "   selection-background-color : rgb(98,100,105); \n"
                          "   selection-color: rgb(255,255,255);\n"
                          "   border: 1px solid rgb(98,100,105);\n"
                          "}\n"));

    setModel(model);
    layout()->setMargin(10);
}

QSize InstrumentSelectorWidget::sizeHint() const
{
    return QSize(170, 400);
}

QSize InstrumentSelectorWidget::minimumSizeHint() const
{
    return QSize(96, 200);
}
