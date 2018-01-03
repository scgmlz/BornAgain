// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Instrument/IDetector2D.cpp
//! @brief     Implements shared functionality of interface IDetector2D.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "IDetector2D.h"
#include "Beam.h"
#include "InfinitePlane.h"
#include "SimulationArea.h"
#include "SimulationElement.h"
#include "SimulationElementsProvider.h"
#include "BornAgainNamespace.h"
#include "Units.h"
#include "RegionOfInterest.h"
#include "DetectorFunctions.h"

IDetector2D::IDetector2D() = default;

IDetector2D::IDetector2D(const IDetector2D &other)
    : IDetector(other)
    , m_detector_mask(other.m_detector_mask)
{
    if(other.regionOfInterest())
        m_region_of_interest.reset(other.regionOfInterest()->clone());
}

IDetector2D::~IDetector2D() = default;

void IDetector2D::setDetectorParameters(size_t n_x, double x_min, double x_max,
                                        size_t n_y, double y_min, double y_max)
{
    clear();
    addAxis(*createAxis(BornAgain::X_AXIS_INDEX, n_x, x_min, x_max));
    addAxis(*createAxis(BornAgain::Y_AXIS_INDEX, n_y, y_min, y_max));
}

void IDetector2D::setDetectorAxes(const IAxis &axis0, const IAxis &axis1)
{
    clear();
    addAxis(axis0);
    addAxis(axis1);
}

const RegionOfInterest *IDetector2D::regionOfInterest() const
{
    return m_region_of_interest.get();
}

void IDetector2D::setRegionOfInterest(double xlow, double ylow, double xup, double yup)
{
    m_region_of_interest.reset(new RegionOfInterest(*this, xlow, ylow, xup, yup));
    m_detector_mask.initMaskData(*this);
}

void IDetector2D::resetRegionOfInterest()
{
    m_region_of_interest.reset();
    m_detector_mask.initMaskData(*this);
}

void IDetector2D::removeMasks()
{
    m_detector_mask.removeMasks();
}

void IDetector2D::addMask(const IShape2D &shape, bool mask_value)
{
    m_detector_mask.addMask(shape, mask_value);
    m_detector_mask.initMaskData(*this);
}

void IDetector2D::maskAll()
{
    if(dimension() != 2) return;
    m_detector_mask.removeMasks();
    addMask(InfinitePlane(), true);
}

const DetectorMask* IDetector2D::detectorMask() const
{
    return &m_detector_mask;
}

std::unique_ptr<ISimulationElementsProvider> IDetector2D::createSimulationElements(const Beam &beam)
{
    auto agent = std::make_unique<SimulationElementsProvider<SimulationElement>>();
    auto& elements = agent->getElementVector();

    const double wavelength = beam.getWavelength();
    const double alpha_i = - beam.getAlpha();  // Defined to be always positive in Beam
    const double phi_i = beam.getPhi();
    const Eigen::Matrix2cd& beam_polarization = beam.getPolarization();
    const Eigen::Matrix2cd& analyzer_operator = detectionProperties().analyzerOperator();

    if (!detectorMask()->hasMasks())
        m_detector_mask.initMaskData(*this);
    size_t spec_index = getIndexOfSpecular(beam);

    SimulationArea area(this);
    elements.reserve(area.totalSize());
    for(SimulationArea::iterator it = area.begin(); it!=area.end(); ++it) {
        elements.emplace_back(wavelength, alpha_i, phi_i,
                            std::unique_ptr<IPixel>(createPixel(it.detectorIndex())));
        auto& sim_element = elements.back();
        sim_element.setPolarization(beam_polarization);
        sim_element.setAnalyzerOperator(analyzer_operator);
        if (it.index()==spec_index)
            sim_element.setSpecular();
    }

    return agent;
}

SimulationElement IDetector2D::getSimulationElement(size_t index, const Beam &beam) const
{
    double wavelength = beam.getWavelength();
    double alpha_i = - beam.getAlpha();  // Defined to be always positive in Beam
    double phi_i = beam.getPhi();
    return SimulationElement(wavelength, alpha_i, phi_i,
                             std::unique_ptr<IPixel>(createPixel(index)));
}

void IDetector2D::calculateAxisRange(size_t axis_index, const Beam &beam,
        AxesUnits units, double &amin, double &amax) const
{
    if(units == AxesUnits::QYQZ && axis_index == BornAgain::X_AXIS_INDEX) {
        const IAxis &aX = getAxis(BornAgain::X_AXIS_INDEX);
        SimulationElement el_left_bottom
            = getSimulationElement(getGlobalIndex(0, 0), beam);
        SimulationElement el_right_bottom
            = getSimulationElement(getGlobalIndex(aX.size()-1, 0), beam);
        amin = el_left_bottom.getQ(0.0, 0.0).y();
        amax = el_right_bottom.getQ(1.0, 0.0).y();

    } else if(units == AxesUnits::QYQZ && axis_index == BornAgain::Y_AXIS_INDEX) {
        const IAxis &aX = getAxis(BornAgain::X_AXIS_INDEX);
        const IAxis &aY = getAxis(BornAgain::Y_AXIS_INDEX);
        SimulationElement el_center_bottom
            = getSimulationElement(getGlobalIndex(aX.size()/2, 0), beam);
        SimulationElement el_center_top
            = getSimulationElement(getGlobalIndex(aX.size()/2, aY.size()-1), beam);
        amin = -el_center_bottom.getQ(0.5, 0.0).z();
        amax = -el_center_top.getQ(0.5, 1.0).z();

    } else
        return IDetector::calculateAxisRange(axis_index, beam, units, amin, amax);
}

size_t IDetector2D::getGlobalIndex(size_t x, size_t y) const
{
    if (dimension() != 2)
        return totalSize();
    return x * getAxis(1).size() + y;
}

