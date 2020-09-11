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

#include "GUI/coregui/Views/TestView.h"
#include "GUI/coregui/Models/ApplicationModels.h"
#include "GUI/coregui/Models/Data1DViewItem.h"
#include "GUI/coregui/Models/DataPropertyContainer.h"
#include "GUI/coregui/Models/JobItem.h"
#include "GUI/coregui/Models/JobModel.h"
#include "GUI/coregui/Models/MinimizerItem.h"
#include "GUI/coregui/Models/RealDataItem.h"
#include "GUI/coregui/Models/SampleModel.h"
#include "GUI/coregui/Models/SpecularDataItem.h"
#include "GUI/coregui/Views/AccordionWidget/AccordionWidget.h"
#include "GUI/coregui/Views/FitWidgets/MinimizerSettingsWidget.h"
#include "GUI/coregui/Views/MaskWidgets/MaskEditor.h"
#include "GUI/coregui/Views/MaterialEditor/MaterialEditor.h"
#include "GUI/coregui/Views/PropertyEditor/TestComponentView.h"
#include "GUI/coregui/Views/RealSpaceWidgets/RealSpaceWidget.h"
#include "GUI/coregui/Views/SpecularDataWidgets/Plot1DCanvas.h"
#include "GUI/coregui/mainwindow/mainwindow.h"
#include <QTreeView>

#include <QCheckBox>
#include <QLineEdit>

namespace
{
// These functions are required for testing purposes only
// They must be removed after completion of
// SpecularDataWidget
double getTestValue(size_t bin, double factor);
SpecularDataItem* fillTestItem(SessionItem* item, double factor);
} // namespace

TestView::TestView(MainWindow* mainWindow) : QWidget(mainWindow), m_mainWindow(mainWindow)
{
    //    test_ComponentProxyModel();
    //    test_MaterialEditor();
    //    test_MinimizerSettings();
    //    test_AccordionWidget();
    //    test_RunFitWidget();
    //    test_ba3d();
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
    MaterialEditor* materialEditor = new MaterialEditor(m_mainWindow->materialModel());
    QVBoxLayout* layout = new QVBoxLayout;
    layout->setMargin(0);
    layout->setSpacing(0);
    layout->addWidget(materialEditor);
    setLayout(layout);
}

void TestView::test_MinimizerSettings()
{
    MinimizerSettingsWidget* widget = new MinimizerSettingsWidget;
    QVBoxLayout* layout = new QVBoxLayout;
    layout->setMargin(0);
    layout->setSpacing(0);
    layout->addWidget(widget);
    setLayout(layout);

    SessionModel* model = new SessionModel("TempModel", this);
    MinimizerContainerItem* minimizerItem =
        dynamic_cast<MinimizerContainerItem*>(model->insertNewItem("MinimizerContainer"));
    widget->setItem(minimizerItem);
}

void TestView::test_AccordionWidget()
{
    AccordionWidget* myAccordion = new AccordionWidget();
    myAccordion->setMultiActive(true);
    // add the Accordion to your layout
    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(myAccordion);
    setLayout(layout);

    // add a content pane with a header
    int firstPaneIndex = myAccordion->addContentPane("My first content pane");
    // make sure our content pane was added
    if (firstPaneIndex != -1) {
        // get a QFrame* from the Content Pane. This is where we place our content
        QFrame* contentFrame = myAccordion->getContentPane(firstPaneIndex)->getContentFrame();
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
        QFrame* contentFrame = myAccordion->getContentPane(secondPaneIndex)->getContentFrame();
        // give the QFrame a QLayout
        contentFrame->setLayout(new QVBoxLayout());
        // add a simpel QLabel to the frame
        QLineEdit* led = new QLineEdit();
        QLineEdit* led2 = new QLineEdit();
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
        QFrame* contentFrame = myAccordion->getContentPane(third)->getContentFrame();
        contentFrame->setMaximumHeight(500);
        // give the QFrame a QLayout
        contentFrame->setLayout(new QVBoxLayout());
        // add a simpel QLabel to the frame
        QCheckBox* cb = new QCheckBox();
        cb->setText("Option 1");
        QCheckBox* cb2 = new QCheckBox();
        cb2->setText("Option 2");
        QCheckBox* cb3 = new QCheckBox();
        cb3->setText("Option 3");
        QCheckBox* cb4 = new QCheckBox();
        cb4->setText("Option 4");
        QCheckBox* cb5 = new QCheckBox();
        cb5->setText("Option 5");
        QCheckBox* cb6 = new QCheckBox();
        cb6->setText("Option 6");
        QCheckBox* cb7 = new QCheckBox();
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
    // After putting this 3D view in Sample Viewer with the necessary changes, it does not work
    // in test view and needs to be refactored in order to be used.

    QVBoxLayout* layout = new QVBoxLayout;
    layout->setMargin(0);
    layout->setSpacing(0);
    RealSpaceWidget* widget = new RealSpaceWidget(m_mainWindow->sampleModel());
    layout->addWidget(widget);
    setLayout(layout);
}

void TestView::test_specular_data_widget()
{
    SessionModel* tempModel = new SessionModel("Test", this);

    // creating job item
    auto job_item = dynamic_cast<JobItem*>(tempModel->insertNewItem("JobItem"));

    // creating "simulation" data
    auto data_item = new SpecularDataItem();
    job_item->insertItem(-1, data_item, JobItem::T_OUTPUT);
    fillTestItem(data_item, 1.0);

    // creating "real" data
    auto real_data = new RealDataItem();
    job_item->insertItem(-1, real_data, JobItem::T_REALDATA);
    data_item = new SpecularDataItem();
    real_data->insertItem(-1, data_item, RealDataItem::T_INTENSITY_DATA);
    fillTestItem(data_item, 2.0);

    // creating data view
    auto data_view = new Data1DViewItem();
    job_item->insertItem(-1, data_view, JobItem::T_DATAVIEW);
    data_view->insertItem(-1, new DataPropertyContainer, Data1DViewItem::T_DATA_PROPERTIES);
    auto& container = data_view->item<DataPropertyContainer>(Data1DViewItem::T_DATA_PROPERTIES);
    container.addItem(job_item->realDataItem()->dataItem());
    container.addItem(job_item->dataItem());

    QVBoxLayout* layout = new QVBoxLayout;
    layout->setMargin(0);
    layout->setSpacing(0);
    auto widget = new Plot1DCanvas(this);
    widget->setItem(job_item->dataItemView());
    layout->addWidget(widget);
    setLayout(layout);
}

namespace
{
double getTestValue(size_t bin, double factor)
{
    const double angle_factor = M_PI / (180.0 * 100.0);
    const double angle = bin * angle_factor;
    return (std::cos(angle * 1000.0) + 1.5) * std::exp(-(bin * factor / 100.0));
}

SpecularDataItem* fillTestItem(SessionItem* item, double factor)
{
    SpecularDataItem* result = dynamic_cast<SpecularDataItem*>(item);
    ASSERT(result);
    auto outputData = std::make_unique<OutputData<double>>();
    outputData->addAxis(FixedBinAxis("Angle [deg]", 1000, 0.0, 10.0));
    for (size_t i = 0; i < 1000; ++i)
        outputData->operator[](i) = getTestValue(i, factor);

    result->setOutputData(outputData.release());
    return result;
}
} // namespace
