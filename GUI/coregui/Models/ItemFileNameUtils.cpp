// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/ItemFileNameUtils.cpp
//! @brief     Defines auxiliary functions in ItemFileNameUtils namespace.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/coregui/Models/ItemFileNameUtils.h"
#include "GUI/coregui/Models/InstrumentItems.h"
#include "GUI/coregui/Models/JobItem.h"
#include "GUI/coregui/Models/RealDataItem.h"
#include "GUI/coregui/utils/GUIHelpers.h"

namespace
{
const QString jobdata_file_prefix = "jobdata";
const QString refdata_file_prefix = "refdata";
const QString realdata_file_prefix = "realdata";
const QString instrument_file_prefix = "instrdata";
const QString nativedata_file_prefix = "nativedata";

//! Constructs the name of the file for intensity data.
QString intensityDataFileName(const QString& itemName, const QString& prefix);
} // namespace

//! Constructs the name of the file with simulated intensities.

QString ItemFileNameUtils::jobResultsFileName(const JobItem& jobItem)
{
    return intensityDataFileName(jobItem.itemName(), jobdata_file_prefix);
}

//! Constructs the name of the file with reference data.

QString ItemFileNameUtils::jobReferenceFileName(const JobItem& jobItem)
{
    return intensityDataFileName(jobItem.itemName(), refdata_file_prefix);
}

QString ItemFileNameUtils::jobNativeDataFileName(const JobItem& jobItem)
{
    return intensityDataFileName(jobItem.getIdentifier(), nativedata_file_prefix);
}

//! Constructs the name of the intensity file belonging to real data item.

QString ItemFileNameUtils::realDataFileName(const RealDataItem& realDataItem)
{
    return intensityDataFileName(realDataItem.itemName(), realdata_file_prefix);
}

QString ItemFileNameUtils::nativeDataFileName(const RealDataItem& realDataItem)
{
    return intensityDataFileName(realDataItem.itemName(), nativedata_file_prefix);
}

QString ItemFileNameUtils::instrumentDataFileName(const InstrumentItem& instrumentItem)
{
    auto instrument_id = instrumentItem.getItemValue(InstrumentItem::P_IDENTIFIER).toString();
    return intensityDataFileName(instrument_id, instrument_file_prefix);
}

//! Returns list of fileName filters related to nonXML data stored by JobModel and RealDataModel.

QStringList ItemFileNameUtils::nonXMLFileNameFilters()
{
    QStringList result = QStringList() << QString(jobdata_file_prefix + "_*.int.gz")
                                       << QString(refdata_file_prefix + "_*.int.gz")
                                       << QString(realdata_file_prefix + "_*.int.gz")
                                       << QString(nativedata_file_prefix + "_*.int.gz")
                                       << QString(instrument_file_prefix + "_*.int.gz");

    return result;
}

namespace
{
QString intensityDataFileName(const QString& itemName, const QString& prefix)
{
    QString bodyName = GUIHelpers::getValidFileName(itemName);
    return QString("%1_%2_0.int.gz").arg(prefix).arg(bodyName);
}
} // namespace
