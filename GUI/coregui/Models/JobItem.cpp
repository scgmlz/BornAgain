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

#include "JobItem.h"
#include "ComboProperty.h"
#include "FitSuiteItem.h"
#include "GUIHelpers.h"
#include "InstrumentItems.h"
#include "IntensityDataItem.h"
#include "JobItemFunctions.h"
#include "JobItemUtils.h"
#include "MaskUnitsConverter.h"
#include "MultiLayerItem.h"
#include "ParameterTreeItems.h"
#include "RealDataItem.h"
#include "SimulationOptionsItem.h"
#include "SpecularDataItem.h"
#include "item_constants.h"

const QString JobItem::P_IDENTIFIER = "Identifier";
const QString JobItem::P_SAMPLE_NAME = "Sample";
const QString JobItem::P_INSTRUMENT_NAME = "Instrument";
const QString JobItem::P_WITH_FITTING = "With Fitting";
const QString JobItem::P_STATUS = "Status";
const QString JobItem::P_BEGIN_TIME = "Begin Time";
const QString JobItem::P_END_TIME = "End Time";
const QString JobItem::P_DURATION = "Duration";
const QString JobItem::P_COMMENTS = "Comments";
const QString JobItem::P_PROGRESS = "Progress";
const QString JobItem::P_PRESENTATION_TYPE = "Presentation Type";
const QString JobItem::T_SAMPLE = "Sample Tag";
const QString JobItem::T_INSTRUMENT = "Instrument Tag";
const QString JobItem::T_OUTPUT = "Output Tag";
const QString JobItem::T_REALDATA = "Real Data Tag";
const QString JobItem::T_PARAMETER_TREE = "Parameter Tree";
const QString JobItem::T_SIMULATION_OPTIONS = "Simulation Options";
const QString JobItem::T_FIT_SUITE = "Fit Suite";

JobItem::JobItem() : SessionItem(Constants::JobItemType)
{
    setItemName(Constants::JobItemType);
    addProperty(P_IDENTIFIER, QString())->setVisible(false);
    addProperty(P_SAMPLE_NAME, QString())->setEditable(false);
    addProperty(P_INSTRUMENT_NAME, QString())->setEditable(false);
    addProperty(P_WITH_FITTING, false)->setVisible(false);

    addProperty(P_STATUS, Constants::STATUS_IDLE)->setEditable(false);

    addProperty(P_BEGIN_TIME, QString())->setEditable(false);
    addProperty(P_END_TIME, QString())->setEditable(false);

    auto durationItem = addProperty(P_DURATION, QString());
    durationItem->setEditable(false);
    durationItem->setToolTip(QStringLiteral("Duration of DWBA simulation in sec.msec format"));

    addProperty(P_COMMENTS, QString())->setVisible(false);
    addProperty(P_PROGRESS, 0)->setVisible(false);
    addProperty(P_PRESENTATION_TYPE, Constants::IntensityDataPresentation)->setVisible(false);

    registerTag(T_SAMPLE, 1, 1, QStringList() << Constants::MultiLayerType);
    registerTag(T_INSTRUMENT, 1, 1,
                QStringList() << Constants::GISASInstrumentType
                              << Constants::OffSpecInstrumentType
                              << Constants::SpecularInstrumentType);
    registerTag(T_OUTPUT, 1, 1, QStringList() << Constants::IntensityDataType
                << Constants::SpecularDataType);
    registerTag(T_REALDATA, 1, 1, QStringList() << Constants::RealDataType);
    registerTag(T_PARAMETER_TREE, 0, -1, QStringList() << Constants::ParameterContainerType);

    registerTag(T_SIMULATION_OPTIONS, 1, 1, QStringList() << Constants::SimulationOptionsType);

    registerTag(T_FIT_SUITE, 1, 1, QStringList() << Constants::FitSuiteType);

    mapper()->setOnChildPropertyChange([this](SessionItem* item, const QString& name) {
        if (item->parent() != this || name != DataItem::P_AXES_UNITS)
            return;

        if (auto intensityItem = dynamic_cast<IntensityDataItem*>(item)) {
            MaskUnitsConverter converter;
            converter.convertToNbins(intensityItem);

            JobItemUtils::updateDataAxes(intensityItem, instrumentItem());

            converter.convertFromNbins(intensityDataItem());
        } else if (auto specularItem = dynamic_cast<SpecularDataItem*>(item))
            JobItemUtils::updateDataAxes(specularItem, instrumentItem());
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
    if (status == Constants::STATUS_FAILED) {
        if (IntensityDataItem* intensityItem = intensityDataItem()) {
            if (intensityItem->getOutputData())
                intensityItem->getOutputData()->setAllTo(0.0);
            emit intensityItem->emitDataChanged();
        }
    }
}

bool JobItem::isIdle() const
{
    return getStatus() == Constants::STATUS_IDLE;
}

bool JobItem::isRunning() const
{
    return getStatus() == Constants::STATUS_RUNNING;
}

bool JobItem::isCompleted() const
{
    return getStatus() == Constants::STATUS_COMPLETED;
}

bool JobItem::isCanceled() const
{
    return getStatus() == Constants::STATUS_CANCELED;
}

bool JobItem::isFailed() const
{
    return getStatus() == Constants::STATUS_FAILED;
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
        str.sprintf("%7.3f", duration / 1000.);
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
    JobItemUtils::setResults(this, simulation);
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

QString JobItem::presentationType()
{
    return getItemValue(P_PRESENTATION_TYPE).toString();
}

QString JobItem::defaultPresentationType()
{
    auto instrument = instrumentItem();
    if (!instrument)
        throw GUIHelpers::Error(
            "Error in JobItem::defaultPresentationType: default presentation type "
            "cannot be determined");

    auto instrument_type = instrument->modelType();
    if (instrument_type == Constants::SpecularInstrumentType)
        return Constants::SpecularDataPresentation;
    else if (instrument_type == Constants::GISASInstrumentType
             || instrument_type == Constants::OffSpecInstrumentType)
        return Constants::IntensityDataPresentation;
    else
        GUIHelpers::Error("Error in JobItem::defaultPresentationType: unknown type of instrument "
                          "attached to the job item.");
    return QString();
}

//! Updates the name of file to store intensity data.

void JobItem::updateIntensityDataFileName()
{
    if (DataItem* item = dataItem())
        item->setItemValue(DataItem::P_FILE_NAME,
                           JobItemFunctions::jobResultsFileName(*this));

    if (RealDataItem* realItem = realDataItem())
        if (IntensityDataItem* item = realItem->intensityDataItem())
            item->setItemValue(DataItem::P_FILE_NAME,
                               JobItemFunctions::jobReferenceFileName(*this));
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
