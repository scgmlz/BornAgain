// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/PropertyEditor/TestComponentView.h
//! @brief     Defines class TestComponentView
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_VIEWS_PROPERTYEDITOR_TESTCOMPONENTVIEW_H
#define BORNAGAIN_GUI_COREGUI_VIEWS_PROPERTYEDITOR_TESTCOMPONENTVIEW_H

#include "Wrap/WinDllMacros.h"
#include <QWidget>

class MainWindow;
class QPushButton;
class QTreeView;
class SampleModel;
class SessionModelDelegate;
class QItemSelection;
class ComponentEditor;
class ComponentTreeView;
namespace Manhattan
{
class MiniSplitter;
}
class QBoxLayout;
class ComponentFlatView;
class MaterialModel;

//! View to tests QListView working with ComponentProxyModel.

class TestComponentView : public QWidget
{
    Q_OBJECT
public:
    TestComponentView(MainWindow* mainWindow = nullptr);

private slots:
    void onUpdateRequest();
    void onAddItemRequest();
    void onExpandRequest();

private:
    void init_source();
    void onSelectionChanged(const QItemSelection& selected, const QItemSelection&);
    QWidget* componentTreePanel();
    QWidget* componentBoxPanel();

    MainWindow* m_mainWindow;
    SampleModel* m_sampleModel;
    MaterialModel* m_materialModel;
    QTreeView* m_sourceTree;
    ComponentEditor* m_componentTree;
    ComponentEditor* m_componentFlat;
    QPushButton* m_updateButton;
    QPushButton* m_addItemButton;
    QPushButton* m_expandButton;
    Manhattan::MiniSplitter* m_splitter;
    SessionModelDelegate* m_delegate;
    bool m_isExpaned;
};

#endif // BORNAGAIN_GUI_COREGUI_VIEWS_PROPERTYEDITOR_TESTCOMPONENTVIEW_H
