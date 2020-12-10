//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Device/Instrument/Instrument.cpp
//! @brief     Implements class Instrument.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "Device/Instrument/Instrument.h"
#include "Device/Detector/SphericalDetector.h"
#include "Device/Histo/Histogram2D.h"
#include "Device/Resolution/IResolutionFunction2D.h"

Instrument::Instrument(const Beam& beam, const IDetector& detector)
    : m_beam(beam), m_detector(detector.clone()) {
    setName("Instrument");
    registerChild(m_detector.get());
    registerChild(&m_beam);
    initDetector();
}

Instrument::Instrument() : Instrument(Beam::horizontalBeam(), SphericalDetector()) {}

Instrument::Instrument(const Instrument& other) : INode(), m_beam(other.m_beam) {
    if (other.m_detector)
        setDetector(*other.m_detector);
    registerChild(&m_beam);
    setName(other.getName());
}

Instrument::~Instrument() = default;

Instrument& Instrument::operator=(const Instrument& other) {
    if (this != &other) {
        m_beam = other.m_beam;
        registerChild(&m_beam);
        if (other.m_detector)
            setDetector(*other.m_detector);
    }
    return *this;
}

void Instrument::setDetector(const IDetector& detector) {
    m_detector.reset(detector.clone());
    registerChild(m_detector.get());
    initDetector();
}

void Instrument::initDetector() {
    if (!m_detector)
        throw std::runtime_error(
            "Instrument::initDetector() -> Error. Detector is not initialized.");
    m_detector->init(beam());
}

std::vector<const INode*> Instrument::getChildren() const {
    std::vector<const INode*> result;
    result.push_back(&m_beam);
    if (m_detector)
        result.push_back(m_detector.get());
    return result;
}

void Instrument::setBeamParameters(double wavelength, double alpha_i, double phi_i) {
    m_beam.setWavelength(wavelength);
    m_beam.setDirection({alpha_i, phi_i});
    if (m_detector)
        initDetector();
}

void Instrument::setBeam(const Beam& beam) {
    m_beam = beam;
    if (m_detector)
        initDetector();
}

const IDetector* Instrument::getDetector() const {
    ASSERT(m_detector);
    return m_detector.get();
}

const IDetector& Instrument::detector() const {
    ASSERT(m_detector);
    return *m_detector;
}

IDetector& Instrument::detector() {
    ASSERT(m_detector);
    return *m_detector;
}

IDetector2D& Instrument::detector2D() {
    ASSERT(m_detector);
    IDetector2D* p = dynamic_cast<IDetector2D*>(m_detector.get());
    if (!p)
        throw std::runtime_error("Error: Detector is not twodimensional");
    return *p;
}

const IDetector2D& Instrument::detector2D() const {
    ASSERT(m_detector);
    IDetector2D* const p = dynamic_cast<IDetector2D* const>(m_detector.get());
    if (!p)
        throw std::runtime_error("Error: Detector is not twodimensional");
    return *p;
}
