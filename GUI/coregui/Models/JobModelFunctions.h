// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/JobModelFunctions.h
//! @brief     Defines auxiliary functions in JobModelFunctions namespace.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_MODELS_JOBMODELFUNCTIONS_H
#define BORNAGAIN_GUI_COREGUI_MODELS_JOBMODELFUNCTIONS_H

class InstrumentItem;
class JobItem;
class MultiLayerItem;
class RealDataItem;
class SessionItem;

//! Contains set of functions to extend JobModel functionality.
//! Handles setup of JobItem in fitting context.

namespace JobModelFunctions
{
//! Initializes Data1DViewItem and assigns it to the passed JobItem
void initDataView(JobItem* jobItem);

//! Properly copies sample and materials into JobItem
void setupJobItemSampleData(JobItem* jobItem, const MultiLayerItem* sampleItem);

//! Properly copies instrument into job item
void setupJobItemInstrument(JobItem* jobItem, const InstrumentItem* from);

void setupJobItemOutput(JobItem* jobItem);

void setupJobItemForFit(JobItem* jobItem, const RealDataItem* realDataItem);

void muteMagnetizationData(JobItem* jobItem);

//! Copy RealDataItem to jobItem intended for fitting.
void copyRealDataItem(JobItem* jobItem, const RealDataItem* realDataItem);

//! Determines parenting JobItem of a given SessionItem. Returns nullptr, if there
//! is no parent of JobItem type

const JobItem* findJobItem(const SessionItem* item);
} // namespace JobModelFunctions

#endif // BORNAGAIN_GUI_COREGUI_MODELS_JOBMODELFUNCTIONS_H
