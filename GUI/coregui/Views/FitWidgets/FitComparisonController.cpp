// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/FitWidgets/FitComparisonController.cpp
//! @brief     Implements class FitComparisonController
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/coregui/Views/FitWidgets/FitComparisonController.h"
#include "Core/Instrument/IntensityDataFunctions.h"
#include "GUI/coregui/Models/AxesItems.h"
#include "GUI/coregui/Models/IntensityDataItem.h"
#include "GUI/coregui/Models/JobItem.h"
#include "GUI/coregui/Models/RealDataItem.h"
#include "GUI/coregui/Models/SessionModel.h"
#include "GUI/coregui/Models/SpecularDataItem.h"
#include "GUI/coregui/Views/IntensityDataWidgets/PropertyRepeater.h"

namespace
{
// different limits on relative difference plot are required
// to provide the best appearance
const double relative_diff_min_2d = 1e-05;
const double relative_diff_max_2d = 1.0;
} // namespace

class FitComparisonController2D::DiffItemController : public QObject
{
public:
    DiffItemController(const QString& data_type, QObject* parent);
    ~DiffItemController() override;
    void setItem(JobItem* job_item);
    void updateDiffData();
    DataItem* diffItem();
    void subscribe();
    void unsubscribe();

private:
    JobItem* m_current_item;
    SessionModel* m_tempIntensityDataModel;
    DataItem* m_diff_item;
};

using DiffItemController = FitComparisonController2D::DiffItemController;

FitComparisonController2D::FitComparisonController2D(QObject* parent)
    : QObject(parent), m_diff_item_controller(new DiffItemController("IntensityData", this)),
      m_appearanceRepeater(new PropertyRepeater(this)), m_xAxisRepeater(new PropertyRepeater(this)),
      m_yAxisRepeater(new PropertyRepeater(this)), m_zAxisRepeater(new PropertyRepeater(this))
{
}

IntensityDataItem* FitComparisonController2D::diffItem()
{
    ASSERT(dynamic_cast<IntensityDataItem*>(m_diff_item_controller->diffItem()));
    return dynamic_cast<IntensityDataItem*>(m_diff_item_controller->diffItem());
}

void FitComparisonController2D::setItem(JobItem* job_item)
{
    ASSERT(job_item);

    clear();
    m_diff_item_controller->setItem(job_item);

    auto sim_data_item = dynamic_cast<IntensityDataItem*>(job_item->dataItem());
    auto real_data_item = dynamic_cast<IntensityDataItem*>(job_item->realDataItem()->dataItem());

    double zmin = real_data_item->getLowerZ();
    double zmax = real_data_item->getUpperZ();
    sim_data_item->setLowerAndUpperZ(zmin, zmax);

    diffItem()->xAxisItem()->setItemValue(BasicAxisItem::P_TITLE, sim_data_item->getXaxisTitle());
    diffItem()->yAxisItem()->setItemValue(BasicAxisItem::P_TITLE, sim_data_item->getYaxisTitle());
    diffItem()->setLowerAndUpperZ(relative_diff_min_2d, relative_diff_max_2d);
    diffItem()->setAxesRangeToData();

    m_appearanceRepeater->addItem(real_data_item);
    m_appearanceRepeater->addItem(sim_data_item);
    m_appearanceRepeater->addItem(diffItem());

    m_xAxisRepeater->addItem(real_data_item->xAxisItem());
    m_xAxisRepeater->addItem(sim_data_item->xAxisItem());
    m_xAxisRepeater->addItem(diffItem()->xAxisItem());

    m_yAxisRepeater->addItem(real_data_item->yAxisItem());
    m_yAxisRepeater->addItem(sim_data_item->yAxisItem());
    m_yAxisRepeater->addItem(diffItem()->yAxisItem());

    m_zAxisRepeater->addItem(real_data_item->zAxisItem());
    m_zAxisRepeater->addItem(sim_data_item->zAxisItem());
}

void FitComparisonController2D::updateDiffData()
{
    m_diff_item_controller->updateDiffData();
}

void FitComparisonController2D::resetDiffItem()
{
    diffItem()->resetView();
    diffItem()->setLowerAndUpperZ(relative_diff_min_2d, relative_diff_max_2d);
}

void FitComparisonController2D::clear()
{
    m_diff_item_controller->unsubscribe();

    m_appearanceRepeater->clear();
    m_xAxisRepeater->clear();
    m_yAxisRepeater->clear();
    m_zAxisRepeater->clear();
}

DiffItemController::DiffItemController(const QString& data_type, QObject* parent)
    : QObject(parent), m_current_item(nullptr),
      m_tempIntensityDataModel(new SessionModel("TempIntensityDataModel", this)),
      m_diff_item(dynamic_cast<DataItem*>(m_tempIntensityDataModel->insertNewItem(data_type)))
{
    ASSERT(m_diff_item);
}

DiffItemController::~DiffItemController()
{
    unsubscribe();
}

void DiffItemController::setItem(JobItem* job_item)
{
    ASSERT(job_item);
    if (m_current_item)
        unsubscribe();
    m_current_item = job_item;
    subscribe();
    updateDiffData();
}

void DiffItemController::updateDiffData()
{
    ASSERT(m_current_item);

    auto sim_data = m_current_item->dataItem();
    auto real_data = m_current_item->realDataItem()->dataItem();
    ASSERT(sim_data && real_data);

    if (!sim_data->getOutputData()) // job failed
        return;

    m_diff_item->setOutputData(IntensityDataFunctions::createRelativeDifferenceData(
                                   *sim_data->getOutputData(), *real_data->getOutputData())
                                   .release());
}

DataItem* DiffItemController::diffItem()
{
    return m_diff_item;
}

void DiffItemController::subscribe()
{
    if (!m_current_item) {
        ASSERT(false);
        return;
    }

    // on simulation data change
    m_current_item->dataItem()->mapper()->setOnValueChange([this]() { updateDiffData(); }, this);

    // on diff item units change
    m_diff_item->mapper()->setOnPropertyChange(
        [this](const QString& name) {
            if (name == DataItem::P_AXES_UNITS)
                m_diff_item->updateAxesUnits(m_current_item->instrumentItem());
        },
        this);
}

void DiffItemController::unsubscribe()
{
    if (!m_current_item)
        return;
    m_current_item->dataItem()->mapper()->unsubscribe(this);
    m_diff_item->mapper()->unsubscribe(this);
    m_current_item = nullptr;
}
