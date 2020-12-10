//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Device/Detector/RegionOfInterest.cpp
//! @brief     Implements class RegionOfInterest.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "Device/Detector/RegionOfInterest.h"
#include "Device/Detector/IDetector2D.h"
#include "Device/Mask/Rectangle.h"

RegionOfInterest::RegionOfInterest(const IDetector2D& detector, double xlow, double ylow,
                                   double xup, double yup)
    : RegionOfInterest(xlow, ylow, xup, yup) {
    initFrom(detector.axis(0), detector.axis(1));
}

RegionOfInterest::RegionOfInterest(const OutputData<double>& data, double xlow, double ylow,
                                   double xup, double yup)
    : RegionOfInterest(xlow, ylow, xup, yup) {
    if (data.rank() != 2)
        throw std::runtime_error("RegionOfInterest::RegionOfInterest() -> Error. "
                                 "Data is not two-dimensional.");

    initFrom(data.axis(0), data.axis(1));
}

RegionOfInterest::RegionOfInterest(double xlow, double ylow, double xup, double yup)
    : m_rectangle(new Rectangle(xlow, ylow, xup, yup))
    , m_ax1(0)
    , m_ay1(0)
    , m_ax2(0)
    , m_ay2(0)
    , m_glob_index0(0) {}

RegionOfInterest* RegionOfInterest::clone() const {
    return new RegionOfInterest(*this);
}

RegionOfInterest::~RegionOfInterest() = default;

RegionOfInterest::RegionOfInterest(const RegionOfInterest& other)
    : ICloneable()
    , m_rectangle(other.m_rectangle->clone())
    , m_ax1(other.m_ax1)
    , m_ay1(other.m_ay1)
    , m_ax2(other.m_ax2)
    , m_ay2(other.m_ay2)
    , m_glob_index0(other.m_glob_index0)
    , m_detector_dims(other.m_detector_dims)
    , m_roi_dims(other.m_roi_dims) {}

double RegionOfInterest::getXlow() const {
    return m_rectangle->getXlow();
}

double RegionOfInterest::getYlow() const {
    return m_rectangle->getYlow();
}

double RegionOfInterest::getXup() const {
    return m_rectangle->getXup();
}

double RegionOfInterest::getYup() const {
    return m_rectangle->getYup();
}

size_t RegionOfInterest::detectorIndex(size_t roiIndex) const {
    return m_glob_index0 + ycoord(roiIndex, m_roi_dims)
           + xcoord(roiIndex, m_roi_dims) * m_detector_dims[1];
}

size_t RegionOfInterest::roiIndex(size_t globalIndex) const {
    size_t ny = ycoord(globalIndex, m_detector_dims);
    if (ny < m_ay1 || ny > m_ay2)
        throw std::runtime_error("RegionOfInterest::roiIndex() -> Error.");

    size_t nx = xcoord(globalIndex, m_detector_dims);
    if (nx < m_ax1 || nx > m_ax2)
        throw std::runtime_error("RegionOfInterest::roiIndex() -> Error.");

    return ny - m_ay1 + (nx - m_ax1) * m_roi_dims[1];
}

size_t RegionOfInterest::roiSize() const {
    return m_roi_dims[0] * m_roi_dims[1];
}

size_t RegionOfInterest::detectorSize() const {
    return m_detector_dims[0] * m_detector_dims[1];
}

bool RegionOfInterest::isInROI(size_t detectorIndex) const {
    size_t ny = ycoord(detectorIndex, m_detector_dims);
    if (ny < m_ay1 || ny > m_ay2)
        return false;
    size_t nx = xcoord(detectorIndex, m_detector_dims);
    if (nx < m_ax1 || nx > m_ax2)
        return false;
    return true;
}

std::unique_ptr<IAxis> RegionOfInterest::clipAxisToRoi(size_t axis_index, const IAxis& axis) const {
    size_t nbin1 = (axis_index == 0 ? m_ax1 : m_ay1);
    size_t nbin2 = (axis_index == 0 ? m_ax2 : m_ay2);
    return std::unique_ptr<IAxis>(new FixedBinAxis(
        axis.getName(), nbin2 - nbin1 + 1, axis.bin(nbin1).m_lower, axis.bin(nbin2).m_upper));
}

void RegionOfInterest::initFrom(const IAxis& x_axis, const IAxis& y_axis) {
    m_detector_dims.push_back(x_axis.size());
    m_detector_dims.push_back(y_axis.size());

    m_ax1 = x_axis.findClosestIndex(getXlow());
    m_ax2 = x_axis.findClosestIndex(getXup());
    m_ay1 = y_axis.findClosestIndex(getYlow());
    m_ay2 = y_axis.findClosestIndex(getYup());

    m_roi_dims.push_back(m_ax2 - m_ax1 + 1);
    m_roi_dims.push_back(m_ay2 - m_ay1 + 1);

    m_glob_index0 = m_ay1 + m_ax1 * m_detector_dims[1];
}
