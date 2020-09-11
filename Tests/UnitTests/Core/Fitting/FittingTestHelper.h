#ifndef BORNAGAIN_TESTS_UNITTESTS_CORE_FITTING_FITTINGTESTHELPER_H
#define BORNAGAIN_TESTS_UNITTESTS_CORE_FITTING_FITTINGTESTHELPER_H

#include "Core/Basics/Units.h"
#include "Core/Intensity/OutputData.h"
#include "Core/Material/MaterialFactoryFuncs.h"
#include "Core/Multilayer/Layer.h"
#include "Core/Multilayer/MultiLayer.h"
#include "Core/Simulation/GISASSimulation.h"
#include "Fit/Kernel/Parameters.h"
#include <memory>

//! Helper class to simplify testing of SimDataPair and FitObjective

class FittingTestHelper
{
public:
    FittingTestHelper(size_t nx = 5, size_t ny = 5) : m_nx(nx), m_ny(ny), m_builder_calls(0) {}

    size_t m_nx;
    size_t m_ny;
    const double m_xmin = -1.0 * Units::deg;
    const double m_xmax = 4.0 * Units::deg;
    const double m_ymin = 0.0 * Units::deg;
    const double m_ymax = 4.0 * Units::deg;

    size_t m_builder_calls;

    std::unique_ptr<Simulation> createSimulation(const Fit::Parameters&)
    {
        MultiLayer multilayer;
        auto material = HomogeneousMaterial("Shell", 0.0, 0.0);
        multilayer.addLayer(Layer(material));
        multilayer.addLayer(Layer(material));

        std::unique_ptr<GISASSimulation> result(new GISASSimulation(multilayer));
        result->setDetectorParameters(m_nx, m_xmin, m_xmax, m_ny, m_ymin, m_ymax);

        m_builder_calls++;
        return std::unique_ptr<Simulation>(result.release());
    }

    std::unique_ptr<OutputData<double>> createData(double value)
    {
        std::unique_ptr<OutputData<double>> result(new OutputData<double>);
        result->addAxis(FixedBinAxis("phi_f", m_nx, m_xmin, m_xmax));
        result->addAxis(FixedBinAxis("alpha_f", m_ny, m_ymin, m_ymax));
        result->setAllTo(value);
        return result;
    }

    size_t size() const { return m_nx * m_ny; }
};

#endif // BORNAGAIN_TESTS_UNITTESTS_CORE_FITTING_FITTINGTESTHELPER_H
