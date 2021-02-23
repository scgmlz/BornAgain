//  ************************************************************************************************
//
//  BornAgain: simulate and fit reflection and scattering
//
//! @file      GUI/coregui/Models/JobModelFunctions.cpp
//! @brief     Implements auxiliary functions in JobModelFunctions namespace.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "GUI/coregui/Models/JobModelFunctions.h"
#include "Device/Detector/IDetector2D.h"
#include "Device/Instrument/Instrument.h"
#include "GUI/coregui/Models/Data1DViewItem.h"
#include "GUI/coregui/Models/DataPropertyContainer.h"
#include "GUI/coregui/Models/DepthProbeInstrumentItem.h"
#include "GUI/coregui/Models/DetectorItems.h"
#include "GUI/coregui/Models/DomainObjectBuilder.h"
#include "GUI/coregui/Models/FitParameterItems.h"
#include "GUI/coregui/Models/FitSuiteItem.h"
#include "GUI/coregui/Models/GroupItem.h"
#include "GUI/coregui/Models/InstrumentItems.h"
#include "GUI/coregui/Models/IntensityDataItem.h"
#include "GUI/coregui/Models/ItemFileNameUtils.h"
#include "GUI/coregui/Models/JobItem.h"
#include "GUI/coregui/Models/JobItemUtils.h"
#include "GUI/coregui/Models/JobModel.h"
#include "GUI/coregui/Models/MaskItems.h"
#include "GUI/coregui/Models/MaterialItemContainer.h"
#include "GUI/coregui/Models/MinimizerItem.h"
#include "GUI/coregui/Models/MultiLayerItem.h"
#include "GUI/coregui/Models/PointwiseAxisItem.h"
#include "GUI/coregui/Models/RealDataItem.h"
#include "GUI/coregui/Models/SpecularDataItem.h"
#include "GUI/coregui/Views/MaskWidgets/MaskUnitsConverter.h"
#include "GUI/coregui/Views/MaterialEditor/MaterialItemUtils.h"
#include "GUI/coregui/utils/GUIHelpers.h"
#include <map>

namespace {
//! Links RealDataItem to the JobItem's instrument.
// (re-)Linking is necessary because of following reason
// 1) Copying of RealDataItem from RealDataModel on board of JobItem requires relink to the copied
//    insturment
// 2) During relink all masks (if exists) will be converted to the default units of current detector
void processInstrumentLink(JobItem* jobItem);

//! Copies masks and ROI from RealDataItem on board of instrument.
void copyMasksToInstrument(JobItem* jobItem);

//! Crops RealDataItem to the region of interest.
void cropRealData(JobItem* jobItem);

//! Creates necessary fit containers for jobItem intended for fitting.
void createFitContainers(JobItem* jobItem);

PointwiseAxisItem* getPointwiseAxisItem(const SpecularInstrumentItem* instrument);
} // namespace

void JobModelFunctions::initDataView(JobItem* job_item)
{
    ASSERT(job_item && job_item->isValidForFitting());
    ASSERT(job_item->instrumentItem() && job_item->instrumentItem()->is<SpecularInstrumentItem>());
    ASSERT(!job_item->getItem(JobItem::T_DATAVIEW));

    SessionModel* model = job_item->model();
    auto view_item = model->insertItem<Data1DViewItem>(job_item, -1, JobItem::T_DATAVIEW);

    auto property_container =
        model->insertItem<DataPropertyContainer>(view_item, -1, Data1DViewItem::T_DATA_PROPERTIES);

    property_container->addItem(job_item->realDataItem()->dataItem());
    property_container->addItem(job_item->dataItem());

    // also triggers Data1DViewItem::setAxesRangeToData and DataViewUtils::updateAxesTitle by
    // setting new value of P_AXES_UNITS.
    auto converter = DomainObjectBuilder::createUnitConverter(job_item->instrumentItem());
    view_item->setItemValue(Data1DViewItem::P_AXES_UNITS,
                            JobItemUtils::availableUnits(*converter).variant());
}

void JobModelFunctions::setupJobItemSampleData(JobItem* jobItem, const MultiLayerItem* sampleItem)
{
    auto model = jobItem->model();
    auto multilayer = model->copyItem(sampleItem, jobItem, JobItem::T_SAMPLE);
    multilayer->setItemName("MultiLayer");

    // copying materials
    auto container = jobItem->model()->insertItem<MaterialItemContainer>(
        jobItem, -1, JobItem::T_MATERIAL_CONTAINER);

    std::map<MaterialItem*, QString> materials;
    for (auto property_item : multilayer->materialPropertyItems()) {
        auto material_property = property_item->value().value<ExternalProperty>();
        auto material = MaterialItemUtils::findMaterial(material_property);

        auto iter = materials.find(material);
        if (iter == materials.end()) {
            auto material_copy = container->insertCopy(material);
            materials.insert({material, material_copy->identifier()});
            material_property.setIdentifier(material_copy->identifier());
        } else
            material_property.setIdentifier(iter->second);
        property_item->setValue(material_property.variant());
    }
}

void JobModelFunctions::setupJobItemInstrument(JobItem* jobItem, const InstrumentItem* from)
{
    auto model = jobItem->model();
    auto copiedInstrument = model->copyItem(from, jobItem, JobItem::T_INSTRUMENT);
    copiedInstrument->setItemName(from->modelType());
    copiedInstrument->setId(GUIHelpers::createUuid());
    jobItem->getItem(JobItem::P_INSTRUMENT_NAME)->setValue(from->itemName());

    auto spec_to = dynamic_cast<SpecularInstrumentItem*>(copiedInstrument);
    if (!spec_to)
        return;

    // updating filename
    const auto filename = ItemFileNameUtils::instrumentDataFileName(*spec_to);
    spec_to->beamItem()->updateFileName(filename);

    // copying axis data
    auto spec_from = static_cast<const SpecularInstrumentItem*>(from);
    auto axis_origin = getPointwiseAxisItem(spec_from);
    const QString current_axis_type = spec_from->beamItem()->inclinationAxisGroup()->currentType();
    if (current_axis_type == "PointwiseAxis")
        spec_to->beamItem()->updateToData(*axis_origin->axis(), axis_origin->getUnitsLabel());
    else if (axis_origin->containsNonXMLData())
        getPointwiseAxisItem(spec_to)->init(*axis_origin->axis(), axis_origin->getUnitsLabel());
}

//! Setup items intended for storing results of the job.

void JobModelFunctions::setupJobItemOutput(JobItem* jobItem)
{
    const bool isSpecularInstrument = jobItem->instrumentItem()->is<SpecularInstrumentItem>();
    const bool isIntensityInstrument = jobItem->instrumentItem()->is<GISASInstrumentItem>()
                                       || jobItem->instrumentItem()->is<OffSpecularInstrumentItem>()
                                       || jobItem->instrumentItem()->is<DepthProbeInstrumentItem>();

    ASSERT(isSpecularInstrument || isIntensityInstrument);

    if (isSpecularInstrument)
        jobItem->model()->insertItem<SpecularDataItem>(jobItem, -1, JobItem::T_OUTPUT);
    else if (isIntensityInstrument)
        jobItem->model()->insertItem<IntensityDataItem>(jobItem, -1, JobItem::T_OUTPUT);
    else
        throw GUIHelpers::Error("JobModelFunctions::setupJobItemOutput() -> Error. "
                                "Unsupported instrument type");
}

//! Setups JobItem for fit.

void JobModelFunctions::setupJobItemForFit(JobItem* jobItem, const RealDataItem* realDataItem)
{
    if (!jobItem->instrumentItem())
        throw GUIHelpers::Error("JobModelFunctions::processInstrumentLink() -> Error. "
                                "No instrument.");

    copyRealDataItem(jobItem, realDataItem);
    processInstrumentLink(jobItem);
    copyMasksToInstrument(jobItem);

    // TODO: remove if when other simulation types are ready for roi & masks
    if (jobItem->instrumentItem()->is<GISASInstrumentItem>())
        cropRealData(jobItem);
    if (jobItem->instrumentItem()->is<SpecularInstrumentItem>())
        initDataView(jobItem);

    createFitContainers(jobItem);
}

void JobModelFunctions::muteMagnetizationData(JobItem* jobItem)
{
    auto container =
        static_cast<MaterialItemContainer*>(jobItem->getItem(JobItem::T_MATERIAL_CONTAINER));
    for (auto item : container->getItems(MaterialItemContainer::T_MATERIALS))
        item->getItem(MaterialItem::P_MAGNETIZATION)->setVisible(false);

    auto sample = static_cast<MultiLayerItem*>(jobItem->getItem(JobItem::T_SAMPLE));
    sample->getItem(MultiLayerItem::P_EXTERNAL_FIELD)->setVisible(false);
}

void JobModelFunctions::copyRealDataItem(JobItem* jobItem, const RealDataItem* realDataItem)
{
    if (!realDataItem)
        return;

    SessionModel* model = jobItem->model();

    RealDataItem* realDataItemCopy = model->copyItem(realDataItem, jobItem, JobItem::T_REALDATA);
    ASSERT(realDataItemCopy);

    realDataItemCopy->dataItem()->setOutputData(realDataItem->dataItem()->getOutputData()->clone());

    // adapting the name to job name
    realDataItemCopy->dataItem()->setFileName(ItemFileNameUtils::jobReferenceFileName(*jobItem));

    // #baimport ++ copy members of realDataItem

    if (!realDataItem->nativeData())
        return;

    realDataItemCopy->setNativeOutputData(realDataItem->nativeOutputData()->clone());
    realDataItemCopy->nativeData()->setFileName(ItemFileNameUtils::jobNativeDataFileName(*jobItem));
}

const JobItem* JobModelFunctions::findJobItem(const SessionItem* item)
{
    while (item && item->modelType() != "JobItem")
        item = item->parent();
    return static_cast<const JobItem*>(item);
}

namespace {
void processInstrumentLink(JobItem* jobItem)
{
    RealDataItem* realData = jobItem->realDataItem();
    if (!realData)
        throw GUIHelpers::Error("JobModelFunctions::processInstrumentLink() -> Error. No data.");

    realData->setInstrumentId(jobItem->instrumentItem()->id());
    realData->updateToInstrument(jobItem->instrumentItem());
}

void copyMasksToInstrument(JobItem* jobItem)
{
    auto mask_container = jobItem->realDataItem()->maskContainerItem();
    jobItem->instrumentItem()->importMasks(mask_container);
}

void cropRealData(JobItem* jobItem)
{
    RealDataItem* realData = jobItem->realDataItem();

    // adjusting real data to the size of region of interest
    IntensityDataItem* intensityItem = realData->intensityDataItem();

    std::unique_ptr<OutputData<double>> origData(intensityItem->getOutputData()->clone());

    JobItemUtils::createDefaultDetectorMap(intensityItem, jobItem->instrumentItem());

    auto instrument = jobItem->instrumentItem()->createInstrument();
    instrument->getDetector()->iterate(
        [&](IDetector::const_iterator it) {
            auto cropped_data = intensityItem->getOutputData();
            (*cropped_data)[it.roiIndex()] = (*origData)[it.detectorIndex()];
        },
        /*visit_masked*/ false);

    intensityItem->updateDataRange();
}

void createFitContainers(JobItem* jobItem)
{
    SessionModel* model = jobItem->model();

    SessionItem* fitSuiteItem = jobItem->getItem(JobItem::T_FIT_SUITE);
    if (fitSuiteItem != nullptr) {
        throw GUIHelpers::Error("JobModel::createFitContainers() -> Error. Attempt to create "
                                "a second FitSuiteItem.");
    }

    fitSuiteItem = model->insertItem<FitSuiteItem>(jobItem, -1, JobItem::T_FIT_SUITE);

    SessionItem* parsContainerItem =
        fitSuiteItem->getItem(FitSuiteItem::T_FIT_PARAMETERS_CONTAINER);
    if (parsContainerItem != nullptr) {
        throw GUIHelpers::Error("JobModel::createFitContainers() -> Error. Attempt to create "
                                "a second FitParameterContainer.");
    }

    model->insertItem<FitParameterContainerItem>(fitSuiteItem, -1,
                                                 FitSuiteItem::T_FIT_PARAMETERS_CONTAINER);

    // Minimizer settings
    SessionItem* minimizerContainerItem = fitSuiteItem->getItem(FitSuiteItem::T_MINIMIZER);
    if (minimizerContainerItem != nullptr) {
        throw GUIHelpers::Error("JobModel::createFitContainers() -> Error. Attempt to create "
                                "a second MinimizerContainer.");
    }

    model->insertItem<MinimizerContainerItem>(fitSuiteItem, -1, FitSuiteItem::T_MINIMIZER);
}

PointwiseAxisItem* getPointwiseAxisItem(const SpecularInstrumentItem* instrument)
{
    return dynamic_cast<PointwiseAxisItem*>(
        instrument->beamItem()->inclinationAxisGroup()->getChildOfType("PointwiseAxis"));
}
} // namespace
