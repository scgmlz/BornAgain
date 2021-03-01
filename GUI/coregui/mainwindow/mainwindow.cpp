//  ************************************************************************************************
//
//  BornAgain: simulate and fit reflection and scattering
//
//! @file      GUI/coregui/mainwindow/mainwindow.cpp
//! @brief     Implements class MainWindow
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "GUI/coregui/mainwindow/mainwindow.h"
#include "GUI/coregui/Models/ApplicationModels.h"
#include "GUI/coregui/Models/JobModel.h"
#include "GUI/coregui/Views/ImportDataView.h"
#include "GUI/coregui/Views/ImportDataWidgets/LinkInstrumentManager.h"
#include "GUI/coregui/Views/InstrumentView.h"
#include "GUI/coregui/Views/JobView.h"
#include "GUI/coregui/Views/SampleView.h"
#include "GUI/coregui/Views/SessionModelView.h"
#include "GUI/coregui/Views/SimulationView.h"
#include "GUI/coregui/Views/WelcomeView.h"
#include "GUI/coregui/mainwindow/UpdateNotifier.h"
#include "GUI/coregui/mainwindow/actionmanager.h"
#include "GUI/coregui/mainwindow/mainwindow_constants.h"
#include "GUI/coregui/mainwindow/projectmanager.h"
#include "GUI/coregui/mainwindow/tooltipdatabase.h"
#include "GUI/coregui/utils/GUIHelpers.h"
#include "GUI/coregui/utils/hostosinfo.h"
#include <QAction>
#include <QApplication>
#include <QBoxLayout>
#include <QButtonGroup>
#include <QCloseEvent>
#include <QMessageBox>
#include <QProgressBar>
#include <QPushButton>
#include <QSettings>
#include <QStackedLayout>
#include <QStatusBar>
#include <QToolButton>

MainWindow* MainWindow::s_instance = nullptr;

MainWindow::MainWindow()
    : QMainWindow(nullptr)
    , m_progressBar(new QProgressBar)
    , m_viewSelectionButtons(new QButtonGroup(this))
    , m_viewsStack(new QStackedLayout)
    , m_viewSelectionButtonsLayout(new QVBoxLayout)
    , m_statusBar(new QStatusBar)
    , m_applicationModels(new ApplicationModels(this))
    , m_linkManager(new LinkInstrumentManager(this))
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

    s_instance = this;

    m_linkManager->setModels(instrumentModel(), realDataModel());

    QWidget* centralWidget = new QWidget(this);
    QHBoxLayout* mainLayout = new QHBoxLayout(centralWidget);
    mainLayout->setMargin(0);
    mainLayout->setSpacing(0);

    m_viewSelectionButtonsLayout->setMargin(0);
    m_viewSelectionButtonsLayout->setSpacing(0);

    auto fillerButton = createViewSelectionButton();
    fillerButton->setMinimumSize(5, 5);
    fillerButton->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
    fillerButton->setEnabled(false);
    m_viewSelectionButtonsLayout->insertWidget(-1, fillerButton);

#if QT_VERSION >= QT_VERSION_CHECK(5, 15, 0)
    connect(m_viewSelectionButtons, &QButtonGroup::idClicked, this, &MainWindow::setCurrentView);
#else
    connect(m_viewSelectionButtons, QOverload<int>::of(&QButtonGroup::buttonClicked), this,
            &MainWindow::setCurrentView);
#endif

    m_statusBar->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Fixed);

    QVBoxLayout* vlayout = new QVBoxLayout;
    vlayout->setMargin(0);
    vlayout->setSpacing(0);
    vlayout->addLayout(m_viewsStack);
    vlayout->addWidget(m_statusBar);

    mainLayout->addLayout(m_viewSelectionButtonsLayout);
    mainLayout->addLayout(vlayout);

    setCentralWidget(centralWidget);

    m_statusBar->hide();

    initApplication();
    readSettings();
    initProgressBar();
    initViews();
    initConnections();

    ASSERT(m_viewSelectionButtons->button(ViewId::WELCOME) != nullptr);
    m_viewSelectionButtons->button(ViewId::WELCOME)->setChecked(true);

    //    m_applicationModels->createTestSample();
    //    m_applicationModels->createTestJob();
    //    m_applicationModels->createTestRealData();
}

MainWindow::~MainWindow()
{
    s_instance = nullptr;
}

MainWindow* MainWindow::instance()
{
    return s_instance;
}

MaterialModel* MainWindow::materialModel()
{
    return models()->materialModel();
}

InstrumentModel* MainWindow::instrumentModel()
{
    return models()->instrumentModel();
}

SampleModel* MainWindow::sampleModel()
{
    return models()->sampleModel();
}

RealDataModel* MainWindow::realDataModel()
{
    return models()->realDataModel();
}

JobModel* MainWindow::jobModel()
{
    return models()->jobModel();
}

ApplicationModels* MainWindow::models()
{
    return m_applicationModels;
}

LinkInstrumentManager* MainWindow::linkInstrumentManager()
{
    return m_linkManager;
}

QProgressBar* MainWindow::progressBar()
{
    return m_progressBar;
}

QStatusBar* MainWindow::statusBar()
{
    return m_statusBar;
}

ProjectManager* MainWindow::projectManager()
{
    return m_projectManager;
}

UpdateNotifier* MainWindow::updateNotifier()
{
    return m_updateNotifier;
}

QWidget* MainWindow::currentView() const
{
    return m_viewsStack->currentWidget();
}

void MainWindow::setCurrentView(int viewId)
{
    if (m_viewsStack->currentIndex() != viewId) {
        m_viewsStack->setCurrentIndex(viewId);
        emit currentViewChanged(ViewId(viewId));
    }
}

void MainWindow::onFocusRequest(int index)
{
    m_viewSelectionButtons->button(index)->click();
}

void MainWindow::openRecentProject()
{
    if (const QAction* action = qobject_cast<const QAction*>(sender())) {
        QString file = action->data().value<QString>();
        m_projectManager->openProject(file);
    }
}

void MainWindow::onRunSimulationShortcut()
{
    // This clearFocus is needed for the propagation of the current editor value,
    // since the runSimulation method will only change focus after finishing the simulation
    if (auto widget = QApplication::focusWidget())
        widget->clearFocus();
    m_simulationView->onRunSimulationShortcut();
}

//! Inserts/removes developers SessionModelView on the left tabbar.
void MainWindow::onSessionModelViewActive(bool isActive)
{
    auto btn = m_viewSelectionButtons->button(ViewId::SESSIONMODEL);
    ASSERT(btn != nullptr);
    if (btn == nullptr)
        return;

    if (!isActive && m_viewsStack->currentIndex() == SESSIONMODEL)
        m_viewSelectionButtons->buttons().first()->click();

    btn->setEnabled(isActive);
    btn->setVisible(isActive);
}

void MainWindow::closeEvent(QCloseEvent* event)
{
    if (jobModel()->hasUnfinishedJobs()) {
        QMessageBox::warning(this, "Can't quit the application.",
                             "Can't quit the application while jobs are running.\n"
                             "Cancel running jobs or wait until they are completed.");
        event->ignore();
        return;
    }
    if (m_projectManager->closeCurrentProject()) {
        writeSettings();
        event->accept();
    } else {
        event->ignore();
    }
}

void MainWindow::initApplication()
{
    QCoreApplication::setApplicationName(QLatin1String(Constants::APPLICATION_NAME));
    QCoreApplication::setApplicationVersion(GUIHelpers::getBornAgainVersionString());
    QCoreApplication::setOrganizationName(QLatin1String(Constants::APPLICATION_NAME));

    if (!GUI_OS_Utils::HostOsInfo::isMacHost())
        QApplication::setWindowIcon(QIcon(":/images/BornAgain.ico"));

    setDockNestingEnabled(true);
    setAcceptDrops(true);

    setCorner(Qt::BottomLeftCorner, Qt::LeftDockWidgetArea);
    setCorner(Qt::BottomRightCorner, Qt::BottomDockWidgetArea);
}

void MainWindow::initProgressBar()
{
    m_progressBar->hide();
    m_progressBar->setTextVisible(false);
    m_progressBar->setFixedHeight(QApplication::fontMetrics().boundingRect("M").height());
    m_progressBar->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Fixed);
    m_viewSelectionButtonsLayout->addWidget(m_progressBar);
}

void MainWindow::initViews()
{
    m_welcomeView = new WelcomeView(this);
    m_instrumentView = new InstrumentView(this);
    m_sampleView = new SampleView(this);
    m_importDataView = new ImportDataView(this);
    m_simulationView = new SimulationView(this);
    m_jobView = new JobView(this);
    m_sessionModelView = new SessionModelView(this);

    addView(ViewId::WELCOME, QIcon(":/images/main_welcomeview.svg"), "Welcome",
            "Switch to Welcome View", m_welcomeView);

    addView(ViewId::INSTRUMENT, QIcon(":/images/main_instrumentview.svg"), "Instrument",
            "Define the beam and the  detector", m_instrumentView);

    addView(ViewId::SAMPLE, QIcon(":/images/main_sampleview.svg"), "Sample", "Build the sample",
            m_sampleView);

    addView(ViewId::IMPORT, QIcon(":/images/main_importview.svg"), "Data",
            "Import intensity data to fit", m_importDataView);

    addView(ViewId::SIMULATION, QIcon(":/images/main_simulationview.svg"), "Simulation",
            "Run simulation", m_simulationView);

    addView(ViewId::JOB, QIcon(":/images/main_jobview.svg"), "Jobs",
            "Switch to see job results, tune parameters real time,\nfit the data", m_jobView);

    addView(ViewId::SESSIONMODEL, QIcon(":/images/main_sessionmodel.svg"), "Models", "",
            m_sessionModelView);

    // enabling technical view
    QSettings settings;
    settings.beginGroup(Constants::S_SESSIONMODELVIEW);
    onSessionModelViewActive(settings.value(Constants::S_VIEWISACTIVE, false).toBool());
    settings.endGroup();
}

void MainWindow::readSettings()
{
    QSettings settings;
    if (settings.childGroups().contains(Constants::S_MAINWINDOW)) {
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
    connect(m_jobView, &JobView::focusRequest, this, &MainWindow::onFocusRequest);
}

void MainWindow::addView(ViewId id, const QIcon& icon, const QString& title, const QString& tooltip,
                         QWidget* view)
{
    QToolButton* btn = createViewSelectionButton();
    m_viewSelectionButtonsLayout->insertWidget(id, btn);

    btn->setText(title);
    btn->setToolTip(tooltip);
    btn->setIcon(icon);
    m_viewSelectionButtons->addButton(btn, id);

    updateViewSelectionButtonsGeometry();

    m_viewsStack->insertWidget(id, view);
}

void MainWindow::updateViewSelectionButtonsGeometry() const
{
    if (m_viewSelectionButtons->buttons().isEmpty())
        return;

    const QFontMetrics fontMetrics = m_viewSelectionButtons->buttons().first()->fontMetrics();

    // Find the maximum text extents
    int maxTextWidth = 0;
    int maxTextHeight = 0;
    for (auto b : m_viewSelectionButtons->buttons()) {
        const auto r = fontMetrics.boundingRect(b->text());
        maxTextWidth = std::max(maxTextWidth, r.width());
        maxTextHeight = std::max(maxTextHeight, r.height());
    }

    // calculate the button extent by width (width == height!). Ensure an extent of 70 for normal
    // DPI devices (legacy value)
    const int margin = fontMetrics.boundingRect("M").width();
    const int buttonExtent = std::max(70, maxTextWidth + 2 * margin);

    // calculate the icon extent by height (width == height!)
    const int iconExtent = buttonExtent - margin - maxTextHeight;

    // set new values in all buttons
    for (auto b : m_viewSelectionButtons->buttons()) {
        b->setFixedSize(buttonExtent, buttonExtent);
        b->setIconSize({iconExtent, iconExtent});
    }
    // set fixed width in filler and progress bar
    auto filler = m_viewSelectionButtonsLayout->itemAt(m_viewSelectionButtons->buttons().size());
    if (filler)
        if (auto fillerBtn = dynamic_cast<QToolButton*>(filler->widget()); fillerBtn)
            fillerBtn->setFixedWidth(buttonExtent);

    m_progressBar->setFixedWidth(buttonExtent);
}

QToolButton* MainWindow::createViewSelectionButton() const
{

    const QString viewSelectionButtonStyle =
        "QToolButton { border: none; color: white; background-color: qlineargradient(x1: 0, "
        "y1: 0, x2: 1, y2: 0, stop : 0 #153b4c, stop : 1 #347a9c);}        "
        "QToolButton:pressed { "
        " color: black; background-color: qlineargradient(x1: 0, y1: 0, x2: 1, y2: 0, stop: 0 "
        "#97a8b0, stop: "
        "1 #dae7ed); }"
        "QToolButton:hover { "
        " color: white; background-color: qlineargradient(x1: 0, y1: 0, x2: 1, y2: 0, stop: 0 "
        "#254b5c, stop: 1 #448aac); }"
        "QToolButton:checked { "
        " color: black; background-color: qlineargradient(x1: 0, y1: 0, x2: 1, y2: 0, stop: 0 "
        "#97a8b0, stop: "
        "1 #dae7ed);"
        "} ";

    QToolButton* btn = new QToolButton;
    btn->setCheckable(true);
    btn->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    btn->setStyleSheet(viewSelectionButtonStyle);
    return btn;
}
