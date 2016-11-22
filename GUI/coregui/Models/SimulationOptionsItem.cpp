// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/SimulationOptionsItem.cpp
//! @brief     Defines class SimulationOptionsItem
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include <thread>
#include "SimulationOptionsItem.h"
#include "ComboProperty.h"

namespace
{

QStringList getRunPolicyTooltips()
{
    QStringList result;
    result.append(QStringLiteral("Start simulation immediately, switch to Jobs view automatically when completed"));
    result.append(QStringLiteral("Start simulation immediately, do not switch to Jobs view when completed"));
    result.append(QStringLiteral("Only submit simulation for consequent execution,"
                " has to be started from Jobs view explicitely"));
    return result;
}

const QString tooltip_runpolicy = "Defines run policy for the simulation";
const QString tooltip_nthreads = "Defines number of threads to use for the simulation.";
const QString tooltip_computation =
        "Defines computation method (analytical or Monte-Carlo integration)";

}


const QString SimulationOptionsItem::P_RUN_POLICY = "Run Policy";
const QString SimulationOptionsItem::P_NTHREADS = "Number of Threads";
const QString SimulationOptionsItem::P_COMPUTATION_METHOD = "Computation method";
const QString SimulationOptionsItem::P_MC_POINTS = "Number of MC points";


SimulationOptionsItem::SimulationOptionsItem()
    : SessionItem(Constants::SimulationOptionsType)
{

    ComboProperty policy;
    policy << Constants::JOB_RUN_IMMEDIATELY
           << Constants::JOB_RUN_IN_BACKGROUND
           << Constants::JOB_RUN_SUBMIT_ONLY;
    policy.setToolTips(getRunPolicyTooltips());
    addProperty(P_RUN_POLICY, policy.getVariant())->setToolTip(tooltip_runpolicy);

    ComboProperty nthreads;
    nthreads << getCPUUsageOptions();
    addProperty(P_NTHREADS, nthreads.getVariant())->setToolTip(tooltip_nthreads);

    ComboProperty computationMethod;
    computationMethod << Constants::SIMULATION_ANALYTICAL << Constants::SIMULATION_MONTECARLO;
    addProperty(P_COMPUTATION_METHOD, computationMethod.getVariant())->setToolTip(tooltip_computation);

    addProperty(P_MC_POINTS, 100)->setEnabled(false);

    mapper()->setOnPropertyChange(
        [this](const QString &name) {
            if(name == P_COMPUTATION_METHOD && isTag(P_MC_POINTS)) {
                ComboProperty combo = getItemValue(P_COMPUTATION_METHOD).value<ComboProperty>();

                if(combo.getValue() == Constants::SIMULATION_ANALYTICAL) {
                    getItem(P_MC_POINTS)->setEnabled(false);

                } else {
                    getItem(P_MC_POINTS)->setEnabled(true);
                }
            }
    });


}

int SimulationOptionsItem::getNumberOfThreads() const
{
    ComboProperty combo = getItemValue(P_NTHREADS).value<ComboProperty>();
    foreach(QChar ch, combo.getValue()) {
        if(ch.isDigit()) return ch.digitValue();
    }
    return 0;
}

bool SimulationOptionsItem::runImmediately() const
{
    ComboProperty combo = getItemValue(P_RUN_POLICY).value<ComboProperty>();
    return combo.getValue() == Constants::JOB_RUN_IMMEDIATELY;
}

bool SimulationOptionsItem::runInBackground() const
{
    ComboProperty combo = getItemValue(P_RUN_POLICY).value<ComboProperty>();
    return combo.getValue() == Constants::JOB_RUN_IN_BACKGROUND;
}

void SimulationOptionsItem::setRunPolicy(const QString &policy)
{
    ComboProperty combo = getItemValue(P_RUN_POLICY).value<ComboProperty>();
    combo.setValue(policy);
    setItemValue(P_RUN_POLICY, combo.getVariant());
}

void SimulationOptionsItem::setComputationMethod(const QString &name)
{
    ComboProperty combo = getItemValue(P_COMPUTATION_METHOD).value<ComboProperty>();
    combo.setValue(name);
    setItemValue(P_COMPUTATION_METHOD, combo.getVariant());
}

QString SimulationOptionsItem::getComputationMethod() const
{
    ComboProperty combo = getItemValue(P_COMPUTATION_METHOD).value<ComboProperty>();
    return combo.getValue();
}

int SimulationOptionsItem::getNumberOfMonteCarloPoints() const
{
    return getItemValue(P_MC_POINTS).toInt();
}

void SimulationOptionsItem::setNumberOfMonteCarloPoints(int npoints)
{
    setItemValue(P_MC_POINTS, npoints);
}

//! returns list with number of threads to select
QStringList SimulationOptionsItem::getCPUUsageOptions()
{
    QStringList result;
    int nthreads = std::thread::hardware_concurrency();
    for(int i = nthreads; i>0; i--){
        if(i == nthreads) {
            result.append(QString("Max (%1 threads)").arg(QString::number(i)));
        } else if(i == 1) {
            result.append(QString("%1 thread").arg(QString::number(i)));
        } else {
            result.append(QString("%1 threads").arg(QString::number(i)));
        }
    }
    return result;
}
