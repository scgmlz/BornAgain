// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/mainwindow/mainwindow.cpp
//! @brief     Implements class MainWindow
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "mainwindow.h"
#include "ApplicationModels.h"
#include "GUIHelpers.h"
#include "ImportDataView.h"
#include "InstrumentView.h"
#include "JobModel.h"
#include "JobView.h"
#include "SampleView.h"
#include "SessionModelView.h"
#include "SimulationView.h"
#include "UpdateNotifier.h"
#include "WelcomeView.h"
#include "aboutapplicationdialog.h"
#include "actionmanager.h"
#include "fancytabwidget.h"
#include "hostosinfo.h"
#include "mainwindow_constants.h"
#include "manhattanstyle.h"
#include "progressbar.h"
#include "projectmanager.h"
#include "stylehelper.h"
#include "tooltipdatabase.h"
#include <QApplication>
#include <QCloseEvent>
#include <QMessageBox>
#include <QSettings>

MainWindow::MainWindow(QWidget *parent)
    : Manhattan::FancyMainWindow(parent)
    , m_tabWidget(new Manhattan::FancyTabWidget(this))
    , m_progressBar(new Manhattan::ProgressBar(this))
    , m_applicationModels(new ApplicationModels(this))
    , m_projectManager(new ProjectManager(this))
    , m_actionManager(new ActionManager(this))
    , m_toolTipDataBase(new ToolTipDataBase(this))
    , m_updateNotifier(new UpdateNotifier(this))
    , m_welcomeView(0)
    , m_instrumentView(0)
    , m_sampleView(0)
    , m_importDataView(0)
    , m_simulationView(0)
    , m_jobView(0)
    , m_sessionModelView(0)
{
    initApplication();
    readSettings();
    initProgressBar();
    initViews();
    initConnections();

//    m_applicationModels->createTestSample();
//    m_applicationModels->createTestJob();
//    m_applicationModels->createTestRealData();
}

MaterialModel *MainWindow::materialModel()
{
    return models()->materialModel();
}

InstrumentModel *MainWindow::instrumentModel()
{
    return models()->instrumentModel();
}

SampleModel *MainWindow::sampleModel()
{
    return models()->sampleModel();
}

RealDataModel *MainWindow::realDataModel()
{
    return models()->realDataModel();
}

JobModel *MainWindow::jobModel()
{
    return models()->jobModel();
}

ApplicationModels *MainWindow::models()
{
    return m_applicationModels;
}

Manhattan::ProgressBar *MainWindow::progressBar()
{
    return m_progressBar;
}

QStatusBar *MainWindow::statusBar()
{
    return m_tabWidget->statusBar();
}

ActionManager *MainWindow::getActionManager()
{
    return m_actionManager;
}

ProjectManager *MainWindow::projectManager()
{
    return m_projectManager;
}

UpdateNotifier *MainWindow::getUpdateNotifier()
{
    return m_updateNotifier;
}

//! updates views which depend on others
void MainWindow::onChangeTabWidget(int index)
{
    if(index == WELCOME)
    {
        m_welcomeView->updateRecentProjectPanel();
    }
    else if (index == INSTRUMENT) {
        m_instrumentView->updateView();
    }
    else if(index == SIMULATION) {
        m_simulationView->updateSimulationViewElements();
    }
}

void MainWindow::onFocusRequest(int index)
{
    m_tabWidget->setCurrentIndex(index);
}

void MainWindow::openRecentProject()
{
    if (const QAction *action = qobject_cast<const QAction*>(sender())) {
        QString file = action->data().value<QString>();
        qDebug() << "MainWindow::openRecentProject() -> " << file;
        m_projectManager->openProject(file);
    }
}

void MainWindow::onRunSimulationShortcut()
{
    m_simulationView->onRunSimulationShortcut();
}

void MainWindow::onAboutApplication()
{
    AboutApplicationDialog dialog(this);
    dialog.exec();
}

//! Inserts/removes developers SessionModelView on the left fancy tabbar.
//! This SessionModelView will be known for the tab under MAXVIEWCOUNT id (so it is the last one)
void MainWindow::onSessionModelViewActive(bool isActive)
{
    qDebug() << "MainWindow::onSessionModelViewActive" << isActive;

    if(isActive) {
        if(m_sessionModelView)
            return;

        m_sessionModelView = new SessionModelView(this);
        m_tabWidget->insertTab(MAXVIEWCOUNT, m_sessionModelView, QIcon(":/images/main_sessionmodel.svg"), "Models");

    } else {
        if(!m_sessionModelView)
            return;

        if(m_tabWidget->currentIndex() == MAXVIEWCOUNT)
            m_tabWidget->setCurrentIndex(WELCOME);

        m_tabWidget->removeTab(MAXVIEWCOUNT);
        delete m_sessionModelView;
        m_sessionModelView = 0;
        m_tabWidget->update();
    }

}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if(jobModel()->hasUnfinishedJobs()) {
        QMessageBox::warning(this, "Can't quit the application.",
                             "Can't quit the application while jobs are running.\n"
                             "Cancel running jobs or wait until they are completed.");
        event->ignore();
        return;
    }

    if(m_projectManager->closeCurrentProject()) {
        writeSettings();
        event->accept();
    } else {
        event->ignore();
    }
}

//! Launch update notifier after main window appears
void MainWindow::showEvent(QShowEvent *event)
{
    QWidget::showEvent( event );
    QTimer::singleShot(100, m_updateNotifier, SLOT(askForUpdates()));
}

void MainWindow::initApplication()
{
    QCoreApplication::setApplicationName(QLatin1String(Constants::APPLICATION_NAME));
    QCoreApplication::setApplicationVersion(GUIHelpers::getBornAgainVersionString());
    QCoreApplication::setOrganizationName(QLatin1String(Constants::APPLICATION_NAME));

    if (!GUI_OS_Utils::HostOsInfo::isMacHost())
        QApplication::setWindowIcon(QIcon(":/images/BornAgain.ico"));

    QString baseName = QApplication::style()->objectName();
    qApp->setStyle(new ManhattanStyle(baseName));
    Manhattan::Utils::StyleHelper::setBaseColor(QColor(Constants::MAIN_THEME_COLOR));

    setDockNestingEnabled(true);
    setAcceptDrops(true);

    setCorner(Qt::BottomLeftCorner, Qt::LeftDockWidgetArea);
    setCorner(Qt::BottomRightCorner, Qt::BottomDockWidgetArea);
}

void MainWindow::initProgressBar()
{
    m_tabWidget->addBottomCornerWidget(m_progressBar);
    m_progressBar->hide();
}

void MainWindow::initViews()
{
    m_welcomeView = new WelcomeView(this);
    m_instrumentView = new InstrumentView(this);
    m_sampleView = new SampleView(this);
    m_importDataView = new ImportDataView(this);
    m_simulationView = new SimulationView(this);

    m_jobView = new JobView(this);
//    TestView *testView = new TestView(this);
//    m_sessionModelView = new SessionModelView(this);
//    TestFitWidgets *testFitWidgets = new TestFitWidgets(this);
    //m_fitView = new FitView(this);

    m_tabWidget->insertTab(WELCOME, m_welcomeView, QIcon(":/images/main_welcomeview.svg"), "Welcome");
    m_tabWidget->setTabToolTip(WELCOME, QStringLiteral("Switch to Welcome View"));

    m_tabWidget->insertTab(INSTRUMENT, m_instrumentView, QIcon(":/images/main_instrumentview.svg"), "Instrument");
    m_tabWidget->setTabToolTip(INSTRUMENT, QStringLiteral("Define the beam and the detector"));

    m_tabWidget->insertTab(SAMPLE, m_sampleView, QIcon(":/images/main_sampleview.svg"), "Sample");
    m_tabWidget->setTabToolTip(SAMPLE, QStringLiteral("Build the sample"));

    m_tabWidget->insertTab(IMPORT, m_importDataView, QIcon(":/images/main_importview.svg"), "Import");
    m_tabWidget->setTabToolTip(IMPORT, QStringLiteral("Import intensity data to fit"));

    m_tabWidget->insertTab(SIMULATION, m_simulationView, QIcon(":/images/main_simulationview.svg"), "Simulation");
    m_tabWidget->setTabToolTip(SIMULATION, QStringLiteral("Run simulation"));

    m_tabWidget->insertTab(JOB, m_jobView, QIcon(":/images/main_jobview.svg"), "Jobs");
    m_tabWidget->setTabToolTip(JOB, QStringLiteral("Switch to see job results, tune parameters real time,\nfit the data"));

    //m_tabWidget->insertTab(FIT, m_fitView, QIcon(":/images/main_jobview.svg"), "Fit");
    //m_tabWidget->insertTab(MODELVIEW, m_sessionModelView, QIcon(":/images/main_sessionmodel.svg"), "Models");
//    m_tabWidget->insertTab(TESTVIEW, testView, QIcon(":/images/main_jobview.svg"), "TestView");

    m_tabWidget->setCurrentIndex(WELCOME);

    // enabling technical view
    QSettings settings;
    settings.beginGroup(Constants::S_SESSIONMODELVIEW);
    onSessionModelViewActive(settings.value(Constants::S_VIEWISACTIVE, false).toBool());
    settings.endGroup();

    setCentralWidget(m_tabWidget);
}

void MainWindow::readSettings()
{
    QSettings settings;
    if(settings.childGroups().contains(Constants::S_MAINWINDOW)) {
        settings.beginGroup(Constants::S_MAINWINDOW);
        resize(settings.value(Constants::S_WINDOWSIZE, QSize(400, 400)).toSize());
        move(settings.value(Constants::S_WINDOWPOSITION, QPoint(200, 200)).toPoint());
        settings.endGroup();
    }
    m_projectManager->readSettings();
}

void MainWindow::writeSettings()
{
    QSettings settings;
    settings.beginGroup(Constants::S_MAINWINDOW);
    settings.setValue(Constants::S_WINDOWSIZE, size());
    settings.setValue(Constants::S_WINDOWPOSITION, pos());
    settings.endGroup();
    m_projectManager->writeSettings();
    settings.sync();
}

void MainWindow::initConnections()
{
    connect(m_tabWidget, SIGNAL(currentChanged(int)), this, SLOT(onChangeTabWidget(int)));
    connect(m_jobView, SIGNAL(focusRequest(int)), this, SLOT(onFocusRequest(int)));
    connect(m_updateNotifier, SIGNAL(onUpdateNotification(const QString &)),
            m_welcomeView, SLOT(setNotificationText(const QString &)));
}
