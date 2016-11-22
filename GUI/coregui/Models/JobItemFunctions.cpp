// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/JobItemFunctions.cpp
//! @brief     Defines auxiliary functions in JobItemFunctions namespace.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "JobItemFunctions.h"
#include "GUIHelpers.h"
#include "JobItem.h"
#include "RealDataItem.h"
#include "item_constants.h"

namespace JobItemFunctions
{
const QString jobdata_file_prefix = "jobdata";
const QString refdata_file_prefix = "refdata";
const QString realdata_file_prefix = "realdata";

QString intensityDataFileName(const QString& itemName, const QString& prefix);

}

//! Constructs the name of the file for intensity data.

QString JobItemFunctions::intensityDataFileName(const QString& itemName, const QString& prefix)
{
    QString bodyName = GUIHelpers::getValidFileName(itemName);
    return QString("%1_%2_0.int.gz").arg(prefix).arg(bodyName);
}

//! Constructs the name of the file with simulated intensities.

QString JobItemFunctions::jobResultsFileName(const JobItem& jobItem)
{
    return JobItemFunctions::intensityDataFileName(jobItem.itemName(), jobdata_file_prefix);
}

//! Constructs the name of the file with reference data.

QString JobItemFunctions::jobReferenceFileName(const JobItem& jobItem)
{
    return JobItemFunctions::intensityDataFileName(jobItem.itemName(), refdata_file_prefix);
}

//! Constructs the name of the intensity file belonging to real data item.

QString JobItemFunctions::realDataFileName(const RealDataItem& realDataItem)
{
    return JobItemFunctions::intensityDataFileName(realDataItem.itemName(), realdata_file_prefix);
}
