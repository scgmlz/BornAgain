// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/SimulationOptionsItem.h
//! @brief     Defines class SimulationOptionsItem
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_MODELS_SIMULATIONOPTIONSITEM_H
#define BORNAGAIN_GUI_COREGUI_MODELS_SIMULATIONOPTIONSITEM_H

#include "GUI/coregui/Models/SessionItem.h"
#include <QMap>

//! The SimulationOptionsItem class holds simulation status (run policy, number of threads,
//! integration flag). Used in SimulationView to define job settings. When job is started,
//! item is copied to the job as a child.

class BA_CORE_API_ SimulationOptionsItem : public SessionItem
{
public:
    static const QString P_RUN_POLICY;
    static const QString P_NTHREADS;
    static const QString P_COMPUTATION_METHOD;
    static const QString P_MC_POINTS;
    static const QString P_FRESNEL_MATERIAL_METHOD;
    static const QString P_INCLUDE_SPECULAR_PEAK;

    explicit SimulationOptionsItem();

    int getNumberOfThreads() const;
    bool runImmediately() const;
    bool runInBackground() const;

    void setRunPolicy(const QString& policy);

    void setComputationMethod(const QString& name);
    QString getComputationMethod() const;

    int getNumberOfMonteCarloPoints() const;
    void setNumberOfMonteCarloPoints(int npoints);

    void setFresnelMaterialMethod(const QString& name);
    QString getFresnelMaterialMethod() const;

    void setIncludeSpecularPeak(const QString& name);
    QString getIncludeSpecularPeak() const;

private:
    QString runPolicy() const;
    QStringList getCPUUsageOptions();
    QStringList getRunPolicyNames();
    void updateComboItem(QString name, QStringList option_names);
    QMap<QString, int> m_text_to_nthreads;
};

#endif // BORNAGAIN_GUI_COREGUI_MODELS_SIMULATIONOPTIONSITEM_H
