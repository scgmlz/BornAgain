// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/PropertyEditor/PropertyWidgetItem.h
//! @brief     Defines class PropertyWidgetItem
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_VIEWS_PROPERTYEDITOR_PROPERTYWIDGETITEM_H
#define BORNAGAIN_GUI_COREGUI_VIEWS_PROPERTYEDITOR_PROPERTYWIDGETITEM_H

#include "Wrap/WinDllMacros.h"
#include <QObject>

class QLabel;
class QWiget;
class QDataWidgetMapper;
class QGridLayout;
class SessionItem;
class SessionModelDelegate;

//! Container to hold label and editor for PropertyItem.
//! Contains also logic to map editor to SessionModel.

class BA_CORE_API_ PropertyWidgetItem : public QObject
{
    Q_OBJECT
public:
    explicit PropertyWidgetItem(QWidget* parent = nullptr);
    ~PropertyWidgetItem();

    void setItemEditor(const SessionItem* item, QWidget* editor);
    void addToGrid(QGridLayout* gridLayout, int nrow);

    void updateItemRoles();

    const SessionItem* item();

private:
    void connectEditor(QWidget* editor);

    QLabel* m_label;
    QWidget* m_editor;
    QDataWidgetMapper* m_dataMapper;
    SessionModelDelegate* m_delegate;
    const SessionItem* m_item;
};

#endif // BORNAGAIN_GUI_COREGUI_VIEWS_PROPERTYEDITOR_PROPERTYWIDGETITEM_H
