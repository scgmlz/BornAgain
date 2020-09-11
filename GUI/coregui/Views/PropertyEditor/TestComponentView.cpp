// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/PropertyEditor/TestComponentView.cpp
//! @brief     Defines class TestComponentView
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/coregui/Views/PropertyEditor/TestComponentView.h"
#include "Core/Multilayer/MultiLayer.h"
#include "Core/Scattering/ISample.h"
#include "Core/StandardSamples/SampleBuilderFactory.h"
#include "GUI/coregui/Models/GUIObjectBuilder.h"
#include "GUI/coregui/Models/MaterialDataItems.h"
#include "GUI/coregui/Models/MaterialItem.h"
#include "GUI/coregui/Models/MaterialModel.h"
#include "GUI/coregui/Models/SampleModel.h"
#include "GUI/coregui/Models/SessionModelDelegate.h"
#include "GUI/coregui/Views/MaterialEditor/MaterialItemUtils.h"
#include "GUI/coregui/Views/PropertyEditor/ComponentEditor.h"
#include "GUI/coregui/Views/PropertyEditor/ComponentFlatView.h"
#include "GUI/coregui/Views/PropertyEditor/ComponentTreeView.h"
#include "GUI/coregui/mainwindow/mainwindow.h"
#include "GUI/coregui/utils/StyleUtils.h"
#include "minisplitter.h"
#include <QBoxLayout>
#include <QDebug>
#include <QItemSelectionModel>
#include <QPushButton>
#include <QTreeView>
#include <limits>

TestComponentView::TestComponentView(MainWindow* mainWindow)
    : m_mainWindow(mainWindow), m_sampleModel(new SampleModel(this)),
      m_materialModel(new MaterialModel(this)), m_sourceTree(new QTreeView),
      m_componentTree(new ComponentEditor(ComponentEditor::FullTree)),
      m_componentFlat(new ComponentEditor(ComponentEditor::PlainWidget)),
      m_updateButton(new QPushButton("Update models")),
      m_addItemButton(new QPushButton("Add item")), m_expandButton(new QPushButton("Expand tree")),
      m_splitter(new Manhattan::MiniSplitter), m_delegate(new SessionModelDelegate(this)),
      m_isExpaned(false)
{
    auto buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(m_updateButton);
    buttonLayout->addWidget(m_addItemButton);
    buttonLayout->addWidget(m_expandButton);

    m_sourceTree->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
    m_sourceTree->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);

    m_splitter->addWidget(m_sourceTree);
    m_splitter->addWidget(componentTreePanel());
    m_splitter->addWidget(componentBoxPanel());

    auto layout = new QVBoxLayout();
    layout->setMargin(0);
    layout->setSpacing(0);
    layout->addLayout(buttonLayout);
    layout->addWidget(m_splitter);

    setLayout(layout);

    init_source();

    connect(m_updateButton, &QPushButton::clicked, this, &TestComponentView::onUpdateRequest);
    connect(m_addItemButton, &QPushButton::clicked, this, &TestComponentView::onAddItemRequest);
    connect(m_expandButton, &QPushButton::clicked, this, &TestComponentView::onExpandRequest);

    m_sourceTree->setModel(m_sampleModel);
    m_sourceTree->setItemDelegate(m_delegate);
    StyleUtils::setPropertyStyle(m_sourceTree);
    connect(m_sourceTree->selectionModel(), &QItemSelectionModel::selectionChanged, this,
            &TestComponentView::onSelectionChanged);
}

void TestComponentView::onUpdateRequest()
{
    //    m_componentTree->setModel(m_sourceModel);
}

void TestComponentView::onAddItemRequest()
{
    m_sampleModel->insertNewItem("Particle");
}

void TestComponentView::onExpandRequest()
{
    if (!m_isExpaned) {
        m_sourceTree->expandAll();
        m_sourceTree->resizeColumnToContents(0);
        m_sourceTree->resizeColumnToContents(1);
        //        m_componentTree->treeView()->expandAll();
        //        m_componentTree->treeView()->resizeColumnToContents(0);
        //        m_componentTree->treeView()->resizeColumnToContents(1);
    } else {
        m_sourceTree->collapseAll();
        //        m_componentTree->treeView()->collapseAll();
    }

    //    const auto imax = std::numeric_limits<int>::max();
    const int imax = 1;
    QList<int> sizes = {imax, imax, imax};
    m_splitter->setSizes(sizes);

    m_isExpaned = !m_isExpaned;
}

//! Inserts test items into source model.

void TestComponentView::init_source()
{
    SampleBuilderFactory factory;
    const std::unique_ptr<MultiLayer> sample(
        factory.createSample("CylindersWithSizeDistributionBuilder"));
    GUIObjectBuilder::populateSampleModel(m_sampleModel, m_materialModel, *sample);
    m_sampleModel->insertNewItem("Vector");
    m_sampleModel->insertNewItem("GISASBeam");

    // adding intensity data item
    m_sampleModel->insertNewItem("IntensityData");
}

void TestComponentView::onSelectionChanged(const QItemSelection& selected, const QItemSelection&)
{
    QModelIndexList indices = selected.indexes();

    if (indices.size()) {
        //        QModelIndex selectedIndex = indices.front();
        //        m_componentTree->setRootIndex(selectedIndex);
        //        m_componentTree->treeView()->expandAll();

        auto item = m_sampleModel->itemForIndex(indices.front());
        m_componentTree->setItem(item);
        m_componentFlat->setItem(item);
    }
}

QWidget* TestComponentView::componentTreePanel()
{
    Manhattan::MiniSplitter* result = new Manhattan::MiniSplitter(Qt::Vertical);
    result->addWidget(m_componentTree);

    m_componentTree->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
    return result;
}

QWidget* TestComponentView::componentBoxPanel()
{
    Manhattan::MiniSplitter* result = new Manhattan::MiniSplitter(Qt::Vertical);
    result->addWidget(m_componentFlat);

    m_componentFlat->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);

    return result;
}
