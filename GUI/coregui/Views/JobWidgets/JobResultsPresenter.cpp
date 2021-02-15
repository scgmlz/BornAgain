//  ************************************************************************************************
//
//  BornAgain: simulate and fit reflection and scattering
//
//! @file      GUI/coregui/Views/JobWidgets/JobResultsPresenter.cpp
//! @brief     Implements class JobResultsPresenter
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "GUI/coregui/Views/JobWidgets/JobResultsPresenter.h"
#include "GUI/coregui/Models/InstrumentItems.h"
#include "GUI/coregui/Models/JobItem.h"
#include "GUI/coregui/Views/FitWidgets/FitComparisonWidget.h"
#include "GUI/coregui/Views/FitWidgets/FitComparisonWidget1D.h"
#include "GUI/coregui/Views/IntensityDataWidgets/IntensityDataProjectionsWidget.h"
#include "GUI/coregui/Views/IntensityDataWidgets/IntensityDataWidget.h"
#include "GUI/coregui/Views/SpecularDataWidgets/SpecularDataWidget.h"
#include "GUI/coregui/utils/GUIHelpers.h"

JobResultsPresenter::JobResultsPresenter(QWidget* parent) : ItemComboWidget(parent)
{
    registerWidget("Color Map", create_new<IntensityDataWidget>);
    registerWidget("Projections", create_new<IntensityDataProjectionsWidget>);
    registerWidget("Fit 1D Data", create_new<FitComparisonWidget1D>);
    registerWidget("Fit 2D Data", create_new<FitComparisonWidget>);
    registerWidget("Reflectometry", create_new<SpecularDataWidget>);
}

QString JobResultsPresenter::itemPresentation() const
{
    if (!currentItem())
        return {};

    const auto& value = currentItem()->getItemValue(JobItem::P_PRESENTATION_TYPE);
    return value.isValid() ? value.toString() : selectedPresentation();
}

void JobResultsPresenter::setPresentation(const QString& presentationType)
{
    if (!currentItem())
        return;

    ItemComboWidget::setPresentation(presentationType);
    currentItem()->setItemValue(JobItem::P_PRESENTATION_TYPE, presentationType);
}

void JobResultsPresenter::setPresentation(JobViewFlags::EActivities activity)
{
    if (!currentItem())
        return;

    JobItem* jobItem = dynamic_cast<JobItem*>(currentItem());
    if (!jobItem)
        return;

    QString presentation;
    switch (activity) {
    case JobViewFlags::FITTING_ACTIVITY:
        presentation = fitPresentationOfInstrument(jobItem->instrumentItem());
        break;

    case JobViewFlags::REAL_TIME_ACTIVITY:
    case JobViewFlags::JOB_VIEW_ACTIVITY:
        presentation = defaultPresentationOfInstrument(jobItem->instrumentItem());
        break;
    }

    setPresentation(presentation);
}

//! Returns list of presentation types, available for given item. JobItem with fitting abilities
//! is valid for IntensityDataWidget and FitComparisonWidget.

QStringList JobResultsPresenter::activePresentationList(SessionItem* item)
{
    JobItem* jobItem = dynamic_cast<JobItem*>(item);
    if (!jobItem)
        return {};

    ASSERT(jobItem->instrumentItem() != nullptr);

    auto result = defaultActivePresentationsOfInstrument(jobItem->instrumentItem());

    if (jobItem->isValidForFitting())
        result << fitPresentationOfInstrument(jobItem->instrumentItem());

    return result;
}

QStringList JobResultsPresenter::presentationList(SessionItem* item)
{
    JobItem* jobItem = dynamic_cast<JobItem*>(item);
    if (!jobItem)
        return {};

    ASSERT(jobItem->instrumentItem() != nullptr);

    auto result = defaultActivePresentationsOfInstrument(jobItem->instrumentItem());
    auto addon = fitPresentationOfInstrument(jobItem->instrumentItem());
    if (!addon.isEmpty())
        result << addon;

    return result;
}

QString JobResultsPresenter::defaultPresentationOfInstrument(InstrumentItem* instrumentItem)
{
    if (instrumentItem->is<SpecularInstrumentItem>())
        return "Reflectometry";

    return "Color Map";
}

QStringList
JobResultsPresenter::defaultActivePresentationsOfInstrument(InstrumentItem* instrumentItem)
{
    if (instrumentItem->is<SpecularInstrumentItem>())
        return {"Reflectometry"};

    return {"Color Map", "Projections"};
}

QString JobResultsPresenter::fitPresentationOfInstrument(InstrumentItem* instrumentItem)
{
    if (instrumentItem->is<SpecularInstrumentItem>())
        return "Fit 1D Data";

    return "Fit 2D Data";
}
