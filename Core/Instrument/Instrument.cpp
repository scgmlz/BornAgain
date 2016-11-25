// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Instrument/Instrument.cpp
//! @brief     Implements class Instrument.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "Instrument.h"
#include "Beam.h"
#include "ConvolutionDetectorResolution.h"
#include "IDetector2D.h"
#include "IResolutionFunction2D.h"
#include "SimulationElement.h"
#include "SphericalDetector.h"

Instrument::Instrument() : IParameterized("Instrument")
{
    mP_detector.reset(new SphericalDetector());
    init_parameters();
}

Instrument::Instrument(const Instrument& other) : IParameterized(), m_beam(other.m_beam)
{
    mP_detector.reset(other.mP_detector->clone());
    setName(other.getName());
    init_parameters();
}

Instrument::~Instrument() {}

Instrument& Instrument::operator=(const Instrument& other)
{
    if (this != &other) {
        m_beam = other.m_beam;
        mP_detector.reset(other.mP_detector->clone());
        init_parameters();
    }
    return *this;
}

void Instrument::setDetector(const IDetector2D& detector)
{
    mP_detector.reset(detector.clone());
    initDetector();
}

void Instrument::setDetectorParameters(
    size_t n_x, double x_min, double x_max, size_t n_y, double y_min, double y_max)
{
    mP_detector->setDetectorParameters(n_x, x_min, x_max, n_y, y_min, y_max);
}

void Instrument::setDetectorAxes(const IAxis& axis0, const IAxis& axis1)
{
    mP_detector->setDetectorAxes(axis0, axis1);
}

std::string Instrument::addParametersToExternalPool(
    const std::string& path, ParameterPool* external_pool, int copy_number) const
{
    // add own parameters
    std::string new_path =
        IParameterized::addParametersToExternalPool(path, external_pool, copy_number);

    // add parameters of the beam
    m_beam.addParametersToExternalPool(new_path, external_pool, -1);

    // add parameters of the detector
    mP_detector->addParametersToExternalPool(new_path, external_pool, -1);

    return new_path;
}

void Instrument::initDetector()
{
    if (!mP_detector)
        throw Exceptions::RuntimeErrorException(
            "Instrument::initDetector() -> Error. Detector is not initialized.");
    getDetector()->init(getBeam());
}


std::vector<SimulationElement> Instrument::createSimulationElements()
{
    return mP_detector->createSimulationElements(m_beam);
}

void Instrument::setDetectorResolutionFunction(IResolutionFunction2D* p_resolution_function)
{
    if (p_resolution_function) {
        mP_detector->setDetectorResolution(
            new ConvolutionDetectorResolution(p_resolution_function));
    } else {
        mP_detector->setDetectorResolution(0);
    }
}

void Instrument::setDetectorResolutionFunction(const IResolutionFunction2D& p_resolution_function)
{
    mP_detector->setDetectorResolution(new ConvolutionDetectorResolution(p_resolution_function));
}

void Instrument::applyDetectorResolution(OutputData<double>* p_intensity_map) const
{
    mP_detector->applyDetectorResolution(p_intensity_map);
}

OutputData<double>* Instrument::createDetectorIntensity(
    const std::vector<SimulationElement>& elements, IDetector2D::EAxesUnits units) const
{
    return mP_detector->createDetectorIntensity(elements, m_beam, units);
}

OutputData<double>* Instrument::createDetectorMap(IDetector2D::EAxesUnits units) const
{
    return mP_detector->createDetectorMap(m_beam, units);
}

void Instrument::print(std::ostream& ostr) const
{
    ostr << "Instrument: '" << getName() << "' " << getParameterPool() << std::endl;
    ostr << "    " << m_beam << std::endl;
    ostr << "    " << *mP_detector << std::endl;
}

void Instrument::setBeamParameters(double wavelength, double alpha_i, double phi_i)
{
    m_beam.setCentralK(wavelength, alpha_i, phi_i);
    if (mP_detector)
        initDetector();
}

const DetectorMask* Instrument::getDetectorMask() const { return getDetector()->getDetectorMask(); }

void Instrument::setBeam(const Beam& beam)
{
    m_beam = beam;
    if (mP_detector)
        initDetector();
}

void Instrument::setBeamIntensity(double intensity) { m_beam.setIntensity(intensity); }

void Instrument::setBeamPolarization(const kvector_t bloch_vector)
{
    m_beam.setPolarization(bloch_vector);
}

double Instrument::getBeamIntensity() const { return m_beam.getIntensity(); }

const IDetector2D* Instrument::getDetector() const { return mP_detector.get(); }

IDetector2D* Instrument::getDetector() { return mP_detector.get(); }

const IAxis& Instrument::getDetectorAxis(size_t index) const { return mP_detector->getAxis(index); }

size_t Instrument::getDetectorDimension() const { return mP_detector->getDimension(); }

void Instrument::setAnalyzerProperties(
    const kvector_t direction, double efficiency, double total_transmission)
{
    mP_detector->setAnalyzerProperties(direction, efficiency, total_transmission);
}
