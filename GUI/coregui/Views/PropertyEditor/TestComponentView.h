// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/PropertyEditor/TestComponentView.h
//! @brief     Defines class TestComponentView
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef TESTCOMPONENTVIEW_H
#define TESTCOMPONENTVIEW_H

#include "WinDllMacros.h"
#include <QWidget>

class MainWindow;
class QPushButton;
class QTreeView;
class SampleModel;
class SessionModelDelegate;
class QItemSelection;
class ComponentTreeView;

//! View to tests QListView working with ComponentProxyModel.

class TestComponentView : public QWidget
{
    Q_OBJECT
public:
    TestComponentView(MainWindow *mainWindow = nullptr);

private slots:
    void onUpdateRequest();
    void onAddItemRequest();
    void onExpandRequest();

private:
    void init_source();
    void onSelectionChanged(const QItemSelection& selected, const QItemSelection&);

    MainWindow* m_mainWindow;
    SampleModel* m_sourceModel;
    QTreeView* m_sourceTree;
    ComponentTreeView* m_componentTree;
    QPushButton* m_updateButton;
    QPushButton* m_addItemButton;
    QPushButton* m_expandButton;
    SessionModelDelegate* m_delegate;
    bool m_isExpaned;
};

#endif // TESTCOMPONENTVIEW_H
