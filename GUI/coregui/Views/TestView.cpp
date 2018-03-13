// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/TestView.cpp
//! @brief     Implements class TestView
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "TestView.h"
#include "AccordionWidget.h"
#include "JobModel.h"
#include "JobItem.h"
#include "MaskEditor.h"
#include "MaterialEditor.h"
#include "MinimizerItem.h"
#include "MinimizerSettingsWidget.h"
#include "ApplicationModels.h"
#include "SampleModel.h"
#include "SpecularDataItem.h"
#include "SpecularDataWidget.h"
#include "TestComponentView.h"
#include "mainwindow.h"
#include <QTreeView>

#ifdef BORNAGAIN_OPENGL
#include "RealSpaceWidget.h"
#endif

#include <QCheckBox>
#include <QLineEdit>

namespace {
// These functions are required for testing purposes only
// They must be removed after completion of
// SpecularDataWidget
double getTestValue(size_t bin);
SpecularDataItem* fillTestItem(SessionItem* item);
}

TestView::TestView(MainWindow *mainWindow)
    : QWidget(mainWindow)
    , m_mainWindow(mainWindow)
{
//    test_ComponentProxyModel();
//    test_MaterialEditor();
//    test_MinimizerSettings();
//    test_AccordionWidget();
//    test_RunFitWidget();
    test_ba3d();
//    test_specular_data_widget();
}

void TestView::test_ComponentProxyModel()
{
    auto layout = new QHBoxLayout();
    layout->setMargin(0);
    layout->setSpacing(0);

    layout->addWidget(new TestComponentView(m_mainWindow));

    setLayout(layout);
}


void TestView::test_MaterialEditor()
{
    MaterialEditor *materialEditor = new MaterialEditor(m_mainWindow->materialModel());
    QVBoxLayout *layout = new QVBoxLayout;
    layout->setMargin(0);
    layout->setSpacing(0);
    layout->addWidget(materialEditor);
    setLayout(layout);
}

void TestView::test_MinimizerSettings()
{
    MinimizerSettingsWidget *widget = new MinimizerSettingsWidget;
    QVBoxLayout *layout = new QVBoxLayout;
    layout->setMargin(0);
    layout->setSpacing(0);
    layout->addWidget(widget);
    setLayout(layout);

    SessionModel* model = new SessionModel("TempModel", this);
    MinimizerContainerItem *minimizerItem = dynamic_cast<MinimizerContainerItem *>(
                model->insertNewItem(Constants::MinimizerContainerType));
    widget->setItem(minimizerItem);

}

void TestView::test_AccordionWidget()
{
    AccordionWidget *myAccordion = new AccordionWidget();
    myAccordion->setMultiActive(true);
    // add the Accordion to your layout
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(myAccordion);
    setLayout(layout);

    // add a content pane with a header
    int firstPaneIndex = myAccordion->addContentPane("My first content pane");
    // make sure our content pane was added
    if (firstPaneIndex != -1) {
        // get a QFrame* from the Content Pane. This is where we place our content
        QFrame *contentFrame = myAccordion->getContentPane(firstPaneIndex)->getContentFrame();
        // give the QFrame a QLayout
        contentFrame->setLayout(new QVBoxLayout());
        // add a simpel QLabel to the frame
        contentFrame->layout()->addWidget(new QLabel("Hello Cute World!!!"));
    }

    // add a content pane with a header
    int secondPaneIndex = myAccordion->addContentPane("Basic settings");
    // make sure our content pane was added
    if (secondPaneIndex != -1) {
        // get a QFrame* from the Content Pane. This is where we place our content
        QFrame *contentFrame = myAccordion->getContentPane(secondPaneIndex)->getContentFrame();
        // give the QFrame a QLayout
        contentFrame->setLayout(new QVBoxLayout());
        // add a simpel QLabel to the frame
        QLineEdit *led = new QLineEdit();
        QLineEdit *led2 = new QLineEdit();
        contentFrame->layout()->addWidget(new QLabel("Name:"));
        contentFrame->layout()->addWidget(led);
        contentFrame->layout()->addWidget(new QLabel("Living place:"));
        contentFrame->layout()->addWidget(led2);
    }

    // add a content pane with a header
    int third = myAccordion->addContentPane("Advanced");
    // make sure our content pane was added
    if (third != -1) {
        // get a QFrame* from the Content Pane. This is where we place our content
        myAccordion->getContentPane(third)->setMaximumHeight(500);
        QFrame *contentFrame = myAccordion->getContentPane(third)->getContentFrame();
        contentFrame->setMaximumHeight(500);
        // give the QFrame a QLayout
        contentFrame->setLayout(new QVBoxLayout());
        // add a simpel QLabel to the frame
        QCheckBox *cb = new QCheckBox();
        cb->setText("Option 1");
        QCheckBox *cb2 = new QCheckBox();
        cb2->setText("Option 2");
        QCheckBox *cb3 = new QCheckBox();
        cb3->setText("Option 3");
        QCheckBox *cb4 = new QCheckBox();
        cb4->setText("Option 4");
        QCheckBox *cb5 = new QCheckBox();
        cb5->setText("Option 5");
        QCheckBox *cb6 = new QCheckBox();
        cb6->setText("Option 6");
        QCheckBox *cb7 = new QCheckBox();
        cb7->setText("Option 7");
        contentFrame->layout()->addWidget(cb);
        contentFrame->layout()->addWidget(cb2);
        contentFrame->layout()->addWidget(cb3);
        contentFrame->layout()->addWidget(cb4);
        contentFrame->layout()->addWidget(cb5);
        contentFrame->layout()->addWidget(cb6);
        contentFrame->layout()->addWidget(cb7);

    }
}

void TestView::test_ba3d()
{
    QVBoxLayout *layout = new QVBoxLayout;
    layout->setMargin(0);
    layout->setSpacing(0);
#ifdef BORNAGAIN_OPENGL
    RealSpaceWidget* widget = new RealSpaceWidget;
    widget->setModel(m_mainWindow->sampleModel());
    layout->addWidget(widget);
#endif
    setLayout(layout);

}

void TestView::test_specular_data_widget()
{
    SessionModel* tempModel = new SessionModel("Test", this);
    auto job_item = dynamic_cast<JobItem*>(tempModel->insertNewItem(Constants::JobItemType));
    fillTestItem(tempModel->insertNewItem(Constants::SpecularDataType,
                                          tempModel->indexOfItem(job_item), -1, JobItem::T_OUTPUT));

    QVBoxLayout *layout = new QVBoxLayout;
    layout->setMargin(0);
    layout->setSpacing(0);
    auto widget = new SpecularDataWidget(this);
    widget->setItem(job_item);
    layout->addWidget(widget);
    setLayout(layout);
}

namespace {
double getTestValue(size_t bin)
{
    const double factor = M_PI / (180.0 * 100.0);
    const double angle = bin * factor;
    return (std::cos(angle * 1000.0) + 1.5) * std::exp(-(bin / 100.0));
}

SpecularDataItem* fillTestItem(SessionItem* item)
{
    SpecularDataItem* result = dynamic_cast<SpecularDataItem*>(item);
    Q_ASSERT(result);
    auto outputData = std::make_unique<OutputData<double>>();
    outputData->addAxis(FixedBinAxis("Angle [deg]", 1000, 0.0, 10.0));
    for (size_t i = 0; i < 1000; ++i)
        outputData->operator[](i) = getTestValue(i);

    result->setOutputData(outputData.release());
    return result;
}
}
