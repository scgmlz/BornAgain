// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Simulation/Simulation.cpp
//! @brief     Implements class Simulation.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Simulation.h"
#include "IBackground.h"
#include "IMultiLayerBuilder.h"
#include "MultiLayer.h"
#include <gsl/gsl_errno.h>
#include <iomanip>
#include <iostream>

Simulation::Simulation()
{
    initialize();
}

Simulation::Simulation(const MultiLayer& p_sample)
{
    initialize();
    m_sample_provider.setSample(p_sample);
}

Simulation::Simulation(const std::shared_ptr<IMultiLayerBuilder> p_sample_builder)
{
    initialize();
    m_sample_provider.setSampleBuilder(p_sample_builder);
}

Simulation::Simulation(const Simulation& other)
    : ICloneable()
    , m_sample_provider(other.m_sample_provider)
    , m_options(other.m_options)
    , m_distribution_handler(other.m_distribution_handler)
    , m_progress(other.m_progress)
    , m_instrument(other.m_instrument)
{
    if (other.mP_background)
        setBackground(*other.mP_background);
    initialize();
}

Simulation::~Simulation() {}

//! Initializes a progress monitor that prints to stdout.
void Simulation::setTerminalProgressMonitor()
{
    m_progress.subscribe( [] (size_t percentage_done) -> bool {
            if (percentage_done<100)
                std::cout << std::setprecision(2)
                          << "\r... " << percentage_done << "%" << std::flush;
            else // wipe out
                std::cout << "\r... 100%\n";
            return true;
    } );
}

void Simulation::setDetectorResolutionFunction(const IResolutionFunction2D& resolution_function)
{
    m_instrument.setDetectorResolutionFunction(resolution_function);
}

void Simulation::removeDetectorResolutionFunction()
{
    m_instrument.removeDetectorResolution();
}

//! Sets the polarization analyzer characteristics of the detector
void Simulation::setAnalyzerProperties(const kvector_t direction, double efficiency,
                                       double total_transmission)
{
    m_instrument.setAnalyzerProperties(direction, efficiency, total_transmission);
}

void Simulation::setBeamIntensity(double intensity)
{
    m_instrument.setBeamIntensity(intensity);
}

double Simulation::getBeamIntensity() const
{
    return m_instrument.getBeamIntensity();
}

//! Sets the beam polarization according to the given Bloch vector
void Simulation::setBeamPolarization(const kvector_t bloch_vector)
{
    m_instrument.setBeamPolarization(bloch_vector);
}

void Simulation::prepareSimulation()
{
    updateSample();
    if (!m_sample_provider.sample()->containsCompatibleMaterials())
        throw std::runtime_error("Error in Simulation::prepareSimulation(): non-default materials of "
                                 "several types are used in the sample provided");
    gsl_set_error_handler_off();
}

/* currently unused
void Simulation::runOMPISimulation()
{
    OMPISimulation ompi;
    ompi.runSimulation(this);
}
*/

void Simulation::setInstrument(const Instrument& instrument)
{
    m_instrument = instrument;
    updateIntensityMap();
}

//! The MultiLayer object will not be owned by the Simulation object
void Simulation::setSample(const MultiLayer& sample)
{
    m_sample_provider.setSample(sample);
}

const MultiLayer* Simulation::sample() const
{
    return m_sample_provider.sample();
}

void Simulation::setSampleBuilder(const std::shared_ptr<class IMultiLayerBuilder> p_sample_builder)
{
    m_sample_provider.setSampleBuilder(p_sample_builder);
}

void Simulation::setBackground(const IBackground& bg)
{
    mP_background.reset(bg.clone());
    registerChild(mP_background.get());
}

std::vector<const INode*> Simulation::getChildren() const
{
    std::vector<const INode*> result;
    result.push_back(&m_instrument);
    result << m_sample_provider.getChildren();
    if (mP_background)
        result.push_back(mP_background.get());
    return result;
}

void Simulation::addParameterDistribution(const std::string& param_name,
                                          const IDistribution1D& distribution, size_t nbr_samples,
                                          double sigma_factor, const RealLimits& limits)
{
    m_distribution_handler.addParameterDistribution(
        param_name, distribution, nbr_samples, sigma_factor, limits);
}

void Simulation::addParameterDistribution(const ParameterDistribution& par_distr)
{
    m_distribution_handler.addParameterDistribution(par_distr);
}

void Simulation::updateSample()
{
    m_sample_provider.updateSample();
}

void Simulation::initialize()
{
    registerChild(&m_instrument);
    registerChild(&m_sample_provider);
}
