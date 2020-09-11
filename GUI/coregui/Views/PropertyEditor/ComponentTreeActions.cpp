// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/PropertyEditor/ComponentTreeActions.cpp
//! @brief     Implements class ComponentTreeActions
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/coregui/Views/PropertyEditor/ComponentTreeActions.h"
#include "GUI/coregui/Models/SessionItem.h"
#include <QAction>
#include <QMenu>

ComponentTreeActions::ComponentTreeActions(QObject* parent) : QObject(parent) {}

//! Creates right-mouse-click context menu on top of ComponentTreeView
//! which will allow user to switch between scientific notation and the notation
//! with a specified number of decimals.

void ComponentTreeActions::onCustomContextMenuRequested(const QPoint& point, SessionItem& item)
{
    bool sc_editor = item.editorType() == "ScientificDouble";

    QMenu menu;
    QAction* scientificAction = menu.addAction("Scientific presentation");
    scientificAction->setCheckable(true);
    auto doubleMenu = menu.addMenu("Double presentation");

    // To select scientific notation
    scientificAction->setChecked(sc_editor);
    connect(scientificAction, &QAction::triggered, [&]() {
        if (scientificAction->isChecked())
            item.setEditorType("ScientificDouble");
        else
            item.setEditorType("Default");
    });

    // to select number of decimals
    const int nmaxdigits = 8;
    for (int i = 1; i <= nmaxdigits; ++i) {
        auto action = doubleMenu->addAction(QString("%1 digits").arg(i));
        if (!sc_editor && item.decimals() == i)
            action->setChecked(true);
        connect(action, &QAction::triggered, [i, &item] {
            item.setEditorType("Default");
            item.setDecimals(i);
        });
    }
    menu.exec(point);
}
