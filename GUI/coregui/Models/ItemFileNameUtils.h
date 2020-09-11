// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/ItemFileNameUtils.h
//! @brief     Defines auxiliary functions in ItemFileNameUtils namespace.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_MODELS_ITEMFILENAMEUTILS_H
#define BORNAGAIN_GUI_COREGUI_MODELS_ITEMFILENAMEUTILS_H

#include "Wrap/WinDllMacros.h"
#include <QString>

class InstrumentItem;
class JobItem;
class RealDataItem;

//! Contains set of convenience methods for JobItem and its children.

namespace ItemFileNameUtils
{

BA_CORE_API_ QString jobResultsFileName(const JobItem& jobItem);

BA_CORE_API_ QString jobReferenceFileName(const JobItem& jobItem);

BA_CORE_API_ QString jobNativeDataFileName(const JobItem& jobItem);

BA_CORE_API_ QString realDataFileName(const RealDataItem& realDataItem);

BA_CORE_API_ QString nativeDataFileName(const RealDataItem& realDataItem);

BA_CORE_API_ QString instrumentDataFileName(const InstrumentItem& instrumentItem);

BA_CORE_API_ QStringList nonXMLFileNameFilters();

} // namespace ItemFileNameUtils

#endif // BORNAGAIN_GUI_COREGUI_MODELS_ITEMFILENAMEUTILS_H
