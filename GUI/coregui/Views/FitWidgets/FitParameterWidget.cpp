// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/FitWidgets/FitParameterWidget.cpp
//! @brief     Implements class FitParameterWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/coregui/Views/FitWidgets/FitParameterWidget.h"
#include "GUI/coregui/Models/FilterPropertyProxy.h"
#include "GUI/coregui/Models/FitParameterHelper.h"
#include "GUI/coregui/Models/FitParameterItems.h"
#include "GUI/coregui/Models/FitParameterProxyModel.h"
#include "GUI/coregui/Models/FitSuiteItem.h"
#include "GUI/coregui/Models/JobItem.h"
#include "GUI/coregui/Models/JobModel.h"
#include "GUI/coregui/Models/ParameterTreeItems.h"
#include "GUI/coregui/Models/SessionModelDelegate.h"
#include "GUI/coregui/Views/InfoWidgets/OverlayLabelController.h"
#include "GUI/coregui/Views/JobWidgets/ParameterTuningWidget.h"
#include "GUI/coregui/mainwindow/mainwindow_constants.h"
#include "GUI/coregui/utils/CustomEventFilters.h"
#include <QAction>
#include <QMenu>
#include <QTreeView>
#include <QVBoxLayout>

FitParameterWidget::FitParameterWidget(QWidget* parent)
    : SessionItemWidget(parent), m_treeView(new QTreeView), m_tuningWidget(0),
      m_createFitParAction(0), m_removeFromFitParAction(0), m_removeFitParAction(0),
      m_fitParameterModel(0), m_delegate(new SessionModelDelegate(this)),
      m_keyboardFilter(new DeleteEventFilter(this)), m_infoLabel(new OverlayLabelController(this))
{
    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(m_treeView);
    layout->setMargin(0);
    layout->setSpacing(0);
    setLayout(layout);
    init_actions();

    m_treeView->setSelectionMode(QAbstractItemView::ExtendedSelection);
    m_treeView->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_treeView->setContextMenuPolicy(Qt::CustomContextMenu);
    m_treeView->setItemDelegate(m_delegate);
    m_treeView->setDragEnabled(true);
    m_treeView->setDragDropMode(QAbstractItemView::DragDrop);
    m_treeView->installEventFilter(m_keyboardFilter);
    m_treeView->setAlternatingRowColors(true);
    m_treeView->setStyleSheet("alternate-background-color: #EFF0F1;");

    connect(m_treeView, SIGNAL(customContextMenuRequested(const QPoint&)), this,
            SLOT(onFitParameterTreeContextMenu(const QPoint&)));

    m_infoLabel->setArea(m_treeView);
    m_infoLabel->setText("Drop parameter(s) to fit here");
}

//! Sets ParameterTuningWidget to be able to provide it with context menu and steer
//! it behaviour in the course of fit settings or fit runnig

void FitParameterWidget::setParameterTuningWidget(ParameterTuningWidget* tuningWidget)
{
    if (tuningWidget == m_tuningWidget) {
        return;

    } else {
        if (m_tuningWidget)
            disconnect(m_tuningWidget, SIGNAL(itemContextMenuRequest(QPoint)), this,
                       SLOT(onTuningWidgetContextMenu(QPoint)));

        m_tuningWidget = tuningWidget;
        if (!m_tuningWidget)
            return;

        connect(m_tuningWidget, SIGNAL(itemContextMenuRequest(QPoint)), this,
                SLOT(onTuningWidgetContextMenu(QPoint)), Qt::UniqueConnection);
        connect(m_tuningWidget, &QObject::destroyed, [this] { m_tuningWidget = nullptr; });
    }
}

// QSize FitParameterWidget::sizeHint() const
//{
//    return QSize(Constants::REALTIME_WIDGET_WIDTH_HINT, Constants::FIT_PARAMETER_WIDGET_HEIGHT);
//}

// QSize FitParameterWidget::minimumSizeHint() const
//{
//    return QSize(25, 25);
//}

//! Creates context menu for ParameterTuningWidget

void FitParameterWidget::onTuningWidgetContextMenu(const QPoint& point)
{
    QMenu menu;
    initTuningWidgetContextMenu(menu);
    menu.exec(point);
    setActionsEnabled(true);
}

//! Creates context menu for the tree with fit parameters

void FitParameterWidget::onFitParameterTreeContextMenu(const QPoint& point)
{
    QMenu menu;
    initFitParameterTreeContextMenu(menu);
    menu.exec(m_treeView->mapToGlobal(point + QPoint(2, 22)));
    setActionsEnabled(true);
}

void FitParameterWidget::onTuningWidgetSelectionChanged(const QItemSelection& selection)
{
    Q_UNUSED(selection);
}

//! Propagates selection form the tree with fit parameters to the tuning widget

void FitParameterWidget::onFitParametersSelectionChanged(const QItemSelection& selection)
{
    if (selection.indexes().isEmpty())
        return;

    for (auto index : selection.indexes()) {
        m_tuningWidget->selectionModel()->clearSelection();
        SessionItem* item = m_fitParameterModel->itemForIndex(index);
        if (item->parent()->modelType() == "FitParameterLink") {
            QString link = item->parent()->getItemValue(FitParameterLinkItem::P_LINK).toString();
            m_tuningWidget->makeSelected(
                FitParameterHelper::getParameterItem(jobItem()->fitParameterContainerItem(), link));
        }
    }
}

//! Creates fit parameters for all selected ParameterItem's in tuning widget

void FitParameterWidget::onCreateFitParAction()
{
    for (auto item : m_tuningWidget->getSelectedParameters()) {
        if (!FitParameterHelper::getFitParameterItem(jobItem()->fitParameterContainerItem(),
                                                     item)) {
            FitParameterHelper::createFitParameter(jobItem()->fitParameterContainerItem(), item);
        }
    }
}

//! All ParameterItem's selected in tuning widget will be removed from link section of
//! corresponding fitParameterItem.

void FitParameterWidget::onRemoveFromFitParAction()
{
    for (auto item : m_tuningWidget->getSelectedParameters()) {
        if (FitParameterHelper::getFitParameterItem(jobItem()->fitParameterContainerItem(), item)) {
            FitParameterHelper::removeFromFitParameters(jobItem()->fitParameterContainerItem(),
                                                        item);
        }
    }
}

//! All selected FitParameterItem's of FitParameterItemLink's will be removed

void FitParameterWidget::onRemoveFitParAction()
{
    FitParameterContainerItem* container = jobItem()->fitParameterContainerItem();

    // retrieve both, selected FitParameterItem and FitParameterItemLink
    QVector<FitParameterLinkItem*> linksToRemove = selectedFitParameterLinks();

    for (auto item : linksToRemove) {
        container->model()->removeRow(item->index().row(), item->index().parent());
    }

    QVector<FitParameterItem*> itemsToRemove = selectedFitParameters();
    //  By uncommenting line below, removing link from fit parameter will lead to fit parameter
    // removal too (if it doesn't have other links)
    //  QVector<FitParameterItem *> itemsToRemove = selectedFitParameters()+emptyFitParameters();

    for (auto item : itemsToRemove) {
        container->model()->removeRow(item->index().row(), item->index().parent());
    }
}

//! Add all selected parameters to fitParameter with given index

void FitParameterWidget::onAddToFitParAction(int ipar)
{
    QStringList fitParNames =
        FitParameterHelper::getFitParameterNames(jobItem()->fitParameterContainerItem());
    for (auto item : m_tuningWidget->getSelectedParameters()) {
        FitParameterHelper::addToFitParameter(jobItem()->fitParameterContainerItem(), item,
                                              fitParNames.at(ipar));
    }
}

void FitParameterWidget::onFitParameterModelChange()
{
    spanParameters();
    updateInfoLabel();
}

//! Context menu reimplemented to suppress the default one

void FitParameterWidget::contextMenuEvent(QContextMenuEvent* event)
{
    Q_UNUSED(event);
}

void FitParameterWidget::subscribeToItem()
{
    init_fit_model();
}

void FitParameterWidget::init_actions()
{
    m_createFitParAction = new QAction("Create fit parameter", this);
    connect(m_createFitParAction, SIGNAL(triggered()), this, SLOT(onCreateFitParAction()));

    m_removeFromFitParAction = new QAction("Remove from fit parameters", this);
    connect(m_removeFromFitParAction, SIGNAL(triggered()), this, SLOT(onRemoveFromFitParAction()));

    m_removeFitParAction = new QAction("Remove fit parameter", this);
    connect(m_removeFitParAction, SIGNAL(triggered()), this, SLOT(onRemoveFitParAction()));

    connect(m_keyboardFilter, SIGNAL(removeItem()), this, SLOT(onRemoveFitParAction()));
}

//! Fills context menu for ParameterTuningWidget with content.

void FitParameterWidget::initTuningWidgetContextMenu(QMenu& menu)
{
    if (jobItem()->getStatus() == "Fitting") {
        setActionsEnabled(false);
        return;
    }

    m_removeFromFitParAction->setEnabled(canRemoveFromFitParameters());
    m_createFitParAction->setEnabled(canCreateFitParameter());

    menu.addAction(m_createFitParAction);
    QMenu* addToFitParMenu = menu.addMenu("Add to existing fit parameter");
    addToFitParMenu->setEnabled(true);

    const bool allow_one_fit_parameter_to_have_more_than_one_link = true;
    if (allow_one_fit_parameter_to_have_more_than_one_link) {
        QStringList fitParNames =
            FitParameterHelper::getFitParameterNames(jobItem()->fitParameterContainerItem());
        if (fitParNames.isEmpty() || canCreateFitParameter() == false) {
            addToFitParMenu->setEnabled(false);
        }
        for (int i = 0; i < fitParNames.count(); ++i) {
            QAction* action =
                new QAction(QString("to ").append(fitParNames.at(i)), addToFitParMenu);
            connect(action, &QAction::triggered, [=] { onAddToFitParAction(i); });
            addToFitParMenu->addAction(action);
        }
    }
    menu.addSeparator();
    menu.addAction(m_removeFromFitParAction);
}

//! Fills context menu for FitParameterTree with content.

void FitParameterWidget::initFitParameterTreeContextMenu(QMenu& menu)
{
    if (jobItem()->getStatus() == "Fitting") {
        setActionsEnabled(false);
        return;
    }
    menu.addAction(m_removeFitParAction);
}

//! Initializes FitParameterModel and its tree.

void FitParameterWidget::init_fit_model()
{
    m_treeView->setModel(0);

    delete m_fitParameterModel;
    m_fitParameterModel = new FitParameterProxyModel(
        jobItem()->fitParameterContainerItem(), jobItem()->fitParameterContainerItem()->model());
    m_treeView->setModel(m_fitParameterModel);

    connect(m_fitParameterModel, SIGNAL(dataChanged(QModelIndex, QModelIndex, QVector<int>)), this,
            SLOT(onFitParameterModelChange()));
    connect(m_fitParameterModel, SIGNAL(modelReset()), this, SLOT(onFitParameterModelChange()));

    onFitParameterModelChange();
    connectFitParametersSelection(true);
}

//! Returns true if tuning widget contains selected ParameterItem's which can be used to create
//! a fit parameter (i.e. it is not linked with some fit parameter already).

bool FitParameterWidget::canCreateFitParameter()
{
    QVector<ParameterItem*> selected = m_tuningWidget->getSelectedParameters();
    for (auto item : selected) {
        if (FitParameterHelper::getFitParameterItem(jobItem()->fitParameterContainerItem(), item)
            == nullptr)
            return true;
    }
    return false;
}

//! Returns true if tuning widget contains selected ParameterItem's which can be removed from
//! fit parameters.

bool FitParameterWidget::canRemoveFromFitParameters()
{
    QVector<ParameterItem*> selected = m_tuningWidget->getSelectedParameters();
    for (auto item : selected) {
        if (FitParameterHelper::getFitParameterItem(jobItem()->fitParameterContainerItem(), item))
            return true;
    }
    return false;
}

//! Enables/disables all context menu actions.

void FitParameterWidget::setActionsEnabled(bool value)
{
    m_createFitParAction->setEnabled(value);
    m_removeFromFitParAction->setEnabled(value);
    m_removeFitParAction->setEnabled(value);
}

//! Returns list of FitParameterItem's currently selected in FitParameterItem tree

QVector<FitParameterItem*> FitParameterWidget::selectedFitParameters()
{
    QVector<FitParameterItem*> result;
    QModelIndexList indexes = m_treeView->selectionModel()->selectedIndexes();
    for (auto index : indexes) {
        if (SessionItem* item = m_fitParameterModel->itemForIndex(index)) {
            if (item->modelType() == "FitParameter") {
                FitParameterItem* fitParItem = dynamic_cast<FitParameterItem*>(item);
                ASSERT(fitParItem);
                result.push_back(fitParItem);
            }
        }
    }
    return result;
}

//! Returns list of FitParameterItem's which doesn't have any links attached.

QVector<FitParameterItem*> FitParameterWidget::emptyFitParameters()
{
    QVector<FitParameterItem*> result;
    for (auto fitParItem : jobItem()->fitParameterContainerItem()->fitParameterItems())
        if (fitParItem->getItems(FitParameterItem::T_LINK).empty())
            result.push_back(fitParItem);

    return result;
}

//! Returns links of FitParameterLink's item selected in FitParameterItem tree

QVector<FitParameterLinkItem*> FitParameterWidget::selectedFitParameterLinks()
{
    QVector<FitParameterLinkItem*> result;
    QModelIndexList indexes = m_treeView->selectionModel()->selectedIndexes();
    for (QModelIndex index : indexes) {
        if (SessionItem* item = m_fitParameterModel->itemForIndex(index)) {
            if (item->parent()->modelType() == "FitParameterLink") {
                FitParameterLinkItem* fitParItem =
                    dynamic_cast<FitParameterLinkItem*>(item->parent());
                ASSERT(fitParItem);
                result.push_back(fitParItem);
            }
        }
    }
    return result;
}

//! Makes first column in FitParameterItem's tree related to ParameterItem link occupy whole space.

void FitParameterWidget::spanParameters()
{
    m_treeView->expandAll();
    for (int i = 0; i < m_fitParameterModel->rowCount(QModelIndex()); i++) {
        QModelIndex parameter = m_fitParameterModel->index(i, 0, QModelIndex());
        if (!parameter.isValid())
            break;
        int childRowCount = m_fitParameterModel->rowCount(parameter);
        if (childRowCount > 0) {
            for (int j = 0; j < childRowCount; j++) {
                m_treeView->setFirstColumnSpanned(j, parameter, true);
            }
        }
    }
}

//! Places overlay label on top of tree view, if there is no fit parameters
void FitParameterWidget::updateInfoLabel()
{
    if (!jobItem())
        return;

    bool is_to_show_label = jobItem()->fitParameterContainerItem()->isEmpty();
    m_infoLabel->setShown(is_to_show_label);
}

void FitParameterWidget::connectTuningWidgetSelection(bool active)
{
    ASSERT(m_tuningWidget);

    if (active) {
        connect(m_tuningWidget->selectionModel(),
                SIGNAL(selectionChanged(QItemSelection, QItemSelection)), this,
                SLOT(onTuningWidgetSelectionChanged(QItemSelection)), Qt::UniqueConnection);
    } else {
        disconnect(m_tuningWidget->selectionModel(),
                   SIGNAL(selectionChanged(QItemSelection, QItemSelection)), this,
                   SLOT(onTuningWidgetSelectionChanged(QItemSelection)));
    }
}

void FitParameterWidget::connectFitParametersSelection(bool active)
{
    if (active) {
        connect(m_treeView->selectionModel(),
                SIGNAL(selectionChanged(QItemSelection, QItemSelection)), this,
                SLOT(onFitParametersSelectionChanged(QItemSelection)), Qt::UniqueConnection);
    } else {
        disconnect(m_treeView->selectionModel(),
                   SIGNAL(selectionChanged(QItemSelection, QItemSelection)), this,
                   SLOT(onFitParametersSelectionChanged(QItemSelection)));
    }
}

JobItem* FitParameterWidget::jobItem()
{
    return dynamic_cast<JobItem*>(currentItem());
}
