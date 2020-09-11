// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/JobWidgets/ParameterTuningWidget.cpp
//! @brief     Implements class ParameterTuningWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/coregui/Views/JobWidgets/ParameterTuningWidget.h"
#include "GUI/coregui/Models/IntensityDataItem.h"
#include "GUI/coregui/Models/JobItem.h"
#include "GUI/coregui/Models/JobModel.h"
#include "GUI/coregui/Models/ParameterTreeItems.h"
#include "GUI/coregui/Models/ParameterTuningModel.h"
#include "GUI/coregui/Views/InfoWidgets/WarningSign.h"
#include "GUI/coregui/Views/JobWidgets/JobRealTimeToolBar.h"
#include "GUI/coregui/Views/JobWidgets/ParameterTuningDelegate.h"
#include "GUI/coregui/Views/JobWidgets/SliderSettingsWidget.h"
#include "GUI/coregui/utils/GUIHelpers.h"
#include <QTreeView>
#include <QVBoxLayout>

ParameterTuningWidget::ParameterTuningWidget(QWidget* parent)
    : SessionItemWidget(parent), m_toolBar(new JobRealTimeToolBar(this)), m_jobModel(nullptr),
      m_parameterTuningModel(nullptr), m_sliderSettingsWidget(new SliderSettingsWidget(this)),
      m_treeView(new QTreeView), m_delegate(new ParameterTuningDelegate(this)),
      m_warningSign(new WarningSign(m_treeView))
{
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    m_treeView->setItemDelegate(m_delegate);
    m_treeView->setContextMenuPolicy(Qt::CustomContextMenu);
    m_treeView->setDragDropMode(QAbstractItemView::NoDragDrop);
    m_treeView->setAttribute(Qt::WA_MacShowFocusRect, false);

    auto mainLayout = new QVBoxLayout;
    mainLayout->setMargin(0);
    mainLayout->setSpacing(0);
    mainLayout->addWidget(m_toolBar);
    mainLayout->addWidget(m_sliderSettingsWidget);
    mainLayout->addWidget(m_treeView);
    setLayout(mainLayout);

    connect(m_sliderSettingsWidget, &SliderSettingsWidget::sliderRangeFactorChanged, this,
            &ParameterTuningWidget::onSliderValueChanged);
    connect(m_sliderSettingsWidget, &SliderSettingsWidget::lockzChanged, this,
            &ParameterTuningWidget::onLockZValueChanged);
    connect(m_delegate, &ParameterTuningDelegate::currentLinkChanged, this,
            &ParameterTuningWidget::onCurrentLinkChanged);
    connect(m_treeView, &QTreeView::customContextMenuRequested, this,
            &ParameterTuningWidget::onCustomContextMenuRequested);
    connect(m_toolBar, &JobRealTimeToolBar::resetParameters, this,
            &ParameterTuningWidget::restoreModelsOfCurrentJobItem);
}

QItemSelectionModel* ParameterTuningWidget::selectionModel()
{
    ASSERT(m_treeView);
    return m_treeView->selectionModel();
}

//! Returns list of ParameterItem's currently selected in parameter tree

QVector<ParameterItem*> ParameterTuningWidget::getSelectedParameters()
{
    QVector<ParameterItem*> result;
    QModelIndexList proxyIndexes = selectionModel()->selectedIndexes();
    for (auto proxyIndex : proxyIndexes) {
        if (ParameterItem* parItem = m_parameterTuningModel->getParameterItem(proxyIndex))
            result.push_back(parItem);
    }
    return result;
}

void ParameterTuningWidget::onCurrentLinkChanged(SessionItem* item)
{
    ASSERT(jobItem());

    if (jobItem()->isRunning())
        return;

    if (item) {
        // link.updateItem(); // FIXME circular dependency if uncomment
        m_jobModel->runJob(jobItem()->index());
    }
}

void ParameterTuningWidget::onSliderValueChanged(double value)
{
    m_delegate->setSliderRangeFactor(value);
}

void ParameterTuningWidget::onLockZValueChanged(bool value)
{
    if (!jobItem())
        return;
    if (IntensityDataItem* intensityDataItem = jobItem()->intensityDataItem())
        intensityDataItem->setZAxisLocked(value);
}

void ParameterTuningWidget::updateParameterModel()
{
    ASSERT(m_jobModel);

    if (!jobItem())
        return;

    if (!jobItem()->multiLayerItem() || !jobItem()->instrumentItem())
        throw GUIHelpers::Error("ModelTuningWidget::updateParameterModel() -> Error."
                                "JobItem doesn't have sample or instrument model.");

    delete m_parameterTuningModel;
    m_parameterTuningModel = new ParameterTuningModel(this);
    m_parameterTuningModel->setSourceModel(m_jobModel);

    m_treeView->setModel(m_parameterTuningModel);
    m_treeView->setRootIndex(
        m_parameterTuningModel->mapFromSource(jobItem()->parameterContainerItem()->index()));
    if (m_treeView->columnWidth(0) < 170)
        m_treeView->setColumnWidth(0, 170);
    m_treeView->expandAll();
}

void ParameterTuningWidget::onCustomContextMenuRequested(const QPoint& point)
{
    emit itemContextMenuRequest(m_treeView->mapToGlobal(point + QPoint(2, 22)));
}

void ParameterTuningWidget::restoreModelsOfCurrentJobItem()
{
    ASSERT(m_jobModel);
    ASSERT(jobItem());

    if (jobItem()->isRunning())
        return;

    closeActiveEditors();

    m_jobModel->restore(jobItem());
    m_jobModel->runJob(jobItem()->index());
}

void ParameterTuningWidget::makeSelected(ParameterItem* item)
{
    QModelIndex proxyIndex = m_parameterTuningModel->mapFromSource(item->index());
    if (proxyIndex.isValid())
        selectionModel()->select(proxyIndex, QItemSelectionModel::Select);
}

void ParameterTuningWidget::contextMenuEvent(QContextMenuEvent*)
{
    // reimplemented to suppress context menu from QMainWindow
}

void ParameterTuningWidget::subscribeToItem()
{
    m_jobModel = dynamic_cast<JobModel*>(jobItem()->model());

    updateParameterModel();
    updateDragAndDropSettings();

    jobItem()->mapper()->setOnPropertyChange(
        [this](const QString& name) { onPropertyChanged(name); }, this);

    onPropertyChanged(JobItem::P_STATUS);
}

void ParameterTuningWidget::onPropertyChanged(const QString& property_name)
{
    if (property_name == JobItem::P_STATUS) {
        m_warningSign->clear();

        if (jobItem()->isFailed()) {
            QString message;
            message.append("Current parameter values cause simulation failure.\n\n");
            message.append(jobItem()->getComments());
            m_warningSign->setWarningMessage(message);
        }

        updateDragAndDropSettings();
    }
}

JobItem* ParameterTuningWidget::jobItem()
{
    return dynamic_cast<JobItem*>(currentItem());
}

//! Disable drag-and-drop abilities, if job is in fit running state.

void ParameterTuningWidget::updateDragAndDropSettings()
{
    ASSERT(jobItem());
    if (jobItem()->getStatus() == "Fitting") {
        setTuningDelegateEnabled(false);
        m_treeView->setDragDropMode(QAbstractItemView::NoDragDrop);
    } else {
        setTuningDelegateEnabled(true);
        if (jobItem()->isValidForFitting())
            m_treeView->setDragDropMode(QAbstractItemView::DragOnly);
    }
}

//! Sets delegate to enabled/disabled state.
//! In 'disabled' state the delegate is in ReadOnlyMode, if it was containing already some
//! editing widget, it will be forced to close.
void ParameterTuningWidget::setTuningDelegateEnabled(bool enabled)
{
    if (enabled) {
        m_delegate->setReadOnly(false);
    } else {
        m_delegate->setReadOnly(true);
        closeActiveEditors();
    }
}

void ParameterTuningWidget::closeActiveEditors()
{
    QModelIndex index = m_treeView->currentIndex();
    QWidget* editor = m_treeView->indexWidget(index);
    if (editor) {
        // m_delegate->commitData(editor);
        m_delegate->closeEditor(editor, QAbstractItemDelegate::NoHint);
    }
    m_treeView->selectionModel()->clearSelection();
}
