// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/JobWidgets/JobResultsPresenter.cpp
//! @brief     Implements class JobResultsPresenter
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/coregui/Views/JobWidgets/JobResultsPresenter.h"
#include "GUI/coregui/Models/JobItem.h"
#include "GUI/coregui/Views/FitWidgets/FitComparisonWidget.h"
#include "GUI/coregui/Views/FitWidgets/FitComparisonWidget1D.h"
#include "GUI/coregui/Views/IntensityDataWidgets/IntensityDataProjectionsWidget.h"
#include "GUI/coregui/Views/IntensityDataWidgets/IntensityDataWidget.h"
#include "GUI/coregui/Views/SpecularDataWidgets/SpecularDataWidget.h"
#include "GUI/coregui/utils/GUIHelpers.h"

namespace
{
// Will switch to the presentation which was used before for given item
const bool use_job_last_presentation = true;

const std::map<QString, QString> instrument_to_default_presentaion{
    {"SpecularInstrument", "Reflectometry"},
    {"GISASInstrument", "Color Map"},
    {"OffSpecInstrument", "Color Map"},
    {"DepthProbeInstrument", "Color Map"}};

const std::map<QString, QString> instrument_to_fit_presentaion{
    {"SpecularInstrument", "Fit 1D Data"},
    {"GISASInstrument", "Fit 2D Data"},
    {"OffSpecInstrument", "Fit 2D Data"}};

const std::map<JobViewFlags::EActivities, std::map<QString, QString>> activity_to_presentation{
    {JobViewFlags::FITTING_ACTIVITY, instrument_to_fit_presentaion},
    {JobViewFlags::REAL_TIME_ACTIVITY, instrument_to_default_presentaion},
    {JobViewFlags::JOB_VIEW_ACTIVITY, instrument_to_default_presentaion}};

const std::map<QString, QStringList> default_active_presentation_list{
    {"SpecularInstrument", {"Reflectometry"}},
    {{"GISASInstrument"}, {"Color Map", "Projections"}},
    {{"OffSpecInstrument"}, {"Color Map", "Projections"}},
    {{"DepthProbeInstrument"}, {"Color Map", "Projections"}}};

template <class QStringObj>
QStringObj getPresentations(const SessionItem* job_item,
                            const std::map<QString, QStringObj>& presentation_map)
{
    const QString& instrument_type = job_item->getItem(JobItem::T_INSTRUMENT)->modelType();
    const auto list_iter = presentation_map.find(instrument_type);
    if (list_iter == presentation_map.cend())
        return QStringObj();
    return list_iter->second;
}
} // namespace

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
    return use_job_last_presentation && value.isValid() ? value.toString() : selectedPresentation();
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

    auto iter = activity_to_presentation.find(activity);
    if (iter == activity_to_presentation.cend())
        throw GUIHelpers::Error("Error in JobResultsPresenter::setPresentation: unknown activity.");

    setPresentation(getPresentations(currentItem(), iter->second));
}

//! Returns list of presentation types, available for given item. JobItem with fitting abilities
//! is valid for IntensityDataWidget and FitComparisonWidget.

QStringList JobResultsPresenter::activePresentationList(SessionItem* item)
{
    auto result = getPresentations(item, default_active_presentation_list);

    auto job_item = dynamic_cast<JobItem*>(item);
    if (job_item && job_item->isValidForFitting())
        result << getPresentations(item, instrument_to_fit_presentaion);

    return result;
}

QStringList JobResultsPresenter::presentationList(SessionItem* item)
{
    auto result = getPresentations(item, default_active_presentation_list);
    auto addon = getPresentations(item, instrument_to_fit_presentaion);
    if (!addon.isEmpty())
        result << addon;

    return result;
}
