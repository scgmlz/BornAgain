// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/JobItem.h
//! @brief     Defines class JobItem
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_MODELS_JOBITEM_H
#define BORNAGAIN_GUI_COREGUI_MODELS_JOBITEM_H

#include "GUI/coregui/Models/SessionItem.h"

class DataItem;
class Data1DViewItem;
class FitParameterContainerItem;
class FitSuiteItem;
class InstrumentItem;
class IntensityDataItem;
class MaterialItemContainer;
class MultiLayerItem;
class ParameterContainerItem;
class RealDataItem;
class Simulation;
class SimulationOptionsItem;

class BA_CORE_API_ JobItem : public SessionItem
{

public:
    static const QString P_IDENTIFIER;
    static const QString P_SAMPLE_NAME;
    static const QString P_INSTRUMENT_NAME;
    static const QString P_WITH_FITTING;
    static const QString P_STATUS;
    static const QString P_BEGIN_TIME;
    static const QString P_END_TIME;
    static const QString P_DURATION;
    static const QString P_COMMENTS;
    static const QString P_PROGRESS;
    static const QString P_PRESENTATION_TYPE;
    static const QString T_SAMPLE;
    static const QString T_MATERIAL_CONTAINER;
    static const QString T_INSTRUMENT;
    static const QString T_OUTPUT;
    static const QString T_REALDATA;
    static const QString T_DATAVIEW;
    static const QString T_PARAMETER_TREE;
    static const QString T_SIMULATION_OPTIONS;
    static const QString T_FIT_SUITE;

    JobItem();

    QString getIdentifier() const;
    void setIdentifier(const QString& identifier);

    IntensityDataItem* intensityDataItem();
    DataItem* dataItem();

    QString getStatus() const;
    void setStatus(const QString& status);

    bool isIdle() const;
    bool isRunning() const;
    bool isCompleted() const;
    bool isCanceled() const;
    bool isFailed() const;
    bool isValidForFitting();

    void setBeginTime(const QString& begin_time);

    void setEndTime(const QString& end_time);

    void setDuration(int duration);

    QString getComments() const;
    void setComments(const QString& comments);

    int getProgress() const;
    void setProgress(int progress);

    bool runImmediately() const;
    bool runInBackground() const;

    MultiLayerItem* multiLayerItem();

    InstrumentItem* instrumentItem();

    SimulationOptionsItem* simulationOptionsItem();

    void setResults(const Simulation* simulation);

    FitSuiteItem* fitSuiteItem();
    ParameterContainerItem* parameterContainerItem();
    const ParameterContainerItem* parameterContainerItem() const;

    FitParameterContainerItem* fitParameterContainerItem();
    RealDataItem* realDataItem();

    const MaterialItemContainer* materialContainerItem() const;

    Data1DViewItem* dataItemView();

private:
    void updateIntensityDataFileName();
    const SimulationOptionsItem* simulationOptionsItem() const;
};

#endif // BORNAGAIN_GUI_COREGUI_MODELS_JOBITEM_H
