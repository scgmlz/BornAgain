// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/mainwindow/mainwindow.h
//! @brief     Defines class MainWindow
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_MAINWINDOW_MAINWINDOW_H
#define BORNAGAIN_GUI_COREGUI_MAINWINDOW_MAINWINDOW_H

#include "Wrap/WinDllMacros.h"
#include "fancymainwindow.h"

namespace Manhattan
{
class FancyTabWidget;
class ProgressBar;
} // namespace Manhattan

class WelcomeView;
class InstrumentView;
class SampleView;
class ImportDataView;
class SimulationView;
class JobView;
class SessionModelView;

class MaterialModel;
class SampleModel;
class InstrumentModel;
class RealDataModel;
class JobModel;
class ApplicationModels;
class ProjectManager;
class ActionManager;
class ToolTipDataBase;
class UpdateNotifier;

class BA_CORE_API_ MainWindow : public Manhattan::FancyMainWindow
{
    Q_OBJECT

public:
    enum ETabViewId { WELCOME, INSTRUMENT, SAMPLE, IMPORT, SIMULATION, JOB, MAXVIEWCOUNT };

    explicit MainWindow(QWidget* parent = nullptr);

    MaterialModel* materialModel();
    InstrumentModel* instrumentModel();
    SampleModel* sampleModel();
    RealDataModel* realDataModel();
    JobModel* jobModel();
    ApplicationModels* models();

    Manhattan::ProgressBar* progressBar();
    QStatusBar* statusBar();

    ProjectManager* projectManager();
    UpdateNotifier* updateNotifier();

public slots:
    void onFocusRequest(int index);
    void openRecentProject();
    void onRunSimulationShortcut();
    void onSessionModelViewActive(bool isActive);

protected:
    void closeEvent(QCloseEvent* event);

private:
    void initApplication();
    void initProgressBar();
    void initViews();

    void readSettings();
    void writeSettings();
    void initConnections();

    Manhattan::FancyTabWidget* m_tabWidget;
    Manhattan::ProgressBar* m_progressBar;

    ApplicationModels* m_applicationModels;
    ProjectManager* m_projectManager;
    ActionManager* m_actionManager;
    ToolTipDataBase* m_toolTipDataBase;
    UpdateNotifier* m_updateNotifier;

    WelcomeView* m_welcomeView;
    InstrumentView* m_instrumentView;
    SampleView* m_sampleView;
    ImportDataView* m_importDataView;
    SimulationView* m_simulationView;
    JobView* m_jobView;
    SessionModelView* m_sessionModelView;
};

#endif // BORNAGAIN_GUI_COREGUI_MAINWINDOW_MAINWINDOW_H
