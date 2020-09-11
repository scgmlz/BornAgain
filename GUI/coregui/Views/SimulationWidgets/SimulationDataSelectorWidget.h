// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/SimulationWidgets/SimulationDataSelectorWidget.h
//! @brief     Defines class SimulationDataSelectorWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_VIEWS_SIMULATIONWIDGETS_SIMULATIONDATASELECTORWIDGET_H
#define BORNAGAIN_GUI_COREGUI_VIEWS_SIMULATIONWIDGETS_SIMULATIONDATASELECTORWIDGET_H

#include "Wrap/WinDllMacros.h"
#include <QWidget>

class ApplicationModels;
class QComboBox;
class MultiLayerItem;
class InstrumentItem;
class RealDataItem;

//! The SimulationDataSelectorWidget class represents widget to select instrument, sample and
//! real data. Located at the top of SimulationView.

class BA_CORE_API_ SimulationDataSelectorWidget : public QWidget
{
    Q_OBJECT

public:
    SimulationDataSelectorWidget(QWidget* parent = 0);

    void setApplicationModels(ApplicationModels* applicationModels);

    const MultiLayerItem* selectedMultiLayerItem() const;
    const InstrumentItem* selectedInstrumentItem() const;
    const RealDataItem* selectedRealDataItem() const;

    void updateViewElements();

private:
    int selectedInstrumentIndex() const;
    int selectedSampleIndex() const;
    int selectedRealDataIndex() const;
    void updateSelection(QComboBox* comboBox, QStringList itemList, bool allow_none = false);

    QComboBox* m_instrumentCombo;
    QComboBox* m_sampleCombo;
    QComboBox* m_realDataCombo;
    ApplicationModels* m_applicationModels;
};

#endif // BORNAGAIN_GUI_COREGUI_VIEWS_SIMULATIONWIDGETS_SIMULATIONDATASELECTORWIDGET_H
