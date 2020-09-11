// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Detector/IDetector2D.cpp
//! @brief     Implements shared functionality of interface IDetector2D.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Core/Detector/IDetector2D.h"
#include "Core/Basics/Units.h"
#include "Core/Beam/Beam.h"
#include "Core/Detector/DetectorContext.h"
#include "Core/Detector/DetectorFunctions.h"
#include "Core/Detector/RegionOfInterest.h"
#include "Core/Detector/SimulationArea.h"
#include "Core/Mask/InfinitePlane.h"
#include "Core/SimulationElement/SimulationElement.h"

IDetector2D::IDetector2D() = default;

IDetector2D::IDetector2D(const IDetector2D& other)
    : IDetector(other), m_detector_mask(other.m_detector_mask)
{
    if (other.regionOfInterest())
        m_region_of_interest.reset(other.regionOfInterest()->clone());
}

IDetector2D::~IDetector2D() = default;

void IDetector2D::setDetectorParameters(size_t n_x, double x_min, double x_max, size_t n_y,
                                        double y_min, double y_max)
{
    clear();
    addAxis(*createAxis(0, n_x, x_min, x_max));
    addAxis(*createAxis(1, n_y, y_min, y_max));
}

void IDetector2D::setDetectorAxes(const IAxis& axis0, const IAxis& axis1)
{
    clear();
    addAxis(axis0);
    addAxis(axis1);
}

const RegionOfInterest* IDetector2D::regionOfInterest() const
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

std::vector<size_t> IDetector2D::active_indices() const
{
    std::vector<size_t> result;
    SimulationArea area(this);
    for (SimulationArea::iterator it = area.begin(); it != area.end(); ++it)
        result.push_back(it.detectorIndex());
    return result;
}

std::unique_ptr<DetectorContext> IDetector2D::createContext() const
{
    return std::make_unique<DetectorContext>(this);
}

void IDetector2D::removeMasks()
{
    m_detector_mask.removeMasks();
}

void IDetector2D::addMask(const IShape2D& shape, bool mask_value)
{
    m_detector_mask.addMask(shape, mask_value);
    m_detector_mask.initMaskData(*this);
}

void IDetector2D::maskAll()
{
    if (dimension() != 2)
        return;
    m_detector_mask.removeMasks();
    addMask(InfinitePlane(), true);
}

const DetectorMask* IDetector2D::detectorMask() const
{
    return &m_detector_mask;
}

size_t IDetector2D::getGlobalIndex(size_t x, size_t y) const
{
    if (dimension() != 2)
        return totalSize();
    return x * getAxis(1).size() + y;
}
