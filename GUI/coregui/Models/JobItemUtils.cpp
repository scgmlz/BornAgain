// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/JobItemUtils.cpp
//! @brief     Implements class JobItemUtils
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/coregui/Models/JobItemUtils.h"
#include "Core/Simulation/Simulation.h"
#include "Core/Simulation/UnitConverterUtils.h"
#include "GUI/coregui/Models/ComboProperty.h"
#include "GUI/coregui/Models/DataItem.h"
#include "GUI/coregui/Models/DomainObjectBuilder.h"
#include "GUI/coregui/Models/InstrumentItems.h"
#include "GUI/coregui/Models/JobItem.h"
#include "GUI/coregui/Models/RealDataItem.h"
#include "GUI/coregui/utils/GUIHelpers.h"
#include <QDebug>
#include <QFileInfo>

namespace
{
const std::map<QString, AxesUnits> units_from_names{{"nbins", AxesUnits::NBINS},
                                                    {"Radians", AxesUnits::RADIANS},
                                                    {"Degrees", AxesUnits::DEGREES},
                                                    {"mm", AxesUnits::MM},
                                                    {"q-space", AxesUnits::QSPACE}};

const std::map<AxesUnits, QString> names_from_units{{AxesUnits::NBINS, "nbins"},
                                                    {AxesUnits::RADIANS, "Radians"},
                                                    {AxesUnits::MM, "mm"},
                                                    {AxesUnits::QSPACE, "q-space"},
                                                    {AxesUnits::DEGREES, "Degrees"}};

//! Updates axes' titles
void updateAxesTitle(DataItem* intensityItem, const IUnitConverter& converter, AxesUnits units);
} // namespace

//! Updates axes of OutputData in IntensityData item to correspond with ::P_AXES_UNITS selection.
//! InstrumentItem is used to get domain's detector map for given units.

void JobItemUtils::updateDataAxes(DataItem* intensityItem, const InstrumentItem* instrumentItem)
{
    ASSERT(intensityItem);

    if (!instrumentItem) {
        // special case when reading old project files: project failed on load instrument
        // but we want to try to recover the rest.
        qInfo() << "JobItemUtils::updateDataAxes() -> Error. Absent instrument.";
        return;
    }

    if (!intensityItem->getOutputData())
        return;

    AxesUnits requested_units = axesUnitsFromName(intensityItem->selectedAxesUnits());

    const auto converter = DomainObjectBuilder::createUnitConverter(instrumentItem);
    auto newData = UnitConverterUtils::createOutputData(*converter.get(), requested_units);
    newData->setRawDataVector(intensityItem->getOutputData()->getRawDataVector());

    intensityItem->setOutputData(newData.release());
    intensityItem->setAxesRangeToData();
    updateAxesTitle(intensityItem, *converter, requested_units);
}

//! Correspondance of domain detector axes types to their gui counterpart.

QString JobItemUtils::nameFromAxesUnits(AxesUnits units)
{
    return names_from_units.find(units) != names_from_units.end() ? names_from_units.at(units)
                                                                  : QString();
}

//! Correspondance of GUI axes units names to their domain counterpart.

AxesUnits JobItemUtils::axesUnitsFromName(const QString& name)
{
    return units_from_names.at(name);
}

//! Sets axes units suitable for given instrument.

void JobItemUtils::setIntensityItemAxesUnits(DataItem* intensityItem,
                                             const InstrumentItem* instrumentItem)
{
    const auto converter = DomainObjectBuilder::createUnitConverter(instrumentItem);
    if (!converter)
        return;
    setIntensityItemAxesUnits(intensityItem, *converter);
}

void JobItemUtils::setIntensityItemAxesUnits(DataItem* intensityItem,
                                             const IUnitConverter& converter)
{
    ComboProperty combo = availableUnits(converter);
    intensityItem->setItemValue(DataItem::P_AXES_UNITS, combo.variant());
}

void JobItemUtils::createDefaultDetectorMap(DataItem* intensityItem,
                                            const InstrumentItem* instrumentItem)
{
    const auto converter = DomainObjectBuilder::createUnitConverter(instrumentItem);
    auto output_data = UnitConverterUtils::createOutputData(*converter, converter->defaultUnits());
    intensityItem->setOutputData(output_data.release());
    setIntensityItemAxesUnits(intensityItem, *converter);
    updateAxesTitle(intensityItem, *converter, converter->defaultUnits());
}

void JobItemUtils::setResults(DataItem* intensityItem, const Simulation* simulation)
{
    const auto sim_result = simulation->result();
    if (intensityItem->getOutputData() == nullptr) {
        const auto& converter = sim_result.converter();
        JobItemUtils::setIntensityItemAxesUnits(intensityItem, converter);
        updateAxesTitle(intensityItem, converter, converter.defaultUnits());
    }
    auto selected_units = JobItemUtils::axesUnitsFromName(intensityItem->selectedAxesUnits());
    auto data = sim_result.data(selected_units);
    intensityItem->setOutputData(data.release());
}

ComboProperty JobItemUtils::availableUnits(const IUnitConverter& converter)
{
    ComboProperty result;
    for (auto units : converter.availableUnits()) {
        auto unit_name = nameFromAxesUnits(units);
        if (unit_name != "")
            result << unit_name;
    }

    result.setValue(nameFromAxesUnits(converter.defaultUnits()));
    return result;
}

namespace
{
void updateAxesTitle(DataItem* intensityItem, const IUnitConverter& converter, AxesUnits units)
{
    intensityItem->setXaxisTitle(QString::fromStdString(converter.axisName(0, units)));
    if (converter.dimension() > 1)
        intensityItem->setYaxisTitle(QString::fromStdString(converter.axisName(1, units)));
}
} // namespace
