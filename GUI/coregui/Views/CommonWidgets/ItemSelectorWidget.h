// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/CommonWidgets/ItemSelectorWidget.h
//! @brief     Defines class ItemSelectorWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_VIEWS_COMMONWIDGETS_ITEMSELECTORWIDGET_H
#define BORNAGAIN_GUI_COREGUI_VIEWS_COMMONWIDGETS_ITEMSELECTORWIDGET_H

#include "Wrap/WinDllMacros.h"
#include <QItemSelectionModel>
#include <QWidget>
#include <memory>

class SessionModel;
class SessionItem;
class QItemSelection;
class QModelIndex;
class QAbstractItemDelegate;
class QListView;
class SessionDecorationModel;

//! The ItemSelectorWidget class holds QListView to show top level items of SessionModel.
//! Used in InstrumentView, ImportDataView, JobSelectorView to switch between items.

class BA_CORE_API_ ItemSelectorWidget : public QWidget
{
    Q_OBJECT

public:
    ItemSelectorWidget(QWidget* parent = 0);
    ~ItemSelectorWidget();

    QSize sizeHint() const;
    QSize minimumSizeHint() const;

    void setModel(SessionModel* model);
    void setItemDelegate(QAbstractItemDelegate* delegate);

    QItemSelectionModel* selectionModel();
    QListView* listView();

public slots:
    void select(const QModelIndex& index, QItemSelectionModel::SelectionFlags command);
    void updateSelection();
    void selectLast();

signals:
    void selectionChanged(SessionItem* item);
    void contextMenuRequest(const QPoint& point, const QModelIndex& index);

private slots:
    void onSelectionChanged(const QItemSelection& selected, const QItemSelection&);
    void onCustomContextMenuRequested(const QPoint& point);

protected:
    void connectModel();
    void disconnectModel();
    void showEvent(class QShowEvent*);

    QListView* m_listView;
    SessionModel* m_model;
    std::unique_ptr<SessionDecorationModel> m_decorationModel;
};

#endif // BORNAGAIN_GUI_COREGUI_VIEWS_COMMONWIDGETS_ITEMSELECTORWIDGET_H
