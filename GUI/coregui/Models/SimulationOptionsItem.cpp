// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/SimulationOptionsItem.cpp
//! @brief     Defines class SimulationOptionsItem
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/coregui/Models/SimulationOptionsItem.h"
#include "GUI/coregui/Models/ComboProperty.h"
#include <thread>

namespace
{

QStringList getRunPolicyTooltips()
{
    QStringList result;
    result.append("Start simulation immediately, switch to Jobs view automatically when completed");
    result.append("Start simulation immediately, do not switch to Jobs view when completed");
    return result;
}

const QString tooltip_runpolicy = "Defines run policy for the simulation";
const QString tooltip_nthreads = "Defines number of threads to use for the simulation.";
const QString tooltip_computation =
    "Defines computation method (analytical or Monte-Carlo integration)";
const QString tooltip_ambientmaterial =
    "Define if the material used for Fresnel calculations should be the ambient layer "
    "material or the average material of the layer and the particles it contains";
const QString tooltip_specularpeak =
    "Defines if the specular peak should be included in the simulation result";

} // namespace

const QString SimulationOptionsItem::P_RUN_POLICY = "Run Policy";
const QString SimulationOptionsItem::P_NTHREADS = "Number of Threads";
const QString SimulationOptionsItem::P_COMPUTATION_METHOD = "Computation method";
const QString SimulationOptionsItem::P_MC_POINTS = "Number of MC points";
const QString SimulationOptionsItem::P_FRESNEL_MATERIAL_METHOD =
    "Material for Fresnel calculations";
const QString SimulationOptionsItem::P_INCLUDE_SPECULAR_PEAK = "Include specular peak";

SimulationOptionsItem::SimulationOptionsItem() : SessionItem("SimulationOptions")
{

    ComboProperty policy;
    policy << getRunPolicyNames();
    policy.setToolTips(getRunPolicyTooltips());
    addProperty(P_RUN_POLICY, policy.variant())->setToolTip(tooltip_runpolicy);

    ComboProperty nthreads;
    nthreads << getCPUUsageOptions();
    addProperty(P_NTHREADS, nthreads.variant())->setToolTip(tooltip_nthreads);

    ComboProperty computationMethod;
    computationMethod << "Analytical"
                      << "Monte-Carlo Integration";
    addProperty(P_COMPUTATION_METHOD, computationMethod.variant())->setToolTip(tooltip_computation);

    addProperty(P_MC_POINTS, 100)->setEnabled(false);

    ComboProperty averageLayerMaterials;
    averageLayerMaterials << "Ambient Layer Material"
                          << "Average Layer Material";
    addProperty(P_FRESNEL_MATERIAL_METHOD, averageLayerMaterials.variant())
        ->setToolTip(tooltip_ambientmaterial);

    ComboProperty includeSpecularPeak;
    includeSpecularPeak << "No"
                        << "Yes";
    addProperty(P_INCLUDE_SPECULAR_PEAK, includeSpecularPeak.variant())
        ->setToolTip(tooltip_specularpeak);

    mapper()->setOnPropertyChange([this](const QString& name) {
        if (name == P_COMPUTATION_METHOD && isTag(P_MC_POINTS)) {
            ComboProperty combo = getItemValue(P_COMPUTATION_METHOD).value<ComboProperty>();

            if (combo.getValue() == "Analytical") {
                getItem(P_MC_POINTS)->setEnabled(false);

            } else {
                getItem(P_MC_POINTS)->setEnabled(true);
            }
        } else if (name == P_NTHREADS) {
            updateComboItem(P_NTHREADS, getCPUUsageOptions());
        } else if (name == P_RUN_POLICY) {
            updateComboItem(P_RUN_POLICY, getRunPolicyNames());
        }
    });
}

int SimulationOptionsItem::getNumberOfThreads() const
{
    ComboProperty combo = getItemValue(P_NTHREADS).value<ComboProperty>();
    return m_text_to_nthreads[combo.getValue()];
}

bool SimulationOptionsItem::runImmediately() const
{
    return runPolicy() == "Immediately";
}

bool SimulationOptionsItem::runInBackground() const
{
    return runPolicy() == "In background";
}

void SimulationOptionsItem::setRunPolicy(const QString& policy)
{
    ComboProperty combo = getItemValue(P_RUN_POLICY).value<ComboProperty>();
    combo.setValue(policy);
    setItemValue(P_RUN_POLICY, combo.variant());
}

void SimulationOptionsItem::setComputationMethod(const QString& name)
{
    ComboProperty combo = getItemValue(P_COMPUTATION_METHOD).value<ComboProperty>();
    combo.setValue(name);
    setItemValue(P_COMPUTATION_METHOD, combo.variant());
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

void SimulationOptionsItem::setFresnelMaterialMethod(const QString& name)
{
    ComboProperty combo = getItemValue(P_FRESNEL_MATERIAL_METHOD).value<ComboProperty>();
    combo.setValue(name);
    setItemValue(P_FRESNEL_MATERIAL_METHOD, combo.variant());
}

QString SimulationOptionsItem::getFresnelMaterialMethod() const
{
    ComboProperty combo = getItemValue(P_FRESNEL_MATERIAL_METHOD).value<ComboProperty>();
    return combo.getValue();
}

void SimulationOptionsItem::setIncludeSpecularPeak(const QString& name)
{
    ComboProperty combo = getItemValue(P_INCLUDE_SPECULAR_PEAK).value<ComboProperty>();
    combo.setValue(name);
    setItemValue(P_INCLUDE_SPECULAR_PEAK, combo.variant());
}

QString SimulationOptionsItem::getIncludeSpecularPeak() const
{
    ComboProperty combo = getItemValue(P_INCLUDE_SPECULAR_PEAK).value<ComboProperty>();
    return combo.getValue();
}

QString SimulationOptionsItem::runPolicy() const
{
    ComboProperty combo = getItemValue(P_RUN_POLICY).value<ComboProperty>();
    return combo.getValue();
}

//! returns list with number of threads to select
QStringList SimulationOptionsItem::getCPUUsageOptions()
{
    m_text_to_nthreads.clear();
    QStringList result;
    int nthreads = static_cast<int>(std::thread::hardware_concurrency());
    for (int i = nthreads; i > 0; i--) {
        QString str;
        if (i == nthreads) {
            str = QString("Max (%1 threads)").arg(QString::number(i));
        } else if (i == 1) {
            str = QString("%1 thread").arg(QString::number(i));
        } else {
            str = QString("%1 threads").arg(QString::number(i));
        }
        result.append(str);
        m_text_to_nthreads[str] = i;
    }
    return result;
}

QStringList SimulationOptionsItem::getRunPolicyNames()
{
    QStringList result;
    result << "Immediately"
           << "In background";
    return result;
}

void SimulationOptionsItem::updateComboItem(QString name, QStringList option_names)
{
    ComboProperty combo = getItemValue(name).value<ComboProperty>();
    if (combo.getValues().size() != option_names.size()) {
        auto p_item = getItem(name);
        auto selected_value = combo.getValue();
        ComboProperty new_combo;
        new_combo << option_names;
        if (new_combo.getValues().contains(selected_value))
            new_combo.setValue(selected_value);
        p_item->setValue(new_combo.variant());
    }
}
