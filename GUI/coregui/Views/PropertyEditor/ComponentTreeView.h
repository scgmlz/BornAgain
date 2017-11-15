// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/PropertyEditor/ComponentTreeView.h
//! @brief     Defines class ComponentTreeView
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef COMPONENTTREEVIEW_H
#define COMPONENTTREEVIEW_H

#include "WinDllMacros.h"
#include <QWidget>

class QTreeView;
class SessionModel;
class SessionModelDelegate;
class ComponentProxyModel;
class QModelIndex;

//! Component property tree for SessionItems.
//! Shows only PropertyItems and current items of GroupProperties.

class BA_CORE_API_ ComponentTreeView : public QWidget
{
    Q_OBJECT
public:
    ComponentTreeView(QWidget* parent = nullptr);

    void setModel(SessionModel* model);
    void setRootIndex(const QModelIndex& index);

    QTreeView* treeView();

private:
    QTreeView* m_tree;
    SessionModelDelegate* m_delegate;
    ComponentProxyModel* m_proxyModel;
};

#endif  //  COMPONENTTREEVIEW_H
