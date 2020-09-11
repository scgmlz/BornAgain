// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Instrument/Instrument.cpp
//! @brief     Implements class Instrument.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Core/Instrument/Instrument.h"
#include "Core/Beam/Beam.h"
#include "Core/Detector/DetectorFunctions.h"
#include "Core/Detector/IResolutionFunction2D.h"
#include "Core/Detector/SphericalDetector.h"
#include "Core/Intensity/Histogram2D.h"
#include "Core/SimulationElement/SimulationElement.h"

Instrument::Instrument() : mP_detector(new SphericalDetector), m_beam(Beam::horizontalBeam())
{
    setName("Instrument");
    registerChild(mP_detector.get());
    registerChild(&m_beam);
}

Instrument::Instrument(const Instrument& other) : m_beam(other.m_beam)
{
    if (other.mP_detector)
        setDetector(*other.mP_detector);
    registerChild(&m_beam);
    setName(other.getName());
}

Instrument::~Instrument() {}

Instrument& Instrument::operator=(const Instrument& other)
{
    if (this != &other) {
        m_beam = other.m_beam;
        registerChild(&m_beam);
        if (other.mP_detector)
            setDetector(*other.mP_detector);
    }
    return *this;
}

void Instrument::setDetector(const IDetector& detector)
{
    mP_detector.reset(detector.clone());
    registerChild(mP_detector.get());
    initDetector();
}

void Instrument::initDetector()
{
    if (!mP_detector)
        throw Exceptions::RuntimeErrorException(
            "Instrument::initDetector() -> Error. Detector is not initialized.");
    getDetector()->init(getBeam());
}

std::vector<const INode*> Instrument::getChildren() const
{
    std::vector<const INode*> result;
    result.push_back(&m_beam);
    if (mP_detector)
        result.push_back(mP_detector.get());
    return result;
}

void Instrument::setDetectorResolutionFunction(const IResolutionFunction2D& p_resolution_function)
{
    mP_detector->setResolutionFunction(p_resolution_function);
}

void Instrument::removeDetectorResolution()
{
    mP_detector->removeDetectorResolution();
}

void Instrument::applyDetectorResolution(OutputData<double>* p_intensity_map) const
{
    mP_detector->applyDetectorResolution(p_intensity_map);
}

OutputData<double>*
Instrument::createDetectorIntensity(const std::vector<SimulationElement>& elements) const
{
    return mP_detector->createDetectorIntensity(elements);
}

void Instrument::setBeamParameters(double wavelength, double alpha_i, double phi_i)
{
    m_beam.setCentralK(wavelength, alpha_i, phi_i);
    if (mP_detector)
        initDetector();
}

const DetectorMask* Instrument::getDetectorMask() const
{
    return getDetector()->detectorMask();
}

void Instrument::setBeam(const Beam& beam)
{
    m_beam = beam;
    if (mP_detector)
        initDetector();
}

void Instrument::setBeamIntensity(double intensity)
{
    m_beam.setIntensity(intensity);
}

void Instrument::setBeamPolarization(const kvector_t bloch_vector)
{
    m_beam.setPolarization(bloch_vector);
}

double Instrument::getBeamIntensity() const
{
    return m_beam.getIntensity();
}

const IDetector* Instrument::getDetector() const
{
    return mP_detector.get();
}

IDetector* Instrument::getDetector()
{
    return mP_detector.get();
}

const IAxis& Instrument::getDetectorAxis(size_t index) const
{
    return mP_detector->getAxis(index);
}

size_t Instrument::getDetectorDimension() const
{
    return mP_detector->dimension();
}

void Instrument::setAnalyzerProperties(const kvector_t direction, double efficiency,
                                       double total_transmission)
{
    mP_detector->setAnalyzerProperties(direction, efficiency, total_transmission);
}
