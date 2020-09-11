// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/SampleDesigner/SamplePropertyWidget.cpp
//! @brief     Implements class IntensityDataPropertyWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/coregui/Views/SampleDesigner/SamplePropertyWidget.h"
#include "GUI/coregui/Models/SessionItem.h"
#include "GUI/coregui/Views/PropertyEditor/ComponentEditor.h"
#include <QItemSelection>
#include <QModelIndexList>
#include <QSortFilterProxyModel>
#include <QVBoxLayout>

SamplePropertyWidget::SamplePropertyWidget(QItemSelectionModel* selection_model, QWidget* parent)
    : QWidget(parent), m_selection_model(nullptr),
      m_propertyEditor(new ComponentEditor(ComponentEditor::FullTree))
{
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    setWindowTitle(QLatin1String("Property Editor"));
    setObjectName(QLatin1String("SamplePropertyWidget"));

    setSelectionModel(selection_model);

    auto mainLayout = new QVBoxLayout;
    mainLayout->setMargin(0);
    mainLayout->setSpacing(0);
    mainLayout->addWidget(m_propertyEditor);

    setLayout(mainLayout);
}

QSize SamplePropertyWidget::sizeHint() const
{
    return QSize(230, 256);
}

QSize SamplePropertyWidget::minimumSizeHint() const
{
    return QSize(230, 64);
}

void SamplePropertyWidget::setSelectionModel(QItemSelectionModel* selection_model)
{
    if (selection_model == m_selection_model)
        return;

    if (m_selection_model) {
        disconnect(m_selection_model, &QItemSelectionModel::selectionChanged, this,
                   &SamplePropertyWidget::selectionChanged);
    }

    m_selection_model = selection_model;

    if (m_selection_model) {
        connect(m_selection_model, &QItemSelectionModel::selectionChanged, this,
                &SamplePropertyWidget::selectionChanged);
    }
}

// TODO Refactor this together with whole SampleView. Remove knowledge about proxy model.

void SamplePropertyWidget::selectionChanged(const QItemSelection& selected, const QItemSelection&)
{
    QModelIndexList indices = selected.indexes();

    if (indices.size()) {
        QModelIndex index = indices.back();

        if (auto proxy = dynamic_cast<QSortFilterProxyModel*>(
                const_cast<QAbstractItemModel*>(indices.front().model())))
            index = proxy->mapToSource(indices.back());

        SessionItem* item = static_cast<SessionItem*>(index.internalPointer());
        if (item)
            m_propertyEditor->setItem(item);

    } else {
        m_propertyEditor->setItem(nullptr);
    }
}
