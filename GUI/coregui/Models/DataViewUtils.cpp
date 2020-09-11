// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/DataViewUtils.cpp
//! @brief     Implements functions in namespace DataViewUtils
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/coregui/Models/DataViewUtils.h"
#include "Core/Simulation/UnitConverterUtils.h"
#include "GUI/coregui/Models/Data1DViewItem.h"
#include "GUI/coregui/Models/DataItem.h"
#include "GUI/coregui/Models/DataPropertyContainer.h"
#include "GUI/coregui/Models/DomainObjectBuilder.h"
#include "GUI/coregui/Models/JobItem.h"
#include "GUI/coregui/Models/JobItemUtils.h"

namespace
{
std::unique_ptr<IUnitConverter> getConverter(Data1DViewItem* view_item)
{
    auto job_item = view_item->jobItem();
    ASSERT(job_item->instrumentItem());

    return DomainObjectBuilder::createUnitConverter(job_item->instrumentItem());
}

AxesUnits selectedUnits(Data1DViewItem* view_item)
{
    auto current_unit_name =
        view_item->getItemValue(Data1DViewItem::P_AXES_UNITS).value<ComboProperty>().getValue();
    return JobItemUtils::axesUnitsFromName(current_unit_name);
}
} // namespace

void DataViewUtils::updateAxesTitle(Data1DViewItem* view_item)
{
    auto converter = getConverter(view_item);
    if (!converter)
        return;
    auto current_units = selectedUnits(view_item);
    view_item->setXaxisTitle(QString::fromStdString(converter->axisName(0, current_units)));
    if (converter->dimension() > 1)
        view_item->setYaxisTitle(QString::fromStdString(converter->axisName(1, current_units)));
}

std::unique_ptr<OutputData<double>> DataViewUtils::getTranslatedData(Data1DViewItem* view_item,
                                                                     DataItem* data_item)
{
    std::unique_ptr<OutputData<double>> result;
    if (!data_item || !data_item->getOutputData())
        return result;

    auto converter = getConverter(view_item);
    auto current_units = selectedUnits(view_item);

    result = UnitConverterUtils::createOutputData(*converter, current_units);
    result->setRawDataVector(data_item->getOutputData()->getRawDataVector());

    return result;
}
