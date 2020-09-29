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

#include <QString>

class InstrumentItem;
class JobItem;
class RealDataItem;

//! Contains set of convenience methods for JobItem and its children.

namespace ItemFileNameUtils
{

QString jobResultsFileName(const JobItem& jobItem);

QString jobReferenceFileName(const JobItem& jobItem);

QString jobNativeDataFileName(const JobItem& jobItem);

QString realDataFileName(const RealDataItem& realDataItem);

QString nativeDataFileName(const RealDataItem& realDataItem);

QString instrumentDataFileName(const InstrumentItem& instrumentItem);

QStringList nonXMLFileNameFilters();

} // namespace ItemFileNameUtils

#endif // BORNAGAIN_GUI_COREGUI_MODELS_ITEMFILENAMEUTILS_H
