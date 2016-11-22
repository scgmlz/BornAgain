// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/JobModelFunctions.h
//! @brief     Defines auxiliary functions in JobModelFunctions namespace.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef JOBMODELFUNCTIONS_H
#define JOBMODELFUNCTIONS_H

#include "WinDllMacros.h"

class JobItem;
class RealDataItem;

//! Contains set of functions to extend JobModel functionality.
//! Handles setup of JobItem in fitting context.

namespace JobModelFunctions
{

BA_CORE_API_ void setupJobItemForFit(JobItem *jobItem, const RealDataItem *realDataItem);

}


#endif // JOBMODELFUNCTIONS_H

