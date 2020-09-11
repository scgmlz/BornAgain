// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/JobModel.cpp
//! @brief     Implements class JobModel
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/coregui/Models/JobModel.h"
#include "GUI/coregui/Models/AxesItems.h"
#include "GUI/coregui/Models/FitSuiteItem.h"
#include "GUI/coregui/Models/GroupItem.h"
#include "GUI/coregui/Models/InstrumentItems.h"
#include "GUI/coregui/Models/IntensityDataItem.h"
#include "GUI/coregui/Models/JobItem.h"
#include "GUI/coregui/Models/JobItemUtils.h"
#include "GUI/coregui/Models/JobModelFunctions.h"
#include "GUI/coregui/Models/JobQueueData.h"
#include "GUI/coregui/Models/MultiLayerItem.h"
#include "GUI/coregui/Models/ParameterTreeItems.h"
#include "GUI/coregui/Models/ParameterTreeUtils.h"
#include "GUI/coregui/Models/RealDataItem.h"
#include "GUI/coregui/Models/SimulationOptionsItem.h"
#include "GUI/coregui/utils/GUIHelpers.h"

JobModel::JobModel(QObject* parent)
    : SessionModel(SessionXML::JobModelTag, parent), m_queue_data(nullptr)
{
    m_queue_data = new JobQueueData(this);
    connect(m_queue_data, SIGNAL(focusRequest(JobItem*)), this, SIGNAL(focusRequest(JobItem*)));
    connect(m_queue_data, SIGNAL(globalProgress(int)), this, SIGNAL(globalProgress(int)));
    setObjectName(SessionXML::JobModelTag);
}

JobModel::~JobModel()
{
    delete m_queue_data;
}

const JobItem* JobModel::getJobItemForIndex(const QModelIndex& index) const
{
    const JobItem* result = dynamic_cast<const JobItem*>(itemForIndex(index));
    ASSERT(result);
    return result;
}

JobItem* JobModel::getJobItemForIndex(const QModelIndex& index)
{
    JobItem* result = dynamic_cast<JobItem*>(itemForIndex(index));
    ASSERT(result);
    return result;
}

JobItem* JobModel::getJobItemForIdentifier(const QString& identifier)
{
    QModelIndex parentIndex;
    for (int i_row = 0; i_row < rowCount(parentIndex); ++i_row) {
        QModelIndex itemIndex = index(i_row, 0, parentIndex);
        JobItem* jobItem = getJobItemForIndex(itemIndex);
        if (jobItem->getIdentifier() == identifier)
            return jobItem;
    }
    return nullptr;
}

//! Main method to add a job
JobItem* JobModel::addJob(const MultiLayerItem* multiLayerItem,
                          const InstrumentItem* instrumentItem, const RealDataItem* realDataItem,
                          const SimulationOptionsItem* optionItem)
{
    ASSERT(multiLayerItem);
    ASSERT(instrumentItem);
    ASSERT(optionItem);

    JobItem* jobItem = dynamic_cast<JobItem*>(insertNewItem("JobItem"));
    jobItem->setItemName(generateJobName());
    jobItem->setIdentifier(GUIHelpers::createUuid());

    JobModelFunctions::setupJobItemSampleData(jobItem, multiLayerItem);
    JobModelFunctions::setupJobItemInstrument(jobItem, instrumentItem);

    // TODO: remove when specular instrument is ready for magnetization
    if (instrumentItem->modelType() == "SpecularInstrument")
        JobModelFunctions::muteMagnetizationData(jobItem);
    copyItem(optionItem, jobItem, JobItem::T_SIMULATION_OPTIONS);

    jobItem->getItem(JobItem::P_SAMPLE_NAME)->setValue(multiLayerItem->itemName());

    ParameterTreeUtils::createParameterTree(jobItem);

    JobModelFunctions::setupJobItemOutput(jobItem);

    if (realDataItem)
        JobModelFunctions::setupJobItemForFit(jobItem, realDataItem);

    return jobItem;
}

//! restore instrument and sample model from backup for given JobItem
void JobModel::restore(JobItem* jobItem)
{
    restoreItem(jobItem->getItem(JobItem::T_PARAMETER_TREE));
}

bool JobModel::hasUnfinishedJobs()
{
    bool result = m_queue_data->hasUnfinishedJobs();
    for (auto jobItem : topItems<JobItem>()) {
        if (jobItem->getStatus() == "Fitting")
            result = true;
    }

    return result;
}

void JobModel::clear()
{
    for (auto item : topItems())
        removeJob(item->index());

    SessionModel::clear();
}

QVector<SessionItem*> JobModel::nonXMLData() const
{
    QVector<SessionItem*> result;

    for (auto jobItem : topItems<JobItem>()) {
        if (auto intensityItem = jobItem->getItem(JobItem::T_OUTPUT))
            result.push_back(intensityItem);

        if (auto real_data = dynamic_cast<RealDataItem*>(jobItem->getItem(JobItem::T_REALDATA))) {
            if (auto data_item = real_data->dataItem())
                result.push_back(data_item);
            if (auto native_data = real_data->nativeData())
                result.push_back(native_data);
        }

        auto instrument =
            dynamic_cast<SpecularInstrumentItem*>(jobItem->getItem(JobItem::T_INSTRUMENT));
        if (instrument) {
            auto axis_group = instrument->beamItem()->inclinationAxisGroup();
            result.push_back(axis_group->getChildOfType("PointwiseAxis"));
        }
    }

    return result;
}

//! Link instruments to real data on project load.

void JobModel::link_instruments()
{
    for (int i = 0; i < rowCount(QModelIndex()); ++i) {
        JobItem* jobItem = getJobItemForIndex(index(i, 0, QModelIndex()));
        if (RealDataItem* refItem = jobItem->realDataItem())
            refItem->linkToInstrument(jobItem->instrumentItem(), false);
    }
}

void JobModel::onCancelAllJobs()
{
    m_queue_data->onCancelAllJobs();
}

void JobModel::runJob(const QModelIndex& index)
{
    m_queue_data->runJob(getJobItemForIndex(index));
}

void JobModel::cancelJob(const QModelIndex& index)
{
    m_queue_data->cancelJob(getJobItemForIndex(index)->getIdentifier());
}

void JobModel::removeJob(const QModelIndex& index)
{
    JobItem* jobItem = getJobItemForIndex(index);
    ASSERT(jobItem);
    m_queue_data->removeJob(jobItem->getIdentifier());

    emit aboutToDeleteJobItem(jobItem);
    removeRows(index.row(), 1, QModelIndex());
}

//! generates job name
QString JobModel::generateJobName()
{
    int glob_index = 0;
    QModelIndex parentIndex;
    for (int i_row = 0; i_row < rowCount(parentIndex); ++i_row) {
        QModelIndex itemIndex = index(i_row, 0, parentIndex);

        if (SessionItem* item = itemForIndex(itemIndex)) {
            if (item->modelType() == "JobItem") {
                QString jobName = item->itemName();
                if (jobName.startsWith("job")) {
                    int job_index = jobName.remove(0, 3).toInt();
                    if (job_index > glob_index)
                        glob_index = job_index;
                }
            }
        }
    }
    return QString("job") + QString::number(++glob_index);
}

void JobModel::restoreItem(SessionItem* item)
{
    if (ParameterItem* parameter = dynamic_cast<ParameterItem*>(item))
        parameter->restoreFromBackup();

    for (auto child : item->children())
        restoreItem(child);
}
