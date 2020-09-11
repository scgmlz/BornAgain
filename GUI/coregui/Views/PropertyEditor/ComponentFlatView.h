// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/PropertyEditor/ComponentFlatView.h
//! @brief     Defines class ComponentFlatView
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_VIEWS_PROPERTYEDITOR_COMPONENTFLATVIEW_H
#define BORNAGAIN_GUI_COREGUI_VIEWS_PROPERTYEDITOR_COMPONENTFLATVIEW_H

#include "GUI/coregui/Views/PropertyEditor/ComponentView.h"
#include <memory>

class SessionItem;
class SessionModel;
class QGridLayout;
class QBoxLayout;
class PropertyWidgetItem;

//! Component property widget for SessionItems. On the contrary to ComponentTreeView
//! properties are presented as widgets in grid layout.
//! Shows only PropertyItems and current items of GroupProperties.

class BA_CORE_API_ ComponentFlatView : public ComponentView
{
    Q_OBJECT
public:
    ComponentFlatView(QWidget* parent = nullptr);
    ~ComponentFlatView();

    void setItem(SessionItem* item);
    void addItem(SessionItem* item);

    void setModel(SessionModel* model);

    void clearEditor();

    void setShowChildren(bool show);

public slots:
    void onDataChanged(const QModelIndex& topLeft, const QModelIndex& bottomRight,
                       const QVector<int>& roles);

private:
    void clearLayout();
    void updateItemProperties();
    void updateItemRoles(SessionItem* item);
    void initGridLayout();
    PropertyWidgetItem* createWidget(const SessionItem* item);

    QBoxLayout* m_mainLayout;
    QGridLayout* m_gridLayout;
    QVector<PropertyWidgetItem*> m_widgetItems;
    SessionModel* m_model;
    bool m_show_children;
    QVector<const SessionItem*> m_topItems;
};

#endif // BORNAGAIN_GUI_COREGUI_VIEWS_PROPERTYEDITOR_COMPONENTFLATVIEW_H
