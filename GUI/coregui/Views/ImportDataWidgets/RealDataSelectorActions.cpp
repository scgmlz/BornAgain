// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/ImportDataWidgets/RealDataSelectorActions.cpp
//! @brief     Implements class RealDataSelectorActions
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/coregui/Views/ImportDataWidgets/RealDataSelectorActions.h"
#include "Core/Intensity/IntensityDataFunctions.h"
#include "Core/Intensity/OutputData.h"
#include "GUI/coregui/Models/IntensityDataItem.h"
#include "GUI/coregui/Models/MaskItems.h"
#include "GUI/coregui/Models/ProjectionItems.h"
#include "GUI/coregui/Models/RealDataItem.h"
#include "GUI/coregui/Models/RealDataModel.h"
#include "GUI/coregui/Views/ImportDataWidgets/ImportDataUtils.h"
#include "GUI/coregui/mainwindow/AppSvc.h"
#include "GUI/coregui/mainwindow/projectmanager.h"
#include "GUI/coregui/utils/GUIHelpers.h"
#include "GUI/coregui/utils/ImportDataInfo.h"
#include <QAction>
#include <QApplication>
#include <QFileDialog>
#include <QItemSelectionModel>
#include <QMenu>

namespace
{
bool openRotateWarningDialog(QWidget* parent)
{
    const QString title("Rotate data");

    const QString message("Rotation will break the link between the data and the instrument. "
                          "Detector masks or profiles, if they exist, will be removed.");

    return GUIHelpers::question(parent, title, message, "Do you wish to rotate the data?",
                                "Yes, please rotate", "No, cancel data rotation");
}

//! Returns true, if rotation will affect linked instrument or mask presence.

bool rotationAffectsSetup(IntensityDataItem& intensityItem)
{
    if (intensityItem.parent()->getItemValue(RealDataItem::P_INSTRUMENT_ID).toBool())
        return true;

    if (intensityItem.maskContainerItem() && intensityItem.maskContainerItem()->hasChildren())
        return true;

    if (intensityItem.projectionContainerItem()
        && intensityItem.projectionContainerItem()->hasChildren())
        return true;

    return false;
}

//! Resets linked instruments and masks.

void resetSetup(IntensityDataItem& intensityItem)
{

    auto data_parent = intensityItem.parent();
    if (data_parent->getItemValue(RealDataItem::P_INSTRUMENT_ID).toBool())
        data_parent->setItemValue(RealDataItem::P_INSTRUMENT_ID, QString());

    if (auto maskContainer = intensityItem.maskContainerItem())
        maskContainer->model()->removeRows(0, maskContainer->numberOfChildren(),
                                           maskContainer->index());

    if (auto projectionsContainer = intensityItem.projectionContainerItem())
        projectionsContainer->model()->removeRows(0, projectionsContainer->numberOfChildren(),
                                                  projectionsContainer->index());
}

} // namespace

RealDataSelectorActions::RealDataSelectorActions(QObject* parent)
    : QObject(parent), m_import2dDataAction(nullptr), m_import1dDataAction(nullptr),
      m_removeDataAction(nullptr), m_rotateDataAction(new QAction(this)), m_realDataModel(nullptr),
      m_selectionModel(nullptr)
{
    m_import2dDataAction = new QAction("Import 2D data", parent);
    m_import2dDataAction->setIcon(QIcon(":/images/import.svg"));
    m_import2dDataAction->setToolTip("Import 2D data");
    connect(m_import2dDataAction, &QAction::triggered, this,
            &RealDataSelectorActions::onImport2dDataAction);

    m_import1dDataAction = new QAction("Import 1D data", parent);
    m_import1dDataAction->setIcon(QIcon(":/images/import.svg"));
    m_import1dDataAction->setToolTip("Import 1D data");
    connect(m_import1dDataAction, &QAction::triggered, this,
            &RealDataSelectorActions::onImport1dDataAction);

    m_removeDataAction = new QAction("Remove this data", parent);
    m_removeDataAction->setIcon(QIcon(":/images/delete.svg"));
    m_removeDataAction->setToolTip("Remove selected data");
    connect(m_removeDataAction, &QAction::triggered, this,
            &RealDataSelectorActions::onRemoveDataAction);

    m_rotateDataAction->setText("Rotate this data");
    m_rotateDataAction->setIcon(QIcon(":/images/rotate-left.svg"));
    m_rotateDataAction->setToolTip("Rotate intensity data by 90 deg counterclockwise");
    connect(m_rotateDataAction, &QAction::triggered, this,
            &RealDataSelectorActions::onRotateDataRequest);
}

void RealDataSelectorActions::setRealDataModel(RealDataModel* model)
{
    m_realDataModel = model;
}

void RealDataSelectorActions::setSelectionModel(QItemSelectionModel* selectionModel)
{
    m_selectionModel = selectionModel;
}

void RealDataSelectorActions::importDataLoop(int ndim)
{
    ASSERT(m_realDataModel);
    ASSERT(m_selectionModel);
    QString filter_string_ba;
    if (ndim == 2) {
        filter_string_ba = "Intensity File (*.int *.gz *.tif *.tiff *.txt *.csv);;"
                           "Other (*.*)";
    } else {
        filter_string_ba = "";
    }
    QString dirname = AppSvc::projectManager()->userImportDir();
    QStringList fileNames =
        QFileDialog::getOpenFileNames(Q_NULLPTR, "Open Intensity Files", dirname, filter_string_ba);

    if (fileNames.isEmpty())
        return;

    QString newImportDir = GUIHelpers::fileDir(fileNames[0]);
    if (newImportDir != dirname)
        AppSvc::projectManager()->setImportDir(newImportDir);

    for (auto fileName : fileNames) {
        QFileInfo info(fileName);
        auto baseNameOfLoadedFile = info.baseName();

        if (ndim == 2) {
            std::unique_ptr<OutputData<double>> data = ImportDataUtils::Import2dData(fileName);
            if (data) {
                RealDataItem* realDataItem =
                    dynamic_cast<RealDataItem*>(m_realDataModel->insertNewItem("RealData"));
                realDataItem->setItemName(baseNameOfLoadedFile);
                realDataItem->setOutputData(data.release());
                m_selectionModel->clearSelection();
                m_selectionModel->select(realDataItem->index(), QItemSelectionModel::Select);
            }
        } else if (ndim == 1) {
            auto data = ImportDataUtils::Import1dData(fileName);
            if (data) {
                RealDataItem* realDataItem =
                    dynamic_cast<RealDataItem*>(m_realDataModel->insertNewItem("RealData"));
                realDataItem->setItemName(baseNameOfLoadedFile);
                realDataItem->setImportData(std::move(data));
                m_selectionModel->clearSelection();
                m_selectionModel->select(realDataItem->index(), QItemSelectionModel::Select);
            }
        }
    }
}

void RealDataSelectorActions::onImport2dDataAction()
{
    importDataLoop(2);
}

void RealDataSelectorActions::onImport1dDataAction()
{
    importDataLoop(1);
}

void RealDataSelectorActions::onRemoveDataAction()
{
    QModelIndex currentIndex = m_selectionModel->currentIndex();
    if (currentIndex.isValid())
        m_realDataModel->removeRows(currentIndex.row(), 1, QModelIndex());

    updateSelection();
}

void RealDataSelectorActions::onRotateDataRequest()
{
    QModelIndex currentIndex = m_selectionModel->currentIndex();
    if (!currentIndex.isValid())
        return;

    RealDataItem* dataItem =
        dynamic_cast<RealDataItem*>(m_realDataModel->itemForIndex(currentIndex));
    ASSERT(dataItem);
    auto intensityItem = dataItem->intensityDataItem();
    ASSERT(intensityItem);

    if (rotationAffectsSetup(*intensityItem)) {
        if (!openRotateWarningDialog(nullptr))
            return;

        m_selectionModel->select(currentIndex, QItemSelectionModel::Clear);
        resetSetup(*intensityItem);
    }

    QApplication::setOverrideCursor(Qt::WaitCursor);
    const auto input = intensityItem->getOutputData();
    intensityItem->setOutputData(
        IntensityDataFunctions::createRearrangedDataSet(*input, 1).release());
    intensityItem->setAxesRangeToData();

    m_selectionModel->select(currentIndex, QItemSelectionModel::Select);
    QApplication::restoreOverrideCursor();
}

void RealDataSelectorActions::onContextMenuRequest(const QPoint& point,
                                                   const QModelIndex& indexAtPoint)
{
    QMenu menu;
    menu.setToolTipsVisible(true);

    setAllActionsEnabled(indexAtPoint.isValid());

    m_import2dDataAction->setEnabled(true);
    m_import1dDataAction->setEnabled(true);

    menu.addAction(m_removeDataAction);
    menu.addAction(m_rotateDataAction);
    menu.addSeparator();
    menu.addAction(m_import2dDataAction);
    menu.addAction(m_import1dDataAction);
    menu.exec(point);
}

void RealDataSelectorActions::setAllActionsEnabled(bool value)
{
    m_import2dDataAction->setEnabled(value);
    m_import1dDataAction->setEnabled(value);
    m_rotateDataAction->setEnabled(value);
    m_removeDataAction->setEnabled(value);
}

void RealDataSelectorActions::updateSelection()
{
    if (!m_selectionModel->hasSelection()) {
        // select last item
        QModelIndex itemIndex =
            m_realDataModel->index(m_realDataModel->rowCount(QModelIndex()) - 1, 0, QModelIndex());
        m_selectionModel->select(itemIndex, QItemSelectionModel::ClearAndSelect);
    }
}
