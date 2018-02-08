// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Export/SimulationToPython.cpp
//! @brief     Implements class SimulationToPython.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "SimulationToPython.h"
#include "ConstantBackground.h"
#include "ConvolutionDetectorResolution.h"
#include "GISASSimulation.h"
#include "INodeUtils.h"
#include "ParameterUtils.h"
#include "PoissonNoiseBackground.h"
#include "PythonFormatting.h"
#include "RectangularDetector.h"
#include "RegionOfInterest.h"
#include "ResolutionFunction2DGaussian.h"
#include "SampleToPython.h"
#include "SphericalDetector.h"
#include "OffSpecSimulation.h"
#include <iomanip>

using namespace PythonFormatting;

namespace
{
const std::string defineSimulate = "def run_simulation():\n"
                                   "    sample = "+getSampleFunctionName()+"()\n"
                                   "    simulation = get_simulation()\n"
                                   "    simulation.setSample(sample)\n"
                                   "    simulation.runSimulation()\n"
                                   "    return simulation.result()\n"
                                   "\n\n";

//! Returns a function that converts a coordinate to a Python code snippet with appropiate unit
std::function<std::string(double)> printFunc(const IDetector* detector)
{
    if (detector->defaultAxesUnits() == AxesUnits::MM)
        return PythonFormatting::printDouble;
    if (detector->defaultAxesUnits() == AxesUnits::RADIANS)
        return PythonFormatting::printDegrees;
    throw Exceptions::RuntimeErrorException(
        "SimulationToPython::defineMasks() -> Error. Unknown detector units.");
}
} // namespace

//! Returns a Python script that sets up a simulation and runs it if invoked as main program.

std::string SimulationToPython::generateSimulationCode(const Simulation& simulation,
                                                       EMainType mainType)
{
    if (simulation.sample() == nullptr)
        throw std::runtime_error("SimulationToPython::generateSimulationCode() -> Error. "
                                 "Simulation is not initialized.");

    SampleToPython sampleGenerator;

    return scriptPreamble() + sampleGenerator.generateSampleCode(*simulation.sample())
           + defineGetSimulation(&simulation) + defineSimulate + defineMain(mainType);
}

std::string SimulationToPython::defineGetSimulation(const Simulation* simulation) const
{
    std::ostringstream result;
    result << "def get_simulation():\n";

    if (auto gisas = dynamic_cast<const GISASSimulation*>(simulation))
        result << defineGISASSimulation(gisas);
    else if (auto offspec = dynamic_cast<const OffSpecSimulation*>(simulation))
        result << defineOffSpecSimulation(offspec);
    else
        throw std::runtime_error("SimulationToPython::defineGetSimulation() -> Error. "
                                 "Wrong simulation type");

    result << indent() << "return simulation\n\n\n";
    return result.str();
}

std::string SimulationToPython::defineGISASSimulation(const GISASSimulation* simulation) const
{
    std::ostringstream result;
    result << indent() << "simulation = ba.GISASSimulation()\n";
    result << defineDetector(simulation);
    result << defineDetectorResolutionFunction(simulation);
    result << defineDetectorPolarizationAnalysis(simulation);
    result << defineGISASBeam(*simulation);
    result << defineParameterDistributions(simulation);
    result << defineMasks(simulation);
    result << defineSimulationOptions(simulation);
    result << defineBackground(simulation);
    return result.str();
}

std::string SimulationToPython::defineOffSpecSimulation(const OffSpecSimulation* simulation) const
{
    std::ostringstream result;
    result << indent() << "simulation = ba.OffSpecSimulation()\n";
    result << defineDetector(simulation);
    result << defineDetectorResolutionFunction(simulation);
    result << defineDetectorPolarizationAnalysis(simulation);
    result << defineOffSpecBeam(*simulation);
    result << defineParameterDistributions(simulation);
    result << defineMasks(simulation);
    result << defineSimulationOptions(simulation);
    result << defineBackground(simulation);
    return result.str();
}

std::string SimulationToPython::defineDetector(const Simulation* simulation) const
{
    const IDetector* iDetector = simulation->getInstrument().getDetector();

    if (iDetector->dimension() != 2)
        throw Exceptions::RuntimeErrorException("SimulationToPython::defineDetector: "
                                                "detector must be two-dimensional for GISAS");
    std::ostringstream result;
    result << std::setprecision(12);

    if (auto detector = dynamic_cast<const SphericalDetector*>(iDetector)) {
        result << indent() << "simulation.setDetectorParameters(";
        for (size_t index = 0; index < detector->dimension(); ++index) {
            if (index != 0)
                result << ", ";
            result << detector->getAxis(index).size() << ", "
                   << printDegrees(detector->getAxis(index).getMin()) << ", "
                   << printDegrees(detector->getAxis(index).getMax());
        }
        result << ")\n";
    } else if (auto detector = dynamic_cast<const RectangularDetector*>(iDetector)) {
        result << indent() << "\n";
        result << indent() << "detector = ba.RectangularDetector(" << detector->getNbinsX() << ", "
               << printDouble(detector->getWidth()) << ", " << detector->getNbinsY() << ", "
               << printDouble(detector->getHeight()) << ")\n";
        if (detector->getDetectorArrangment() == RectangularDetector::GENERIC) {
            result << indent() << "detector.setPosition("
                   << printKvector(detector->getNormalVector()) << ", "
                   << printDouble(detector->getU0()) << ", " << printDouble(detector->getV0());
            if (!isDefaultDirection(detector->getDirectionVector()))
                result << ", " << printKvector(detector->getDirectionVector());
            result << ")\n";
        } else if (detector->getDetectorArrangment()
                   == RectangularDetector::PERPENDICULAR_TO_SAMPLE) {
            result << indent() << "detector.setPerpendicularToSampleX("
                   << printDouble(detector->getDistance()) << ", " << printDouble(detector->getU0())
                   << ", " << printDouble(detector->getV0()) << ")\n";
        } else if (detector->getDetectorArrangment()
                   == RectangularDetector::PERPENDICULAR_TO_DIRECT_BEAM) {
            result << indent() << "detector.setPerpendicularToDirectBeam("
                   << printDouble(detector->getDistance()) << ", " << printDouble(detector->getU0())
                   << ", " << printDouble(detector->getV0()) << ")\n";
        } else if (detector->getDetectorArrangment()
                   == RectangularDetector::PERPENDICULAR_TO_REFLECTED_BEAM) {
            result << indent() << "detector.setPerpendicularToReflectedBeam("
                   << printDouble(detector->getDistance()) << ", " << printDouble(detector->getU0())
                   << ", " << printDouble(detector->getV0()) << ")\n";
        } else if (detector->getDetectorArrangment()
                   == RectangularDetector::PERPENDICULAR_TO_REFLECTED_BEAM_DPOS) {
            result << indent() << "detector.setPerpendicularToReflectedBeam("
                   << printDouble(detector->getDistance()) << ")\n";
            result << indent() << "detector.setDirectBeamPosition("
                   << printDouble(detector->getDirectBeamU0()) << ", "
                   << printDouble(detector->getDirectBeamV0()) << ")\n";
        } else
            throw Exceptions::RuntimeErrorException(
                "SimulationToPython::defineDetector() -> Error. Unknown alignment.");

        result << indent() << "simulation.setDetector(detector)\n";
    } else
        throw Exceptions::RuntimeErrorException("SimulationToPython::defineDetector() -> Error. "
                                                "Unknown detector");
    if (iDetector->regionOfInterest()) {
        result << indent() << "simulation.setRegionOfInterest("
               << printFunc(iDetector)(iDetector->regionOfInterest()->getXlow()) << ", "
               << printFunc(iDetector)(iDetector->regionOfInterest()->getYlow()) << ", "
               << printFunc(iDetector)(iDetector->regionOfInterest()->getXup()) << ", "
               << printFunc(iDetector)(iDetector->regionOfInterest()->getYup()) << ")\n";
    }
    result << indent() << "\n";
    return result.str();
}

std::string SimulationToPython::defineDetectorResolutionFunction(const Simulation* simulation) const
{
    std::ostringstream result;
    const IDetector* detector = simulation->getInstrument().getDetector();

    if (const IDetectorResolution* p_resfunc = detector->detectorResolution()) {
        if (auto* p_convfunc = dynamic_cast<const ConvolutionDetectorResolution*>(p_resfunc)) {
            if (auto* resfunc = dynamic_cast<const ResolutionFunction2DGaussian*>(
                    p_convfunc->getResolutionFunction2D())) {
                result << indent() << "simulation.setDetectorResolutionFunction(";
                result << "ba.ResolutionFunction2DGaussian(";
                result << printFunc(detector)(resfunc->getSigmaX()) << ", ";
                result << printFunc(detector)(resfunc->getSigmaY()) << "))\n";
            } else
                throw Exceptions::RuntimeErrorException(
                    "SimulationToPython::defineDetectorResolutionFunction() -> Error. "
                    "Unknown detector resolution function");
        } else
            throw Exceptions::RuntimeErrorException(
                "SimulationToPython::defineDetectorResolutionFunction() -> Error. "
                "Not a ConvolutionDetectorResolution function");
    }
    return result.str();
}

std::string
SimulationToPython::defineDetectorPolarizationAnalysis(const Simulation* simulation) const
{
    std::ostringstream result;
    const IDetector* detector = simulation->getInstrument().getDetector();
    kvector_t analyzer_direction = detector->detectionProperties().analyzerDirection();
    double analyzer_efficiency = detector->detectionProperties().analyzerEfficiency();
    double analyzer_total_transmission
        = detector->detectionProperties().analyzerTotalTransmission();

    if (analyzer_direction.mag() > 0.0) {
        std::string direction_name = "analyzer_direction";
        result << indent() << direction_name << " = kvector_t("
               << printDouble(analyzer_direction.x()) << ", " << printDouble(analyzer_direction.y())
               << ", " << printDouble(analyzer_direction.z()) << ")\n";
        result << indent() << "simulation.setAnalyzerProperties(" << direction_name << ", "
               << printDouble(analyzer_efficiency) << ", "
               << printDouble(analyzer_total_transmission) << ")\n";
    }
    return result.str();
}

std::string SimulationToPython::defineGISASBeam(const GISASSimulation& simulation) const
{
    std::ostringstream result;
    const Beam& beam = simulation.getInstrument().getBeam();

    result << indent() << "simulation.setBeamParameters(" << printNm(beam.getWavelength()) << ", "
           << printDegrees(beam.getAlpha()) << ", " << printDegrees(beam.getPhi()) << ")\n";

    result << defineBeamPolarization(beam);
    result << defineBeamIntensity(beam);

    return result.str();
}

std::string SimulationToPython::defineOffSpecBeam(const OffSpecSimulation& simulation) const
{
    std::ostringstream result;
    const Beam& beam = simulation.getInstrument().getBeam();

    result << indent() << "alpha_i_axis = "
           << PythonFormatting::printAxis(*simulation.beamAxis(), BornAgain::UnitsRad) << "\n";

    result << indent() << "simulation.setBeamParameters(" << printNm(beam.getWavelength()) << ", "
           << "alpha_i_axis, " << printDegrees(beam.getPhi()) << ")\n";

    result << defineBeamPolarization(beam);
    result << defineBeamIntensity(beam);
    return result.str();
}

std::string SimulationToPython::defineBeamPolarization(const Beam& beam) const
{
    std::ostringstream result;
    auto bloch_vector = beam.getBlochVector();
    if (bloch_vector.mag() > 0.0) {
        std::string beam_polarization = "beam_polarization";
        result << indent() << beam_polarization << " = kvector_t(" << printDouble(bloch_vector.x())
               << ", " << printDouble(bloch_vector.y()) << ", " << printDouble(bloch_vector.z())
               << ")\n";
        result << indent() << "simulation.setBeamPolarization(" << beam_polarization << ")\n";
    }
    return result.str();
}

std::string SimulationToPython::defineBeamIntensity(const Beam& beam) const
{
    std::ostringstream result;
    double beam_intensity = beam.getIntensity();
    if (beam_intensity > 0.0)
        result << indent() << "simulation.setBeamIntensity("
               << printScientificDouble(beam_intensity) << ")\n";
    return result.str();
}


std::string SimulationToPython::defineParameterDistributions(const Simulation* simulation) const
{
    std::ostringstream result;
    const std::vector<ParameterDistribution>& distributions
        = simulation->getDistributionHandler().getDistributions();
    if (distributions.size() == 0)
        return "";
    for (size_t i = 0; i < distributions.size(); ++i) {
        std::string main_par_name = distributions[i].getMainParameterName();

        std::string mainParUnits = ParameterUtils::poolParameterUnits(*simulation, main_par_name);

        size_t nbr_samples = distributions[i].getNbrSamples();
        double sigma_factor = distributions[i].getSigmaFactor();

        std::string s_distr = "distr_" + std::to_string(i + 1);
        result << indent() << s_distr << " = "
               << printDistribution(*distributions[i].getDistribution(), mainParUnits) << "\n";

        result << indent() << "simulation.addParameterDistribution(\"" << main_par_name << "\", "
               << s_distr << ", " << nbr_samples << ", " << printDouble(sigma_factor)
               << printRealLimitsArg(distributions[i].getLimits(), mainParUnits) << ")\n";
    }
    return result.str();
}

std::string SimulationToPython::defineMasks(const Simulation* simulation) const
{
    std::ostringstream result;
    result << std::setprecision(12);

    const IDetector* detector = simulation->getInstrument().getDetector();
    const DetectorMask* detectorMask = detector->detectorMask();
    if (detectorMask && detectorMask->numberOfMasks()) {
        result << "\n";
        for (size_t i_mask = 0; i_mask < detectorMask->numberOfMasks(); ++i_mask) {
            bool mask_value(false);
            const IShape2D* shape = detectorMask->getMaskShape(i_mask, mask_value);
            result << representShape2D(indent(), shape, mask_value, printFunc(detector));
        }
        result << "\n";
    }
    return result.str();
}

std::string SimulationToPython::defineSimulationOptions(const Simulation* simulation) const
{
    std::ostringstream result;
    result << std::setprecision(12);

    const SimulationOptions& options = simulation->getOptions();
    if (options.getHardwareConcurrency() != options.getNumberOfThreads())
        result << indent() << "simulation.getOptions().setNumberOfThreads("
               << options.getNumberOfThreads() << ")\n";
    if (options.isIntegrate())
        result << indent() << "simulation.getOptions().setMonteCarloIntegration(True, "
               << options.getMcPoints() << ")\n";
    if (options.useAvgMaterials())
        result << indent() << "simulation.getOptions().setUseAvgMaterials(True)\n";
    if (options.includeSpecular())
        result << indent() << "simulation.getOptions().setIncludeSpecular(True)\n";
    return result.str();
}

std::string SimulationToPython::defineBackground(const Simulation* simulation) const
{
    std::ostringstream result;

    auto p_bg = simulation->background();
    if (auto p_constant_bg = dynamic_cast<const ConstantBackground*>(p_bg)) {
        if (p_constant_bg->backgroundValue() > 0.0) {
            result << indent() << "background = ba.ConstantBackground("
                   << printScientificDouble(p_constant_bg->backgroundValue()) << ")\n";
            result << indent() << "simulation.setBackground(background)\n";
        }
    } else if (dynamic_cast<const PoissonNoiseBackground*>(p_bg)) {
        result << indent() << "background = ba.PoissonNoiseBackground()\n";
        result << indent() << "simulation.setBackground(background)\n";
    }
    return result.str();
}

std::string SimulationToPython::defineMain(SimulationToPython::EMainType mainType)
{
    std::string result;
    if (mainType == RUN_SIMULATION) {
        result = "if __name__ == '__main__': \n"
                 "    result = run_simulation()\n"
                 "    ba.plot_simulation_result(result)\n";
    } else if (mainType == SAVE_DATA) {
        result = "if __name__ == '__main__': \n"
                 "    result = run_simulation()\n"
                 "    import sys\n"
                 "    if len(sys.argv)<2:\n"
                 "        exit(\"File name is required\")\n"
                 "    ba.IntensityDataIOFactory.writeSimulationResult(result, sys.argv[1])\n";
    } else {
        throw std::runtime_error("SimulationToPython::defineMain() -> Error. Unknown main type.");
    }
    return result;
}

std::string SimulationToPython::indent() const { return "    "; }
