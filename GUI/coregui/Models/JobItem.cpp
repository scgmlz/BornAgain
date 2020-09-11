// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/JobItem.cpp
//! @brief     Implements class JobItem
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/coregui/Models/JobItem.h"
#include "GUI/coregui/Models/ComboProperty.h"
#include "GUI/coregui/Models/Data1DViewItem.h"
#include "GUI/coregui/Models/FitSuiteItem.h"
#include "GUI/coregui/Models/InstrumentItems.h"
#include "GUI/coregui/Models/IntensityDataItem.h"
#include "GUI/coregui/Models/ItemFileNameUtils.h"
#include "GUI/coregui/Models/JobItemUtils.h"
#include "GUI/coregui/Models/MaterialItemContainer.h"
#include "GUI/coregui/Models/MultiLayerItem.h"
#include "GUI/coregui/Models/ParameterTreeItems.h"
#include "GUI/coregui/Models/RealDataItem.h"
#include "GUI/coregui/Models/SimulationOptionsItem.h"
#include "GUI/coregui/Models/SpecularDataItem.h"
#include "GUI/coregui/Views/MaskWidgets/MaskUnitsConverter.h"
#include "GUI/coregui/utils/GUIHelpers.h"

const QString JobItem::P_IDENTIFIER = "Identifier";
const QString JobItem::P_SAMPLE_NAME = "Sample";
const QString JobItem::P_INSTRUMENT_NAME = "Instrument";
const QString JobItem::P_WITH_FITTING = "With fitting";
const QString JobItem::P_STATUS = "Status";
const QString JobItem::P_BEGIN_TIME = "Begin time";
const QString JobItem::P_END_TIME = "End time";
const QString JobItem::P_DURATION = "Duration";
const QString JobItem::P_COMMENTS = "Comments";
const QString JobItem::P_PROGRESS = "Progress";
const QString JobItem::P_PRESENTATION_TYPE = "Presentation type";
const QString JobItem::T_SAMPLE = "Sample tag";
const QString JobItem::T_MATERIAL_CONTAINER = "Material container tag";
const QString JobItem::T_INSTRUMENT = "Instrument tag";
const QString JobItem::T_OUTPUT = "Output tag";
const QString JobItem::T_REALDATA = "Real Data tag";
const QString JobItem::T_DATAVIEW = "Data View tag";
const QString JobItem::T_PARAMETER_TREE = "Parameter tree tag";
const QString JobItem::T_SIMULATION_OPTIONS = "Simulation options tag";
const QString JobItem::T_FIT_SUITE = "Fit suite tag";

JobItem::JobItem() : SessionItem("JobItem")
{
    setItemName("JobItem");
    addProperty(P_IDENTIFIER, QString())->setVisible(false);
    addProperty(P_SAMPLE_NAME, QString())->setEditable(false);
    addProperty(P_INSTRUMENT_NAME, QString())->setEditable(false);
    addProperty(P_WITH_FITTING, false)->setVisible(false);

    addProperty(P_STATUS, "Idle")->setEditable(false);

    addProperty(P_BEGIN_TIME, QString())->setEditable(false);
    addProperty(P_END_TIME, QString())->setEditable(false);

    auto durationItem = addProperty(P_DURATION, QString());
    durationItem->setEditable(false);
    durationItem->setToolTip("Duration of DWBA simulation in sec.msec format");

    addProperty(P_COMMENTS, QString())->setVisible(false);
    addProperty(P_PROGRESS, 0)->setVisible(false);
    addProperty(P_PRESENTATION_TYPE, QVariant::Type::Invalid)->setVisible(false);

    registerTag(T_SAMPLE, 1, 1, QStringList() << "MultiLayer");
    registerTag(T_MATERIAL_CONTAINER, 1, 1, QStringList{"MaterialContainer"});
    registerTag(T_INSTRUMENT, 1, 1,
                QStringList() << "GISASInstrument"
                              << "OffSpecInstrument"
                              << "SpecularInstrument"
                              << "DepthProbeInstrument");
    registerTag(T_OUTPUT, 1, 1,
                QStringList() << "IntensityData"
                              << "SpecularData");
    registerTag(T_REALDATA, 1, 1, QStringList() << "RealData");
    registerTag(T_DATAVIEW, 1, 1, QStringList() << "Data1DViewItem");
    registerTag(T_PARAMETER_TREE, 0, -1, QStringList() << "Parameter Container");

    registerTag(T_SIMULATION_OPTIONS, 1, 1, QStringList() << "SimulationOptions");

    registerTag(T_FIT_SUITE, 1, 1, QStringList() << "FitSuite");

    mapper()->setOnChildPropertyChange([this](SessionItem* item, const QString& name) {
        if (item->parent() == this && dynamic_cast<DataItem*>(item)
            && name == DataItem::P_AXES_UNITS)
            dynamic_cast<DataItem*>(item)->updateAxesUnits(instrumentItem());
    });

    mapper()->setOnPropertyChange([this](const QString& name) {
        if (name == P_NAME)
            updateIntensityDataFileName();
    });
}

QString JobItem::getIdentifier() const
{
    return getItemValue(P_IDENTIFIER).toString();
}

void JobItem::setIdentifier(const QString& identifier)
{
    setItemValue(JobItem::P_IDENTIFIER, identifier);
}

IntensityDataItem* JobItem::intensityDataItem()
{
    return dynamic_cast<IntensityDataItem*>(getItem(T_OUTPUT));
}

DataItem* JobItem::dataItem()
{
    return dynamic_cast<DataItem*>(getItem(T_OUTPUT));
}

QString JobItem::getStatus() const
{
    return getItemValue(P_STATUS).toString();
}

void JobItem::setStatus(const QString& status)
{
    setItemValue(P_STATUS, status);
    if (status == "Failed") {
        if (DataItem* intensityItem = dataItem()) {
            if (intensityItem->getOutputData())
                intensityItem->getOutputData()->setAllTo(0.0);
            emit intensityItem->emitDataChanged();
        }
    }
}

bool JobItem::isIdle() const
{
    return getStatus() == "Idle";
}

bool JobItem::isRunning() const
{
    return getStatus() == "Running";
}

bool JobItem::isCompleted() const
{
    return getStatus() == "Completed";
}

bool JobItem::isCanceled() const
{
    return getStatus() == "Canceled";
}

bool JobItem::isFailed() const
{
    return getStatus() == "Failed";
}

bool JobItem::isValidForFitting()
{
    return isTag(T_REALDATA) && getItem(T_REALDATA) ? true : false;
}

void JobItem::setBeginTime(const QString& begin_time)
{
    setItemValue(P_BEGIN_TIME, begin_time);
}

void JobItem::setEndTime(const QString& end_time)
{
    setItemValue(P_END_TIME, end_time);
}

// Sets duration (msec -> "sec.msec")
void JobItem::setDuration(int duration)
{
    QString str;
    if (duration != 0)
        str = QString("%7.3f").arg(duration / 1000.);
    setItemValue(P_DURATION, str.simplified());
}

QString JobItem::getComments() const
{
    return getItemValue(P_COMMENTS).toString();
}

void JobItem::setComments(const QString& comments)
{
    setItemValue(P_COMMENTS, comments);
}

int JobItem::getProgress() const
{
    return getItemValue(P_PROGRESS).toInt();
}

void JobItem::setProgress(int progress)
{
    setItemValue(P_PROGRESS, progress);
}

bool JobItem::runImmediately() const
{
    return simulationOptionsItem()->runImmediately();
}

bool JobItem::runInBackground() const
{
    return simulationOptionsItem()->runInBackground();
}

MultiLayerItem* JobItem::multiLayerItem()
{
    return dynamic_cast<MultiLayerItem*>(getItem(T_SAMPLE));
}

InstrumentItem* JobItem::instrumentItem()
{
    return dynamic_cast<InstrumentItem*>(getItem(T_INSTRUMENT));
}

void JobItem::setResults(const Simulation* simulation)
{
    JobItemUtils::setResults(dataItem(), simulation);
    updateIntensityDataFileName();
}

FitSuiteItem* JobItem::fitSuiteItem()
{
    return dynamic_cast<FitSuiteItem*>(getItem(JobItem::T_FIT_SUITE));
}

ParameterContainerItem* JobItem::parameterContainerItem()
{
    return const_cast<ParameterContainerItem*>(
        static_cast<const JobItem*>(this)->parameterContainerItem());
}

const ParameterContainerItem* JobItem::parameterContainerItem() const
{
    return dynamic_cast<ParameterContainerItem*>(getItem(JobItem::T_PARAMETER_TREE));
}

FitParameterContainerItem* JobItem::fitParameterContainerItem()
{
    if (FitSuiteItem* item = fitSuiteItem())
        return item->fitParameterContainerItem();

    return nullptr;
}

RealDataItem* JobItem::realDataItem()
{
    return dynamic_cast<RealDataItem*>(getItem(JobItem::T_REALDATA));
}

const MaterialItemContainer* JobItem::materialContainerItem() const
{
    return static_cast<MaterialItemContainer*>(getItem(JobItem::T_MATERIAL_CONTAINER));
}

Data1DViewItem* JobItem::dataItemView()
{
    return dynamic_cast<Data1DViewItem*>(getItem(JobItem::T_DATAVIEW));
}

//! Updates the name of file to store intensity data.

void JobItem::updateIntensityDataFileName()
{
    if (DataItem* item = dataItem())
        item->setItemValue(DataItem::P_FILE_NAME, ItemFileNameUtils::jobResultsFileName(*this));

    if (RealDataItem* realItem = realDataItem()) {
        if (DataItem* item = realItem->dataItem())
            item->setItemValue(DataItem::P_FILE_NAME,
                               ItemFileNameUtils::jobReferenceFileName(*this));

        if (DataItem* item = realItem->nativeData())
            item->setItemValue(DataItem::P_FILE_NAME,
                               ItemFileNameUtils::jobNativeDataFileName(*this));
    }
}

SimulationOptionsItem* JobItem::simulationOptionsItem()
{
    return const_cast<SimulationOptionsItem*>(
        static_cast<const JobItem*>(this)->simulationOptionsItem());
}

const SimulationOptionsItem* JobItem::simulationOptionsItem() const
{
    return &item<const SimulationOptionsItem>(T_SIMULATION_OPTIONS);
}
