// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/JobWidgets/JobListWidget.cpp
//! @brief     Implements class JobListWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/coregui/Views/JobWidgets/JobListWidget.h"
#include "GUI/coregui/Models/JobItem.h"
#include "GUI/coregui/Models/JobModel.h"
#include "GUI/coregui/Views/CommonWidgets/ItemSelectorWidget.h"
#include "GUI/coregui/Views/JobWidgets/JobListViewDelegate.h"
#include "GUI/coregui/utils/StyleUtils.h"
#include <QItemSelectionModel>
#include <QListView>
#include <QVBoxLayout>

JobListWidget::JobListWidget(QWidget* parent)
    : QWidget(parent), m_listViewDelegate(new JobListViewDelegate(this)),
      m_listView(new ItemSelectorWidget(this)), m_jobModel(nullptr)
{
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

    m_listView->listView()->setItemDelegate(m_listViewDelegate);
    m_listView->listView()->setSelectionMode(QAbstractItemView::ExtendedSelection);

    auto mainLayout = new QVBoxLayout;
    mainLayout->setMargin(0);
    mainLayout->setSpacing(0);

    auto vlayout = new QVBoxLayout;
    vlayout->setMargin(10);
    vlayout->setSpacing(10);

    vlayout->addWidget(m_listView);
    mainLayout->addLayout(vlayout);

    setLayout(mainLayout);

    connect(m_listView, &ItemSelectorWidget::contextMenuRequest, this,
            &JobListWidget::contextMenuRequest);

    connect(m_listView, &ItemSelectorWidget::selectionChanged, this,
            &JobListWidget::onItemSelectionChanged);
}

void JobListWidget::setModel(JobModel* model)
{
    ASSERT(model);
    if (model != m_jobModel) {
        m_jobModel = model;
        m_listView->setModel(model);

        connect(m_listViewDelegate, &JobListViewDelegate::cancelButtonClicked, m_jobModel,
                &JobModel::cancelJob, Qt::UniqueConnection);
    }
}

QItemSelectionModel* JobListWidget::selectionModel()
{
    return m_listView->selectionModel();
}

//! Returns currently selected JobItem

const JobItem* JobListWidget::currentJobItem() const
{
    QModelIndexList selected = m_listView->selectionModel()->selectedIndexes();
    return selected.size() == 1 ? m_jobModel->getJobItemForIndex(selected.at(0)) : nullptr;
}

QSize JobListWidget::sizeHint() const
{
    return QSize(StyleUtils::PropertyPanelWidth(), StyleUtils::PropertyPanelWidth() * 2);
}

QSize JobListWidget::minimumSizeHint() const
{
    return QSize(StyleUtils::PropertyPanelWidth(), StyleUtils::PropertyPanelWidth());
}

void JobListWidget::makeJobItemSelected(JobItem* jobItem)
{
    ASSERT(jobItem);
    QModelIndexList selected = m_listView->selectionModel()->selectedIndexes();

    // Already selected, but we still will emit the signal to notify widgets.
    // To handle the case, when the job was selected before it completed (and some stack widgets
    // were refusing to show the content for non-complete job).
    if (selected.size() == 1 && selected.at(0) == jobItem->index()) {
        emit selectionChanged(jobItem);
        return;
    }

    m_listView->selectionModel()->clearSelection();
    m_listView->selectionModel()->select(jobItem->index(), QItemSelectionModel::Select);
}

//! Recieves SeesionItem from ItemSelectorWidget and emits it further as JobItem.
//! Null item means the absence of selection.

void JobListWidget::onItemSelectionChanged(SessionItem* item)
{
    JobItem* jobItem(nullptr);
    if (item) {
        jobItem = dynamic_cast<JobItem*>(item);
        ASSERT(jobItem);
    }
    emit selectionChanged(jobItem);
}
