// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/MaterialEditor/MaterialEditor.cpp
//! @brief     Implements class MaterialEditor
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/coregui/Views/MaterialEditor/MaterialEditor.h"
#include "GUI/coregui/Models/MaterialItem.h"
#include "GUI/coregui/Models/MaterialModel.h"
#include "GUI/coregui/Models/SessionDecorationModel.h"
#include "GUI/coregui/Views/MaterialEditor/ExternalProperty.h"
#include "GUI/coregui/Views/MaterialEditor/MaterialEditorToolBar.h"
#include "GUI/coregui/Views/PropertyEditor/ComponentEditor.h"
#include <QListView>
#include <QSplitter>
#include <QVBoxLayout>

MaterialEditor::MaterialEditor(MaterialModel* materialModel, QWidget* parent)
    : QWidget(parent), m_materialModel(materialModel),
      m_toolBar(new MaterialEditorToolBar(materialModel, this)), m_splitter(new QSplitter),
      m_listView(new QListView), m_componentEditor(new ComponentEditor), m_model_was_modified(false)
{
    setWindowTitle("MaterialEditorWidget");
    setMinimumSize(128, 128);
    resize(512, 400);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    QVBoxLayout* layout = new QVBoxLayout;
    layout->setContentsMargins(0, 0, 0, 0);

    m_splitter->addWidget(m_listView);
    m_splitter->addWidget(m_componentEditor);
    m_splitter->setCollapsible(0, false);
    m_splitter->setCollapsible(1, false);

    layout->addWidget(m_toolBar);
    layout->addWidget(m_splitter);

    setLayout(layout);

    init_views();
}

QItemSelectionModel* MaterialEditor::selectionModel()
{
    ASSERT(m_listView);
    return m_listView->selectionModel();
}

MaterialItem* MaterialEditor::selectedMaterial()
{
    auto selected = selectionModel()->currentIndex();
    return selected.isValid() ? m_materialModel->materialFromIndex(selected) : nullptr;
}

//! Sets selection corresponding to initial material property
void MaterialEditor::setInitialMaterialProperty(const ExternalProperty& matProperty)
{
    if (MaterialItem* mat = m_materialModel->materialFromIdentifier(matProperty.identifier())) {
        selectionModel()->clearSelection();
        selectionModel()->setCurrentIndex(m_materialModel->indexOfItem(mat),
                                          QItemSelectionModel::ClearAndSelect);
        selectionModel()->select(m_materialModel->indexOfItem(mat),
                                 QItemSelectionModel::ClearAndSelect);
    }
}

bool MaterialEditor::modelWasChanged() const
{
    return m_model_was_modified;
}

void MaterialEditor::onSelectionChanged(const QItemSelection& selected, const QItemSelection&)
{
    QModelIndexList indices = selected.indexes();

    if (indices.isEmpty()) {
        m_componentEditor->setItem(nullptr);
    } else {
        if (SessionItem* item = m_materialModel->itemForIndex(indices.front()))
            m_componentEditor->setItem(item);
    }
}

void MaterialEditor::onDataChanged(const QModelIndex&, const QModelIndex&, const QVector<int>&)
{
    m_model_was_modified = true;
}

void MaterialEditor::onRowsInserted(const QModelIndex&, int, int)
{
    m_model_was_modified = true;
}

void MaterialEditor::onRowsRemoved(const QModelIndex&, int, int)
{
    m_model_was_modified = true;
}

//! Context menu reimplemented to supress default menu
void MaterialEditor::contextMenuEvent(QContextMenuEvent* event)
{
    Q_UNUSED(event);
}

void MaterialEditor::init_views()
{
    connect(m_materialModel, &MaterialModel::dataChanged, this, &MaterialEditor::onDataChanged);
    connect(m_materialModel, &MaterialModel::rowsInserted, this, &MaterialEditor::onRowsInserted);
    connect(m_materialModel, &MaterialModel::rowsRemoved, this, &MaterialEditor::onRowsRemoved);

    m_listView->setContextMenuPolicy(Qt::CustomContextMenu);
    m_listView->setModel(new SessionDecorationModel(m_listView, m_materialModel));
    m_listView->setMovement(QListView::Static);
    m_listView->setMinimumWidth(50);
    m_listView->setMaximumWidth(220);
    m_listView->setSpacing(5);

    m_toolBar->setSelectionModel(selectionModel());

    connect(selectionModel(), &QItemSelectionModel::selectionChanged, this,
            &MaterialEditor::onSelectionChanged);

    // making first material selected
    if (!selectionModel()->hasSelection()) {
        QModelIndex itemIndex = m_materialModel->index(0, 0, QModelIndex());
        selectionModel()->select(itemIndex, QItemSelectionModel::ClearAndSelect);
    }

    connect(m_listView, &QListView::customContextMenuRequested, m_toolBar,
            &MaterialEditorToolBar::onCustomContextMenuRequested);
}
