// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/Core/CoreSpecial/DetectorTest.cpp
//! @brief     Implements class DetectorTest
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Benchmark.h"
#include "DetectorTest.h"
#include "GISASSimulation.h"
#include "RectangularDetector.h"
#include "SampleBuilderFactory.h"
#include "SimulationElement.h"
#include "SphericalDetector.h"
#include "Units.h"
#include <iomanip>

namespace
{
// functions for setting up and running simulations
RectangularDetector rectangularDetector(size_t size);
SphericalDetector sphericalDetector(size_t size);
std::unique_ptr<Instrument> createInstrument(const IDetector& detector);
std::unique_ptr<GISASSimulation> createSimulation(const Instrument& instr);
void test_sim_elements(const IDetector& detector);
void test_run_simulation(const IDetector& detector);

// creating formatted strings for output
template<typename T>
std::string makeString(T value);
}

DetectorTest::DetectorTest()
    : m_input_parameters{{32, 1000},
                       {128, 50},
                       {512, 4},
                       {1024, 1},
                       {2048, 1}}
    , m_data_table(createTableWithHeader())
    , m_init_table_size(m_data_table.size())
{}

DetectorTest::~DetectorTest() = default;

bool DetectorTest::runTest()
{
    std::cout << "Runnging LargeDetectorTest..." << std::endl;

    for (const auto& test_config: m_input_parameters) {
        const size_t detector_size = test_config.first;
        const int number_of_runs = test_config.second;
        auto result = runSingleSizeDetectorTest(detector_size, number_of_runs);
        writeDataToTable(std::move(result), number_of_runs);
    }

    printResult();

    return true;
}

std::unique_ptr<Benchmark> DetectorTest::runSingleSizeDetectorTest(size_t size,
                                                                   int run_n_times) const
{
    std::unique_ptr<Benchmark> bench(new Benchmark);

    bench->test_method("elements_rect",
                       [size]() { test_sim_elements(rectangularDetector(size)); }, run_n_times);
    bench->test_method("run_rect",
                       [size]() { test_run_simulation(rectangularDetector(size)); }, run_n_times);
    bench->test_method("elements_spher",
                       [size]() { test_sim_elements(sphericalDetector(size)); }, run_n_times);
    bench->test_method("run_spher",
                       [size]() { test_run_simulation(sphericalDetector(size)); }, run_n_times);

    return bench;
}

DetectorTest::OutputDataTable DetectorTest::createTableWithHeader() const
{
    OutputDataTable data_table;
    data_table.push_back(makeString("Parameters"));
    data_table.push_back(makeString("Runs"));
    for (const auto& test_conf: m_input_parameters) {
        const std::string dim = std::to_string(test_conf.first);
        data_table[0] += makeString(dim + "x" + dim);
        data_table[1] += makeString(test_conf.second);
    }
    return data_table;
}

void DetectorTest::writeDataToTable(std::unique_ptr<Benchmark> test_result, int n_runs)
{
    const auto& result_data = test_result->retrieveData();
    size_t i = m_init_table_size;
    for (auto iter = result_data.begin(); iter != result_data.end(); ++iter, ++i) {
        if (i + 1 > m_data_table.size())
            m_data_table.push_back(makeString(iter->first));
        m_data_table[i] += makeString(iter->second->runTime() / n_runs);
    }
}

void DetectorTest::printResult()
{
    for (const auto& str: m_data_table)
        std::cout << str << std::endl;
}

namespace
{
void test_sim_elements(const IDetector& detector)
{
    auto instr = createInstrument(detector);
    instr->initDetector();
    instr->createSimulationElements<SimulationElement>();
}

void test_run_simulation(const IDetector& detector)
{
    auto instr = createInstrument(detector);
    auto simulation = createSimulation(*instr);
    simulation->runSimulation();
}

RectangularDetector rectangularDetector(size_t size)
{
    const double width_mm = 10;
    const double height_mm = 10;
    const double distance_mm = 10;
    RectangularDetector detector(size, width_mm, size, height_mm);
    detector.setPerpendicularToReflectedBeam(distance_mm);
    return detector;
}

SphericalDetector sphericalDetector(size_t size)
{
    return SphericalDetector(size, -2.0 * Units::degree, 2.0 * Units::degree, size,
                             0.0 * Units::degree, 2.0 * Units::degree);
}

std::unique_ptr<Instrument> createInstrument(const IDetector& detector)
{
    const kvector_t zplus(0.0, 0.0, 1.0);

    std::unique_ptr<Instrument> result(new Instrument);
    result->setBeamParameters(1.0 * Units::angstrom, 0.2 * Units::degree, 0.0 * Units::degree);
    result->setBeamPolarization(zplus);
    result->setDetector(detector);
    result->setAnalyzerProperties(zplus, 1.0, 0.5);
    return result;
}

std::unique_ptr<GISASSimulation> createSimulation(const Instrument& instr)
{
    std::unique_ptr<GISASSimulation> result(new GISASSimulation());
    result->setInstrument(instr);

    SampleBuilderFactory sampleFactory;
    std::shared_ptr<class IMultiLayerBuilder> builder(
        sampleFactory.create("MagneticSubstrateZeroFieldBuilder").release());
    result->setSampleBuilder(builder);
    return result;
}

template<typename T>
std::string makeString(T value) {
    static const size_t cell_width = 20;
    std::ostringstream output_stream;
    output_stream << std::setw(cell_width) << std::setfill(' ') << value;
    return output_stream.str();
}
}
