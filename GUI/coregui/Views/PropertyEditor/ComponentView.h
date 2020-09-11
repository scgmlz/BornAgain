// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/PropertyEditor/ComponentView.h
//! @brief     Defines class ComponentView
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_VIEWS_PROPERTYEDITOR_COMPONENTVIEW_H
#define BORNAGAIN_GUI_COREGUI_VIEWS_PROPERTYEDITOR_COMPONENTVIEW_H

#include "Wrap/WinDllMacros.h"
#include <QWidget>

class SessionItem;

//! Base class for ComponentTreeView and ComponentFlatView.

class BA_CORE_API_ ComponentView : public QWidget
{
    Q_OBJECT
public:
    ComponentView(QWidget* parent = nullptr) : QWidget(parent) {}

    virtual void clearEditor() = 0;
    virtual void setItem(SessionItem* item) = 0;
    virtual void addItem(SessionItem*) {}
};

#endif // BORNAGAIN_GUI_COREGUI_VIEWS_PROPERTYEDITOR_COMPONENTVIEW_H
