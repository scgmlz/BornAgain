//  ************************************************************************************************
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
//  ************************************************************************************************

#include "Core/Export/SimulationToPython.h"
#include "Base/Utils/Algorithms.h"
#include "Core/Computation/ConstantBackground.h"
#include "Core/Computation/PoissonNoiseBackground.h"
#include "Core/Export/NodeProgeny.h"
#include "Core/Export/PyFmt.h"
#include "Core/Export/PyFmt2.h"
#include "Core/Export/PyFmtLimits.h"
#include "Core/Export/SampleToPython.h"
#include "Core/Scan/AngularSpecScan.h"
#include "Core/Scan/QSpecScan.h"
#include "Core/Simulation/GISASSimulation.h"
#include "Core/Simulation/OffSpecularSimulation.h"
#include "Core/Simulation/SpecularSimulation.h"
#include "Device/Beam/FootprintGauss.h"
#include "Device/Beam/FootprintSquare.h"
#include "Device/Detector/DetectorUtils.h"
#include "Device/Detector/RectangularDetector.h"
#include "Device/Detector/RegionOfInterest.h"
#include "Device/Detector/SphericalDetector.h"
#include "Device/Resolution/ConvolutionDetectorResolution.h"
#include "Device/Resolution/ResolutionFunction2DGaussian.h"
#include "Device/Resolution/ScanResolution.h"
#include "Param/Distrib/RangedDistributions.h"
#include "Param/Varia/ParameterUtils.h"
#include <iomanip>

using pyfmt::indent;

namespace {
//! Returns a function that converts a coordinate to a Python code snippet with appropiate unit
std::function<std::string(double)> printFunc(const IDetector* detector) {
    if (detector->defaultAxesUnits() == Axes::Units::MM)
        return pyfmt::printDouble;
    if (detector->defaultAxesUnits() == Axes::Units::RADIANS)
        return pyfmt::printDegrees;
    throw std::runtime_error("SimulationToPython::defineMasks() -> Error. Unknown detector units.");
}

//! returns true if it is (0, -1, 0) vector
bool isDefaultDirection(const kvector_t direction) {
    return algo::almostEqual(direction.x(), 0.0) && algo::almostEqual(direction.y(), -1.0)
           && algo::almostEqual(direction.z(), 0.0);
}

std::string defineFootprintFactor(const IFootprintFactor& foot) {
    std::ostringstream result;
    result << indent() << "footprint = ba." << foot.name();
    result << "(" << pyfmt::printDouble(foot.widthRatio()) << ")\n";
    return result.str();
}

std::string defineScanResolution(const ScanResolution& scan) {
    std::ostringstream result;
    result << pyfmt2::printRangedDistribution(*scan.distribution()) << "\n"
           << indent() << "resolution = "
           << "ba." << scan.name() << "(distribution, " << pyfmt::printDouble(scan.delta())
           << ")\n";
    return result.str();
}

std::string defineAngularSpecScan(const AngularSpecScan& scan) {
    std::ostringstream result;
    result << "\n"
           << indent() << "# Define specular scan:\n"
           << indent() << "axis = " << pyfmt2::printAxis(scan.coordinateAxis(), "rad") << "\n"
           << indent() << "scan = "
           << "ba.AngularSpecScan(" << pyfmt::printDouble(scan.wavelength()) << ", axis)\n";

    if (scan.footprintFactor()) {
        result << defineFootprintFactor(*scan.footprintFactor());
        result << indent() << "scan.setFootprintFactor(footprint)\n";
    }
    if (const auto* r = scan.angleResolution(); r && r->distribution()) {
        result << defineScanResolution(*r) << "\n";
        result << indent() << "scan.setAngleResolution(resolution)\n";
    }
    if (const auto* r = scan.wavelengthResolution(); r && r->distribution()) {
        result << defineScanResolution(*r) << "\n";
        result << indent() << "scan.setWavelengthResolution(resolution)\n";
    }
    return result.str();
}

std::string defineQSpecScan(const QSpecScan& scan) {
    std::ostringstream result;
    const std::string axis_def = indent() + "axis = ";
    result << axis_def << pyfmt2::printAxis(scan.coordinateAxis(), "") << "\n";
    // TODO correct unit would be 1/nm

    result << indent() << "scan = ba.QSpecScan(axis)";
    if (scan.resolution()) {
        result << "\n";
        result << defineScanResolution(*scan.resolution()) << "\n";
        result << indent() << "scan.setQResolution(resolution)";
    }
    return result.str();
}

std::string defineScan(const ISpecularScan* scan) {
    if (const auto* s = dynamic_cast<const AngularSpecScan*>(scan); s)
        return defineAngularSpecScan(*s);
    if (const auto* s = dynamic_cast<const QSpecScan*>(scan); s)
        return defineQSpecScan(*s);
    ASSERT(0);
}

std::string defineDetector(const ISimulation* simulation) {
    const IDetector* const detector = simulation->instrument().getDetector();
    if (detector->dimension() != 2)
        throw std::runtime_error("defineDetector: "
                                 "detector must be two-dimensional for GISAS");
    std::ostringstream result;
    result << std::setprecision(12);

    if (const auto* const det = dynamic_cast<const SphericalDetector*>(detector)) {
        ASSERT(det->dimension() == 2);
        if (DetectorUtils::isQuadratic(*det)) {
            result << indent() << "nbin = " << det->axis(0).size() << "\n";
            result << indent() << "detector = ba.SphericalDetector(nbin, "
                   << pyfmt::printDegrees(det->axis(0).span()) << ", "
                   << pyfmt::printDegrees(det->axis(0).center()) << ", "
                   << pyfmt::printDegrees(det->axis(1).center());
        } else {
            result << indent() << "nx = " << det->axis(0).size() << "\n";
            result << indent() << "ny = " << det->axis(1).size() << "\n";
            result << indent() << "detector = ba.SphericalDetector(nx, "
                   << pyfmt::printDegrees(det->axis(0).lowerBound()) << ", "
                   << pyfmt::printDegrees(det->axis(0).upperBound()) << ", "
                   << "ny , " << pyfmt::printDegrees(det->axis(1).lowerBound()) << ", "
                   << pyfmt::printDegrees(det->axis(1).upperBound());
        }
        result << ")\n";
    } else if (const auto* const det = dynamic_cast<const RectangularDetector*>(detector)) {
        result << "\n";
        result << indent() << "detector = ba.RectangularDetector(" << det->getNbinsX() << ", "
               << pyfmt::printDouble(det->getWidth()) << ", " << det->getNbinsY() << ", "
               << pyfmt::printDouble(det->getHeight()) << ")\n";
        if (det->getDetectorArrangment() == RectangularDetector::GENERIC) {
            result << indent() << "detector.setPosition("
                   << pyfmt::printKvector(det->getNormalVector()) << ", "
                   << pyfmt::printDouble(det->getU0()) << ", " << pyfmt::printDouble(det->getV0());
            if (!isDefaultDirection(det->getDirectionVector()))
                result << ", " << pyfmt::printKvector(det->getDirectionVector());
            result << ")\n";
        } else if (det->getDetectorArrangment() == RectangularDetector::PERPENDICULAR_TO_SAMPLE) {
            result << indent() << "detector.setPerpendicularToSampleX("
                   << pyfmt::printDouble(det->getDistance()) << ", "
                   << pyfmt::printDouble(det->getU0()) << ", " << pyfmt::printDouble(det->getV0())
                   << ")\n";
        } else if (det->getDetectorArrangment()
                   == RectangularDetector::PERPENDICULAR_TO_DIRECT_BEAM) {
            result << indent() << "detector.setPerpendicularToDirectBeam("
                   << pyfmt::printDouble(det->getDistance()) << ", "
                   << pyfmt::printDouble(det->getU0()) << ", " << pyfmt::printDouble(det->getV0())
                   << ")\n";
        } else if (det->getDetectorArrangment()
                   == RectangularDetector::PERPENDICULAR_TO_REFLECTED_BEAM) {
            result << indent() << "detector.setPerpendicularToReflectedBeam("
                   << pyfmt::printDouble(det->getDistance()) << ", "
                   << pyfmt::printDouble(det->getU0()) << ", " << pyfmt::printDouble(det->getV0())
                   << ")\n";
        } else if (det->getDetectorArrangment()
                   == RectangularDetector::PERPENDICULAR_TO_REFLECTED_BEAM_DPOS) {
            result << indent() << "detector.setPerpendicularToReflectedBeam("
                   << pyfmt::printDouble(det->getDistance()) << ")\n";
            result << indent() << "detector.setDirectBeamPosition("
                   << pyfmt::printDouble(det->getDirectBeamU0()) << ", "
                   << pyfmt::printDouble(det->getDirectBeamV0()) << ")\n";
        } else
            throw std::runtime_error("defineDetector() -> Error. Unknown alignment.");
    } else
        throw std::runtime_error("defineDetector() -> Error. Unknown detector");
    if (detector->regionOfInterest()) {
        result << indent() << "detector.setRegionOfInterest("
               << printFunc(detector)(detector->regionOfInterest()->getXlow()) << ", "
               << printFunc(detector)(detector->regionOfInterest()->getYlow()) << ", "
               << printFunc(detector)(detector->regionOfInterest()->getXup()) << ", "
               << printFunc(detector)(detector->regionOfInterest()->getYup()) << ")\n";
    }
    result << "\n";
    return result.str();
}

std::string defineDetectorResolutionFunction(const ISimulation* simulation) {
    std::ostringstream result;
    const IDetector* detector = simulation->instrument().getDetector();

    if (const IDetectorResolution* resfunc = detector->detectorResolution()) {
        if (auto* convfunc = dynamic_cast<const ConvolutionDetectorResolution*>(resfunc)) {
            if (auto* resfunc = dynamic_cast<const ResolutionFunction2DGaussian*>(
                    convfunc->getResolutionFunction2D())) {
                result << indent() << "simulation.setDetectorResolutionFunction(";
                result << "ba.ResolutionFunction2DGaussian(";
                result << printFunc(detector)(resfunc->getSigmaX()) << ", ";
                result << printFunc(detector)(resfunc->getSigmaY()) << "))\n";
            } else
                throw std::runtime_error("defineDetectorResolutionFunction() -> Error. "
                                         "Unknown detector resolution function");
        } else
            throw std::runtime_error("defineDetectorResolutionFunction() -> Error. "
                                     "Not a ConvolutionDetectorResolution function");
    }
    return result.str();
}

std::string defineDetectorPolarizationAnalysis(const ISimulation* simulation) {
    std::ostringstream result;
    const IDetector* detector = simulation->instrument().getDetector();
    kvector_t analyzer_direction = detector->detectionProperties().analyzerDirection();
    double analyzer_efficiency = detector->detectionProperties().analyzerEfficiency();
    double analyzer_total_transmission =
        detector->detectionProperties().analyzerTotalTransmission();

    if (analyzer_direction.mag() > 0.0) {
        std::string direction_name = "analyzer_direction";
        result << indent() << direction_name << " = kvector_t("
               << pyfmt::printDouble(analyzer_direction.x()) << ", "
               << pyfmt::printDouble(analyzer_direction.y()) << ", "
               << pyfmt::printDouble(analyzer_direction.z()) << ")\n";
        result << indent() << "simulation.setAnalyzerProperties(" << direction_name << ", "
               << pyfmt::printDouble(analyzer_efficiency) << ", "
               << pyfmt::printDouble(analyzer_total_transmission) << ")\n";
    }
    return result.str();
}

std::string defineBeamPolarization(const Beam& beam) {
    std::ostringstream result;
    auto bloch_vector = beam.getBlochVector();
    if (bloch_vector.mag() > 0.0) {
        std::string beam_polarization = "beam_polarization";
        result << indent() << beam_polarization << " = kvector_t("
               << pyfmt::printDouble(bloch_vector.x()) << ", "
               << pyfmt::printDouble(bloch_vector.y()) << ", "
               << pyfmt::printDouble(bloch_vector.z()) << ")\n";
        result << indent() << "beam.setPolarization(" << beam_polarization << ")\n";
    }
    return result.str();
}

std::string defineBeamIntensity(const Beam& beam) {
    std::ostringstream result;
    double beam_intensity = beam.intensity();
    if (beam_intensity > 0.0)
        result << indent() << "simulation.beam().setIntensity("
               << pyfmt::printScientificDouble(beam_intensity) << ")\n";
    return result.str();
}

std::string defineGISASBeam(const GISASSimulation& simulation) {
    std::ostringstream result;
    const Beam& beam = simulation.instrument().beam();

    result << indent() << "beam = ba.Beam(" << pyfmt::printDouble(beam.intensity()) << ", "
           << pyfmt::printNm(beam.wavelength()) << ", ba.Direction("
           << pyfmt::printDegrees(beam.direction().alpha()) << ", "
           << pyfmt::printDegrees(beam.direction().phi()) << "))\n";

    result << defineBeamPolarization(beam);

    return result.str();
}

std::string defineOffSpecularBeam(const OffSpecularSimulation& simulation) {
    std::ostringstream result;
    const Beam& beam = simulation.instrument().beam();

    const std::string axidef = indent() + "alpha_i_axis = ";
    result << axidef << pyfmt2::printAxis(simulation.beamAxis(), "rad") << "\n";

    result << indent() << "simulation.setBeamParameters(" << pyfmt::printNm(beam.wavelength())
           << ", "
           << "alpha_i_axis, " << pyfmt::printDegrees(beam.direction().phi()) << ")\n";

    result << defineBeamPolarization(beam);
    result << defineBeamIntensity(beam);
    return result.str();
}

std::string defineSpecularScan(const SpecularSimulation& simulation) {
    std::ostringstream result;
    const ISpecularScan* scan = simulation.dataHandler();
    if (!scan)
        throw std::runtime_error("Error defineSpecularScan: passed simulation "
                                 "does not contain any scan");
    result << defineScan(scan) << "\n";
    result << indent() << "simulation.setScan(scan)\n";
    result << defineBeamIntensity(simulation.instrument().beam()) << "\n";
    return result.str();
}

std::string defineParameterDistributions(const ISimulation* simulation) {
    std::ostringstream result;
    const std::vector<ParameterDistribution>& distributions =
        simulation->getDistributionHandler().getDistributions();
    if (distributions.empty())
        return "";
    for (size_t i = 0; i < distributions.size(); ++i) {
        std::string main_par_name = distributions[i].getMainParameterName();

        std::string mainParUnits = ParameterUtils::poolParameterUnits(*simulation, main_par_name);

        size_t nbr_samples = distributions[i].getNbrSamples();
        double sigma_factor = distributions[i].getSigmaFactor();

        std::string distr = "distr_" + std::to_string(i + 1);
        result << indent() << distr << " = "
               << pyfmt2::printDistribution(*distributions[i].getDistribution(), mainParUnits)
               << "\n";

        result << indent() << "simulation.addParameterDistribution(\"" << main_par_name << "\", "
               << distr << ", " << nbr_samples << ", " << pyfmt::printDouble(sigma_factor)
               << pyfmt::printRealLimitsArg(distributions[i].getLimits(), mainParUnits) << ")\n";
    }
    return result.str();
}

std::string defineMasks(const ISimulation* simulation) {
    std::ostringstream result;
    result << std::setprecision(12);

    const IDetector* detector = simulation->instrument().getDetector();
    const DetectorMask* detectorMask = detector->detectorMask();
    if (detectorMask && detectorMask->numberOfMasks()) {
        result << "\n";
        for (size_t i_mask = 0; i_mask < detectorMask->numberOfMasks(); ++i_mask) {
            bool mask_value(false);
            const IShape2D* shape = detectorMask->getMaskShape(i_mask, mask_value);
            result << pyfmt2::representShape2D(indent(), shape, mask_value, printFunc(detector));
        }
        result << "\n";
    }
    return result.str();
}

std::string defineSimulationOptions(const ISimulation* simulation) {
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

std::string defineBackground(const ISimulation* simulation) {
    std::ostringstream result;

    auto bg = simulation->background();
    if (auto constant_bg = dynamic_cast<const ConstantBackground*>(bg)) {
        if (constant_bg->backgroundValue() > 0.0) {
            result << indent() << "background = ba.ConstantBackground("
                   << pyfmt::printScientificDouble(constant_bg->backgroundValue()) << ")\n";
            result << indent() << "simulation.setBackground(background)\n";
        }
    } else if (dynamic_cast<const PoissonNoiseBackground*>(bg)) {
        result << indent() << "background = ba.PoissonNoiseBackground()\n";
        result << indent() << "simulation.setBackground(background)\n";
    }
    return result.str();
}

std::string defineGISASSimulation(const GISASSimulation* simulation) {
    std::ostringstream result;
    result << defineGISASBeam(*simulation);
    result << defineDetector(simulation);
    result << indent() << "simulation = ba.GISASSimulation(beam, get_sample(), detector)\n";
    result << defineDetectorResolutionFunction(simulation);
    result << defineDetectorPolarizationAnalysis(simulation);
    result << defineParameterDistributions(simulation);
    result << defineMasks(simulation);
    result << defineSimulationOptions(simulation);
    result << defineBackground(simulation);
    return result.str();
}

std::string defineOffSpecularSimulation(const OffSpecularSimulation* simulation) {
    std::ostringstream result;
    result << indent() << "simulation = ba.OffSpecularSimulation()\n";
    result << defineDetector(simulation);
    result << defineDetectorResolutionFunction(simulation);
    result << defineDetectorPolarizationAnalysis(simulation);
    result << defineOffSpecularBeam(*simulation);
    result << defineParameterDistributions(simulation);
    result << defineMasks(simulation);
    result << defineSimulationOptions(simulation);
    result << defineBackground(simulation);
    result << "    simulation.setSample(get_sample())\n";
    return result.str();
}

std::string defineSpecularSimulation(const SpecularSimulation* simulation) {
    std::ostringstream result;
    result << indent() << "simulation = ba.SpecularSimulation()\n";
    result << defineDetectorPolarizationAnalysis(simulation);
    result << defineSpecularScan(*simulation);
    result << defineParameterDistributions(simulation);
    result << defineSimulationOptions(simulation);
    result << defineBackground(simulation);
    result << "    simulation.setSample(get_sample())\n";
    return result.str();
}

std::string defineSimulate(const ISimulation* simulation) {
    std::ostringstream result;
    result << "def get_simulation():\n";
    if (auto gisas = dynamic_cast<const GISASSimulation*>(simulation))
        result << defineGISASSimulation(gisas);
    else if (auto offspec = dynamic_cast<const OffSpecularSimulation*>(simulation))
        result << defineOffSpecularSimulation(offspec);
    else if (auto spec = dynamic_cast<const SpecularSimulation*>(simulation))
        result << defineSpecularSimulation(spec);
    else
        ASSERT(0);
    result << "    return simulation\n\n\n";

    result << "def run_simulation():\n"
              "    simulation = get_simulation()\n"
              "    simulation.runSimulation()\n"
              "    return simulation.result()\n\n\n";

    return result.str();
}

const std::string defineMain =
    "if __name__ == '__main__':\n"
    "    result = run_simulation()\n"
    "    if len(sys.argv)>=2:\n"
    "        ba.IntensityDataIOFactory.writeSimulationResult(result, sys.argv[1])\n"
    "    else:\n"
    "        ba.plot_simulation_result(result, cmap='jet', aspect='auto')\n";

} // namespace

//  ************************************************************************************************
//  class SimulationToPython
//  ************************************************************************************************

std::string SimulationToPython::generateSimulationCode(const ISimulation& simulation) {
    if (simulation.sample() == nullptr)
        throw std::runtime_error("Cannot export: Simulation has no sample");
    return pyfmt::scriptPreamble() + SampleToPython().generateSampleCode(*simulation.sample())
           + defineSimulate(&simulation) + defineMain;
}
