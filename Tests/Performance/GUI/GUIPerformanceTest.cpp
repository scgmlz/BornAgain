// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Performance/GUI/GUIPerformanceTest.cpp
//! @brief     Implements GUI performance functional test.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Tests/Performance/GUI/GUIPerformanceTest.h"
#include "Core/Multilayer/MultiLayer.h"
#include "Core/Simulation/GISASSimulation.h"
#include "Core/StandardSamples/SampleBuilderFactory.h"
#include "GUI/coregui/Models/ApplicationModels.h"
#include "GUI/coregui/Models/DetectorItems.h"
#include "GUI/coregui/Models/DocumentModel.h"
#include "GUI/coregui/Models/DomainSimulationBuilder.h"
#include "GUI/coregui/Models/FitParameterHelper.h"
#include "GUI/coregui/Models/GUIObjectBuilder.h"
#include "GUI/coregui/Models/InstrumentItems.h"
#include "GUI/coregui/Models/InstrumentModel.h"
#include "GUI/coregui/Models/IntensityDataItem.h"
#include "GUI/coregui/Models/JobItem.h"
#include "GUI/coregui/Models/JobModel.h"
#include "GUI/coregui/Models/ModelPath.h"
#include "GUI/coregui/Models/ParameterTreeItems.h"
#include "GUI/coregui/Models/ParameterTreeUtils.h"
#include "GUI/coregui/Models/SampleModel.h"
#include "GUI/coregui/utils/GUIHelpers.h"
#include "Tests/Performance/Benchmark.h"
#include <QCoreApplication>
#include <QDebug>
#include <QElapsedTimer>
#include <random>

namespace
{
std::random_device rd;
std::mt19937 mt(rd());
std::uniform_real_distribution<double> rndm_radius(5., 6.);
} // namespace

GUIPerformanceTest::GUIPerformanceTest()
    : m_models(new ApplicationModels(nullptr)), m_sample_name("ParticleCompositionBuilder")
{
}

bool GUIPerformanceTest::runTest()
{
#ifndef NDEBUG
    const int mult = 1;
#else
    const int mult = 10;
#endif

    std::cout << "GUIPerformanceTest -> Running ..." << mult << std::endl;
    Benchmark bench;

    bench.test_method(
        "domain2gui", [this]() { test_domain_to_gui(); }, 300 * mult);
    bench.test_method(
        "gui2domain", [this]() { test_gui_to_domain(); }, 100 * mult);
    bench.test_method(
        "realTime", [this]() { test_real_time(); }, 2 * mult);

    std::cout << bench.report() << std::endl;
    return true;
}

//! Creates domain sample once and then populates sample model.

void GUIPerformanceTest::test_domain_to_gui()
{
    static std::unique_ptr<MultiLayer> sample;

    if (!sample) {
        m_models->resetModels();
        SampleBuilderFactory factory;
        sample.reset(factory.createSample(m_sample_name.toStdString()));
    }

    m_models->sampleModel()->clear();
    GUIObjectBuilder::populateSampleModel(m_models->sampleModel(), m_models->materialModel(),
                                          *sample);
}

//! Creates gui sample once and then populates domain.

void GUIPerformanceTest::test_gui_to_domain()
{
    static bool is_initialized(false);

    if (!is_initialized) {
        is_initialized = true;

        m_models->resetModels();

        SampleBuilderFactory factory;
        const std::unique_ptr<MultiLayer> sample(factory.createSample(m_sample_name.toStdString()));

        GUIObjectBuilder::populateSampleModel(m_models->sampleModel(), m_models->materialModel(),
                                              *sample);
    }

    auto sim = DomainSimulationBuilder::createSimulation(
        m_models->sampleModel()->multiLayerItem(), m_models->instrumentModel()->instrumentItem());
}

void GUIPerformanceTest::test_real_time()
{
    static JobItem* jobItem(0);

    if (!jobItem) {
        m_models->resetModels();

        SimulationOptionsItem* optionsItem = m_models->documentModel()->simulationOptionsItem();

        SampleBuilderFactory factory;
        const std::unique_ptr<MultiLayer> sample(factory.createSample(m_sample_name.toStdString()));

        GUIObjectBuilder::populateSampleModel(m_models->sampleModel(), m_models->materialModel(),
                                              *sample);

        auto instrument2DItem =
            dynamic_cast<Instrument2DItem*>(m_models->instrumentModel()->instrumentItem());
        ASSERT(instrument2DItem);
        instrument2DItem->detectorItem()->setXSize(50);
        instrument2DItem->detectorItem()->setYSize(50);

        jobItem = m_models->jobModel()->addJob(m_models->sampleModel()->multiLayerItem(),
                                               m_models->instrumentModel()->instrumentItem(), 0,
                                               optionsItem);
    }

    SessionItem* container = jobItem->parameterContainerItem();

    //    ParameterTreeUtils::visitParameterContainer(container, [&](ParameterItem* parItem)
    //    {
    //        QString parPath = FitParameterHelper::getParameterItemPath(parItem);
    //        qDebug() << parPath;
    //    });

    ParameterItem* parItem = dynamic_cast<ParameterItem*>(ModelPath::getItemFromPath(
        "MultiLayer/Layer0/ParticleLayout/ParticleComposition/Particle1/FullSphere/Radius",
        container));
    ASSERT(parItem);

    double radius = rndm_radius(mt);
    parItem->propagateValueToLink(radius);

    m_models->jobModel()->runJob(jobItem->index());

    while (m_models->jobModel()->hasUnfinishedJobs()) {
        QElapsedTimer timer;
        timer.start();
        while (timer.elapsed() < 10)
            QCoreApplication::processEvents(QEventLoop::AllEvents, 1);
    }
}

int main()
{
    return !GUIPerformanceTest().runTest();
}
