//  ************************************************************************************************
//
//  BornAgain: simulate and fit reflection and scattering
//
//! @file      GUI/coregui/mainwindow/mainwindow.h
//! @brief     Defines class MainWindow
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_GUI_COREGUI_MAINWINDOW_MAINWINDOW_H
#define BORNAGAIN_GUI_COREGUI_MAINWINDOW_MAINWINDOW_H

#include <QMainWindow>

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

class QProgressBar;
class QButtonGroup;
class QStackedLayout;
class QStatusBar;
class QToolButton;
class QVBoxLayout;
class LinkInstrumentManager;

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    enum ViewId { WELCOME, INSTRUMENT, SAMPLE, IMPORT, SIMULATION, JOB, SESSIONMODEL };

    explicit MainWindow();
    ~MainWindow();

    //! Returns the one and only instance of this class
    static MainWindow* instance();

    MaterialModel* materialModel();
    InstrumentModel* instrumentModel();
    SampleModel* sampleModel();
    RealDataModel* realDataModel();
    JobModel* jobModel();
    ApplicationModels* models();
    LinkInstrumentManager* linkInstrumentManager();

    QProgressBar* progressBar();
    QStatusBar* statusBar();

    ProjectManager* projectManager();
    UpdateNotifier* updateNotifier();

    QWidget* currentView() const;
    void setCurrentView(int viewId);

public slots:
    void onFocusRequest(int index);
    void openRecentProject();
    void onRunSimulationShortcut();
    void onSessionModelViewActive(bool isActive);

signals:
    void currentViewChanged(ViewId newView);

protected:
    void closeEvent(QCloseEvent* event);

private:
    void initApplication();
    void initProgressBar();
    void initViews();

    void readSettings();
    void writeSettings();
    void initConnections();
    void addView(ViewId id, const QIcon& icon, const QString& title, const QString& tooltip,
                 QWidget* view);
    QToolButton* createViewSelectionButton() const;

    //! Recalculate the size of the view selection buttons to show complete button text
    void updateViewSelectionButtonsGeometry() const;

    QProgressBar* m_progressBar;
    QButtonGroup* m_viewSelectionButtons;
    QStackedLayout* m_viewsStack;
    QVBoxLayout* m_viewSelectionButtonsLayout;
    QStatusBar* m_statusBar;

    ApplicationModels* m_applicationModels;
    LinkInstrumentManager* m_linkManager;
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

    //! Holds the one and only instance of this class
    static MainWindow* s_instance;
};

#endif // BORNAGAIN_GUI_COREGUI_MAINWINDOW_MAINWINDOW_H
