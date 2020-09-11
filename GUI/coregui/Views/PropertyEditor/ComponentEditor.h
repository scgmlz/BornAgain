// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/PropertyEditor/ComponentEditor.h
//! @brief     Defines ComponentEditor class
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_VIEWS_PROPERTYEDITOR_COMPONENTEDITOR_H
#define BORNAGAIN_GUI_COREGUI_VIEWS_PROPERTYEDITOR_COMPONENTEDITOR_H

#include "Wrap/WinDllMacros.h"
#include <QWidget>

class ComponentView;
class SessionItem;
class QBoxLayout;

//! Component editor for SessionItem. Can have various appearance depending
//! on EditorFlags

class BA_CORE_API_ ComponentEditor : public QWidget
{
    Q_OBJECT
public:
    enum EditorFlags {
        Tree = 0x1000,
        Widget = 0x2000,

        PlainLayout = 0x0010, // editor embedded in standard box layout
        GroupLayout = 0x0020, // editor embedded in QGroupBox
        InfoLayout = 0x0040,  // editor embedded in GroupInfoBox

        T_Header = 0x0100,     // to show QTreeView header (Tree mode only)
        T_Root = 0x0200,       // to show root item  (Tree mode only)
        W_NoChildren = 0x0400, // show no children (Widget mode only)

        FullTree = Tree | PlainLayout | T_Header | T_Root,
        HeaderTree = Tree | PlainLayout | T_Header,
        MiniTree = Tree | PlainLayout,
        PlainWidget = Widget | PlainLayout,
        GroupWidget = Widget | GroupLayout,
        InfoWidget = Widget | InfoLayout,
    };
    Q_DECLARE_FLAGS(EditorType, EditorFlags)

    ComponentEditor(EditorType editorType = HeaderTree, const QString& title = "");

    void setItem(SessionItem* item);
    void clearEditor();
    void addItem(SessionItem* item);

signals:
    void dialogRequest(SessionItem* item, const QString& names);

private slots:
    void onDialogRequest();

private:
    ComponentView* createComponentView();

    EditorType m_type;
    ComponentView* m_componentView;
    SessionItem* m_item;
    QString m_title;
};

Q_DECLARE_OPERATORS_FOR_FLAGS(ComponentEditor::EditorType)

#endif // BORNAGAIN_GUI_COREGUI_VIEWS_PROPERTYEDITOR_COMPONENTEDITOR_H
