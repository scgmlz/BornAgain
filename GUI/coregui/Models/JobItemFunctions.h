// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/JobItemFunctions.h
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

#ifndef JOBITEMFUNCTIONS_H
#define JOBITEMFUNCTIONS_H

#include "WinDllMacros.h"
#include <QString>

class JobItem;
class RealDataItem;

//! Contains set of convenience methods for JobItem and its children.

namespace JobItemFunctions
{

BA_CORE_API_ QString jobResultsFileName(const JobItem& jobItem);

BA_CORE_API_ QString jobReferenceFileName(const JobItem& jobItem);

BA_CORE_API_ QString realDataFileName(const RealDataItem& realDataItem);

}

#endif // JOBITEMFUNCTIONS_H
