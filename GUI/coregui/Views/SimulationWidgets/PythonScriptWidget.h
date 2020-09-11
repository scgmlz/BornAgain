// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/SimulationWidgets/PythonScriptWidget.h
//! @brief     Defines class PythonScriptWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_VIEWS_SIMULATIONWIDGETS_PYTHONSCRIPTWIDGET_H
#define BORNAGAIN_GUI_COREGUI_VIEWS_SIMULATIONWIDGETS_PYTHONSCRIPTWIDGET_H

#include "Wrap/WinDllMacros.h"
#include <QDialog>

class QToolBar;
class QTextEdit;
class WarningSign;
class MultiLayerItem;
class InstrumentItem;
class SimulationOptionsItem;

//! The PythonScriptWidget displays a python script which represents full simulation.
//! Part of SimulationSetupWidget

class BA_CORE_API_ PythonScriptWidget : public QDialog
{
    Q_OBJECT

public:
    PythonScriptWidget(QWidget* parent = 0);

    void generatePythonScript(const MultiLayerItem* sampleItem,
                              const InstrumentItem* instrumentItem,
                              const SimulationOptionsItem* optionItem = 0,
                              const QString& outputDir = "");

private slots:
    void onExportToFileButton();

private:
    QToolBar* m_toolBar;
    QTextEdit* m_textEdit;
    WarningSign* m_warningSign;
    QString m_outputDir;
};

#endif // BORNAGAIN_GUI_COREGUI_VIEWS_SIMULATIONWIDGETS_PYTHONSCRIPTWIDGET_H
