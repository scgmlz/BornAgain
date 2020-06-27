// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/FitWidgets/FitComparisonViewController.cpp
//! @brief     Implements classes DiffItemController, FitComparison1DViewController
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "FitComparisonViewController.h"
#include "AxesItems.h"
#include "Data1DViewItem.h"
#include "DataItem.h"
#include "DataPropertyContainer.h"
#include "IntensityDataFunctions.h"
#include "JobItem.h"
#include "PropertyRepeater.h"
#include "RealDataItem.h"
#include "SessionModel.h"

namespace
{
const double relative_diff_min_1d = 1e-05;
const double relative_diff_max_1d = 4.0;
} // namespace

FitComparison1DViewController::FitComparison1DViewController(QObject* parent)
    : QObject(parent),
      m_diff_item_controller(new DiffItemController(Constants::SpecularDataType, this)),
      m_diff_view_item(nullptr), m_appearanceRepeater(new PropertyRepeater(this)),
      m_xAxisRepeater(new PropertyRepeater(this))
{
}

Data1DViewItem* FitComparison1DViewController::diffItemView()
{
    return m_diff_view_item;
}

void FitComparison1DViewController::setItem(JobItem* job_item)
{
    assert(job_item);

    clear();
    m_diff_item_controller->setJobItem(job_item);
    createDiffViewItem(job_item);

    auto job_data_view = job_item->dataItemView();

    m_appearanceRepeater->addItem(job_data_view);
    m_appearanceRepeater->addItem(diffItemView());

    m_xAxisRepeater->addItem(job_data_view->xAxisItem());
    m_xAxisRepeater->addItem(diffItemView()->xAxisItem());

    m_diff_view_item->setXaxisTitle(job_data_view->getXaxisTitle());
    m_diff_view_item->setYaxisTitle("Relative difference");
    m_diff_view_item->setLowerY(relative_diff_min_1d);
    m_diff_view_item->setUpperY(relative_diff_max_1d);
}

void FitComparison1DViewController::updateDiffData()
{
    m_diff_item_controller->updateDiffData();
}

void FitComparison1DViewController::resetDiffView()
{
    if (!m_diff_view_item)
        return;
    m_diff_view_item->resetView();
    m_diff_view_item->setLowerY(relative_diff_min_1d);
    m_diff_view_item->setUpperY(relative_diff_max_1d);
}

void FitComparison1DViewController::clear()
{
    m_diff_item_controller->unsubscribe();
    m_appearanceRepeater->clear();
    m_xAxisRepeater->clear();
    if (m_diff_view_item)
        deleteDiffViewItem();
}

void FitComparison1DViewController::createDiffViewItem(JobItem* job_item)
{
    m_diff_view_item = dynamic_cast<Data1DViewItem*>(
        m_diff_item_controller->model()->insertNewItem(Constants::Data1DViewItemType));
    auto container = m_diff_view_item->model()->insertNewItem(Constants::DataPropertyContainerType,
                                                              m_diff_view_item->index(), -1,
                                                              Data1DViewItem::T_DATA_PROPERTIES);
    dynamic_cast<DataPropertyContainer*>(container)->addItem(m_diff_item_controller->diffItem());

    m_diff_view_item->setJobItem(job_item);
    auto job_data_view = job_item->dataItemView();
    auto units_value = job_data_view->getItemValue(Data1DViewItem::P_AXES_UNITS);
    m_diff_view_item->setItemValue(Data1DViewItem::P_AXES_UNITS, units_value);
}

void FitComparison1DViewController::deleteDiffViewItem()
{
    auto parent = m_diff_view_item->parent();
    auto old_view_item = parent->takeRow(parent->rowOfChild(m_diff_view_item));
    assert(old_view_item == m_diff_view_item);
    delete (old_view_item);
    m_diff_view_item = nullptr;
}

DiffItemController::DiffItemController(const QString& data_type, QObject* parent)
    : QObject(parent), m_current_item(nullptr),
      m_private_model(new SessionModel("TempIntensityDataModel", this)),
      m_diff_item(dynamic_cast<DataItem*>(m_private_model->insertNewItem(data_type)))
{
    assert(m_diff_item);
}

DiffItemController::~DiffItemController()
{
    unsubscribe();
}

void DiffItemController::setJobItem(JobItem* job_item)
{
    assert(job_item);
    if (m_current_item)
        unsubscribe();
    m_current_item = job_item;
    subscribe();
    updateDiffData();
}

void DiffItemController::updateDiffData()
{
    assert(m_current_item);

    auto sim_data = m_current_item->dataItem();
    auto real_data = m_current_item->realDataItem()->dataItem();
    assert(sim_data && real_data);

    if (!sim_data->getOutputData()) // job failed
        return;

    m_diff_item->setOutputData(IntensityDataFunctions::createRelativeDifferenceData(
                                   *sim_data->getOutputData(), *real_data->getOutputData())
                                   .release());
}

void DiffItemController::subscribe()
{
    if (!m_current_item) {
        assert(false);
        return;
    }

    // on simulation data change
    m_current_item->dataItem()->mapper()->setOnValueChange([this]() { updateDiffData(); }, this);
}

void DiffItemController::unsubscribe()
{
    m_diff_item->mapper()->unsubscribe(this);
    if (!m_current_item)
        return;
    m_current_item->dataItem()->mapper()->unsubscribe(this);
    m_current_item = nullptr;
}
