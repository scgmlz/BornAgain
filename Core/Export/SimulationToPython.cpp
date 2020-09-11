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

#include "Core/Export/SimulationToPython.h"
#include "Core/Beam/FootprintGauss.h"
#include "Core/Beam/FootprintSquare.h"
#include "Core/Computation/ConstantBackground.h"
#include "Core/Computation/PoissonNoiseBackground.h"
#include "Core/Detector/ConvolutionDetectorResolution.h"
#include "Core/Detector/RectangularDetector.h"
#include "Core/Detector/RegionOfInterest.h"
#include "Core/Detector/ResolutionFunction2DGaussian.h"
#include "Core/Detector/SphericalDetector.h"
#include "Core/Export/INodeUtils.h"
#include "Core/Export/SampleToPython.h"
#include "Core/Instrument/ISpecularScan.h"
#include "Core/Parametrization/ParameterUtils.h"
#include "Core/PyIO/PythonFormatting.h"
#include "Core/Simulation/GISASSimulation.h"
#include "Core/Simulation/OffSpecSimulation.h"
#include "Core/Simulation/SpecularSimulation.h"
#include "Core/Tools/PyFmt.h"
#include <iomanip>

namespace
{
const std::string defineSimulate = "def run_simulation():\n"
                                   "    sample = "
                                   + pyfmt::getSampleFunctionName()
                                   + "()\n"
                                     "    simulation = get_simulation()\n"
                                     "    simulation.setSample(sample)\n"
                                     "    simulation.runSimulation()\n"
                                     "    return simulation.result()\n"
                                     "\n\n";

//! Returns a function that converts a coordinate to a Python code snippet with appropiate unit
std::function<std::string(double)> printFunc(const IDetector* detector)
{
    if (detector->defaultAxesUnits() == AxesUnits::MM)
        return pyfmt::printDouble;
    if (detector->defaultAxesUnits() == AxesUnits::RADIANS)
        return pyfmt::printDegrees;
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

    return pyfmt::scriptPreamble() + sampleGenerator.generateSampleCode(*simulation.sample())
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
    else if (auto spec = dynamic_cast<const SpecularSimulation*>(simulation))
        result << defineSpecularSimulation(spec);
    else
        throw std::runtime_error("SimulationToPython::defineGetSimulation() -> Error. "
                                 "Wrong simulation type");

    result << pyfmt::indent() << "return simulation\n\n\n";
    return result.str();
}

std::string SimulationToPython::defineGISASSimulation(const GISASSimulation* simulation) const
{
    std::ostringstream result;
    result << pyfmt::indent() << "simulation = ba.GISASSimulation()\n";
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
    result << pyfmt::indent() << "simulation = ba.OffSpecSimulation()\n";
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

std::string SimulationToPython::defineSpecularSimulation(const SpecularSimulation* simulation) const
{
    std::ostringstream result;
    result << pyfmt::indent() << "simulation = ba.SpecularSimulation()\n";
    result << defineDetectorPolarizationAnalysis(simulation);
    result << defineSpecularScan(*simulation);
    result << defineParameterDistributions(simulation);
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
        result << pyfmt::indent() << "simulation.setDetectorParameters(";
        for (size_t index = 0; index < detector->dimension(); ++index) {
            if (index != 0)
                result << ", ";
            result << detector->getAxis(index).size() << ", "
                   << pyfmt::printDegrees(detector->getAxis(index).getMin()) << ", "
                   << pyfmt::printDegrees(detector->getAxis(index).getMax());
        }
        result << ")\n";
    } else if (auto detector = dynamic_cast<const RectangularDetector*>(iDetector)) {
        result << pyfmt::indent() << "\n";
        result << pyfmt::indent() << "detector = ba.RectangularDetector(" << detector->getNbinsX()
               << ", " << pyfmt::printDouble(detector->getWidth()) << ", " << detector->getNbinsY()
               << ", " << pyfmt::printDouble(detector->getHeight()) << ")\n";
        if (detector->getDetectorArrangment() == RectangularDetector::GENERIC) {
            result << pyfmt::indent() << "detector.setPosition("
                   << pyfmt::printKvector(detector->getNormalVector()) << ", "
                   << pyfmt::printDouble(detector->getU0()) << ", "
                   << pyfmt::printDouble(detector->getV0());
            if (!pyfmt::isDefaultDirection(detector->getDirectionVector()))
                result << ", " << pyfmt::printKvector(detector->getDirectionVector());
            result << ")\n";
        } else if (detector->getDetectorArrangment()
                   == RectangularDetector::PERPENDICULAR_TO_SAMPLE) {
            result << pyfmt::indent() << "detector.setPerpendicularToSampleX("
                   << pyfmt::printDouble(detector->getDistance()) << ", "
                   << pyfmt::printDouble(detector->getU0()) << ", "
                   << pyfmt::printDouble(detector->getV0()) << ")\n";
        } else if (detector->getDetectorArrangment()
                   == RectangularDetector::PERPENDICULAR_TO_DIRECT_BEAM) {
            result << pyfmt::indent() << "detector.setPerpendicularToDirectBeam("
                   << pyfmt::printDouble(detector->getDistance()) << ", "
                   << pyfmt::printDouble(detector->getU0()) << ", "
                   << pyfmt::printDouble(detector->getV0()) << ")\n";
        } else if (detector->getDetectorArrangment()
                   == RectangularDetector::PERPENDICULAR_TO_REFLECTED_BEAM) {
            result << pyfmt::indent() << "detector.setPerpendicularToReflectedBeam("
                   << pyfmt::printDouble(detector->getDistance()) << ", "
                   << pyfmt::printDouble(detector->getU0()) << ", "
                   << pyfmt::printDouble(detector->getV0()) << ")\n";
        } else if (detector->getDetectorArrangment()
                   == RectangularDetector::PERPENDICULAR_TO_REFLECTED_BEAM_DPOS) {
            result << pyfmt::indent() << "detector.setPerpendicularToReflectedBeam("
                   << pyfmt::printDouble(detector->getDistance()) << ")\n";
            result << pyfmt::indent() << "detector.setDirectBeamPosition("
                   << pyfmt::printDouble(detector->getDirectBeamU0()) << ", "
                   << pyfmt::printDouble(detector->getDirectBeamV0()) << ")\n";
        } else
            throw Exceptions::RuntimeErrorException(
                "SimulationToPython::defineDetector() -> Error. Unknown alignment.");

        result << pyfmt::indent() << "simulation.setDetector(detector)\n";
    } else
        throw Exceptions::RuntimeErrorException("SimulationToPython::defineDetector() -> Error. "
                                                "Unknown detector");
    if (iDetector->regionOfInterest()) {
        result << pyfmt::indent() << "simulation.setRegionOfInterest("
               << printFunc(iDetector)(iDetector->regionOfInterest()->getXlow()) << ", "
               << printFunc(iDetector)(iDetector->regionOfInterest()->getYlow()) << ", "
               << printFunc(iDetector)(iDetector->regionOfInterest()->getXup()) << ", "
               << printFunc(iDetector)(iDetector->regionOfInterest()->getYup()) << ")\n";
    }
    result << pyfmt::indent() << "\n";
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
                result << pyfmt::indent() << "simulation.setDetectorResolutionFunction(";
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
    double analyzer_total_transmission =
        detector->detectionProperties().analyzerTotalTransmission();

    if (analyzer_direction.mag() > 0.0) {
        std::string direction_name = "analyzer_direction";
        result << pyfmt::indent() << direction_name << " = kvector_t("
               << pyfmt::printDouble(analyzer_direction.x()) << ", "
               << pyfmt::printDouble(analyzer_direction.y()) << ", "
               << pyfmt::printDouble(analyzer_direction.z()) << ")\n";
        result << pyfmt::indent() << "simulation.setAnalyzerProperties(" << direction_name << ", "
               << pyfmt::printDouble(analyzer_efficiency) << ", "
               << pyfmt::printDouble(analyzer_total_transmission) << ")\n";
    }
    return result.str();
}

std::string SimulationToPython::defineGISASBeam(const GISASSimulation& simulation) const
{
    std::ostringstream result;
    const Beam& beam = simulation.getInstrument().getBeam();

    result << pyfmt::indent() << "simulation.setBeamParameters("
           << pyfmt::printNm(beam.getWavelength()) << ", " << pyfmt::printDegrees(beam.getAlpha())
           << ", " << pyfmt::printDegrees(beam.getPhi()) << ")\n";

    result << defineBeamPolarization(beam);
    result << defineBeamIntensity(beam);

    return result.str();
}

std::string SimulationToPython::defineOffSpecBeam(const OffSpecSimulation& simulation) const
{
    std::ostringstream result;
    const Beam& beam = simulation.getInstrument().getBeam();

    const std::string axis_def = pyfmt::indent() + "alpha_i_axis = ";
    result << axis_def << pyfmt2::printAxis(*simulation.beamAxis(), "rad", axis_def.size()) << "\n";

    result << pyfmt::indent() << "simulation.setBeamParameters("
           << pyfmt::printNm(beam.getWavelength()) << ", "
           << "alpha_i_axis, " << pyfmt::printDegrees(beam.getPhi()) << ")\n";

    result << defineBeamPolarization(beam);
    result << defineBeamIntensity(beam);
    return result.str();
}

std::string SimulationToPython::defineSpecularScan(const SpecularSimulation& simulation) const
{
    std::ostringstream result;
    const ISpecularScan* scan = simulation.dataHandler();
    if (!scan)
        throw std::runtime_error("Error SimulationToPython::defineSpecularScan: passed simulation "
                                 "does not contain any scan");
    result << *scan << "\n";

    result << pyfmt::indent() << "simulation.setScan(scan)\n";
    result << defineBeamIntensity(simulation.getInstrument().getBeam());
    result << "\n";
    return result.str();
}

std::string SimulationToPython::defineBeamPolarization(const Beam& beam) const
{
    std::ostringstream result;
    auto bloch_vector = beam.getBlochVector();
    if (bloch_vector.mag() > 0.0) {
        std::string beam_polarization = "beam_polarization";
        result << pyfmt::indent() << beam_polarization << " = kvector_t("
               << pyfmt::printDouble(bloch_vector.x()) << ", "
               << pyfmt::printDouble(bloch_vector.y()) << ", "
               << pyfmt::printDouble(bloch_vector.z()) << ")\n";
        result << pyfmt::indent() << "simulation.setBeamPolarization(" << beam_polarization
               << ")\n";
    }
    return result.str();
}

std::string SimulationToPython::defineBeamIntensity(const Beam& beam) const
{
    std::ostringstream result;
    double beam_intensity = beam.getIntensity();
    if (beam_intensity > 0.0)
        result << pyfmt::indent() << "simulation.setBeamIntensity("
               << pyfmt::printScientificDouble(beam_intensity) << ")\n";
    return result.str();
}

std::string SimulationToPython::defineParameterDistributions(const Simulation* simulation) const
{
    std::ostringstream result;
    const std::vector<ParameterDistribution>& distributions =
        simulation->getDistributionHandler().getDistributions();
    if (distributions.size() == 0)
        return "";
    for (size_t i = 0; i < distributions.size(); ++i) {
        std::string main_par_name = distributions[i].getMainParameterName();

        std::string mainParUnits = ParameterUtils::poolParameterUnits(*simulation, main_par_name);

        size_t nbr_samples = distributions[i].getNbrSamples();
        double sigma_factor = distributions[i].getSigmaFactor();

        std::string s_distr = "distr_" + std::to_string(i + 1);
        result << pyfmt::indent() << s_distr << " = "
               << pyfmt2::printDistribution(*distributions[i].getDistribution(), mainParUnits)
               << "\n";

        result << pyfmt::indent() << "simulation.addParameterDistribution(\"" << main_par_name
               << "\", " << s_distr << ", " << nbr_samples << ", "
               << pyfmt::printDouble(sigma_factor)
               << pyfmt::printRealLimitsArg(distributions[i].getLimits(), mainParUnits) << ")\n";
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
            result << pyfmt2::representShape2D(pyfmt::indent(), shape, mask_value,
                                               printFunc(detector));
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
        result << pyfmt::indent() << "simulation.getOptions().setNumberOfThreads("
               << options.getNumberOfThreads() << ")\n";
    if (options.isIntegrate())
        result << pyfmt::indent() << "simulation.getOptions().setMonteCarloIntegration(True, "
               << options.getMcPoints() << ")\n";
    if (options.useAvgMaterials())
        result << pyfmt::indent() << "simulation.getOptions().setUseAvgMaterials(True)\n";
    if (options.includeSpecular())
        result << pyfmt::indent() << "simulation.getOptions().setIncludeSpecular(True)\n";
    return result.str();
}

std::string SimulationToPython::defineBackground(const Simulation* simulation) const
{
    std::ostringstream result;

    auto p_bg = simulation->background();
    if (auto p_constant_bg = dynamic_cast<const ConstantBackground*>(p_bg)) {
        if (p_constant_bg->backgroundValue() > 0.0) {
            result << pyfmt::indent() << "background = ba.ConstantBackground("
                   << pyfmt::printScientificDouble(p_constant_bg->backgroundValue()) << ")\n";
            result << pyfmt::indent() << "simulation.setBackground(background)\n";
        }
    } else if (dynamic_cast<const PoissonNoiseBackground*>(p_bg)) {
        result << pyfmt::indent() << "background = ba.PoissonNoiseBackground()\n";
        result << pyfmt::indent() << "simulation.setBackground(background)\n";
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
