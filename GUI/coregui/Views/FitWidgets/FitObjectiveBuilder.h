//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/FitWidgets/FitObjectiveBuilder.h
//! @brief     Defines class FitObjectiveBuilder
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_GUI_COREGUI_VIEWS_FITWIDGETS_FITOBJECTIVEBUILDER_H
#define BORNAGAIN_GUI_COREGUI_VIEWS_FITWIDGETS_FITOBJECTIVEBUILDER_H

#include <memory>

class JobItem;
class FitObjective;
class ISimulation;
namespace mumufit {
class Parameters;
}
template <class T> class OutputData;
class IMinimizer;
class GUIFitObserver;
class IChiSquaredModule;

class FitObjectiveBuilder {
public:
    FitObjectiveBuilder(JobItem* jobItem);
    ~FitObjectiveBuilder();

    void runFit();

    std::unique_ptr<FitObjective> createFitObjective() const;
    std::unique_ptr<IMinimizer> createMinimizer() const;
    std::unique_ptr<IChiSquaredModule> createChiSquaredModule() const;

    mumufit::Parameters createParameters() const;

    void attachObserver(std::shared_ptr<GUIFitObserver> observer);

    void interruptFitting();

private:
    JobItem* m_jobItem;

    std::unique_ptr<ISimulation> buildSimulation(const mumufit::Parameters& params) const;
    std::unique_ptr<OutputData<double>> createOutputData() const;

    void update_fit_parameters(const mumufit::Parameters& params) const;

    std::shared_ptr<GUIFitObserver> m_observer;
    std::unique_ptr<FitObjective> m_fit_objective;
};

#endif // BORNAGAIN_GUI_COREGUI_VIEWS_FITWIDGETS_FITOBJECTIVEBUILDER_H
