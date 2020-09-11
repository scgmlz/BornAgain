// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Detector/DetectorMask.cpp
//! @brief     Implements class DetectorMask.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Core/Detector/IDetector2D.h"
#include "Core/Detector/RegionOfInterest.h"
#include "Core/Intensity/Histogram2D.h"

DetectorMask::DetectorMask() : m_number_of_masked_channels(0) {}

DetectorMask::DetectorMask(const DetectorMask& other)
    : m_shapes(other.m_shapes), m_mask_of_shape(other.m_mask_of_shape),
      m_number_of_masked_channels(other.m_number_of_masked_channels)
{
    m_mask_data.copyFrom(other.m_mask_data);
}

DetectorMask& DetectorMask::operator=(const DetectorMask& other)
{
    if (this != &other) {
        m_shapes = other.m_shapes;
        m_mask_of_shape = other.m_mask_of_shape;
        m_mask_data.copyFrom(other.m_mask_data);
        m_number_of_masked_channels = other.m_number_of_masked_channels;
        //        DetectorMask tmp(other);
        //        tmp.swapContent(*this);
    }
    return *this;
}

void DetectorMask::addMask(const IShape2D& shape, bool mask_value)
{
    m_shapes.push_back(shape.clone());
    m_mask_of_shape.push_back(mask_value);
    m_mask_data.clear();
    m_number_of_masked_channels = 0;
}

void DetectorMask::initMaskData(const IDetector2D& detector)
{
    if (detector.dimension() != 2)
        throw Exceptions::RuntimeErrorException("DetectorMask::initMaskData() -> Error. Attempt "
                                                "to add masks to uninitialized detector.");

    ASSERT(m_shapes.size() == m_mask_of_shape.size());
    m_mask_data.clear();

    for (size_t dim = 0; dim < detector.dimension(); ++dim) {
        const IAxis& axis = detector.getAxis(dim);
        m_mask_data.addAxis(axis);
    }

    process_masks();
}

void DetectorMask::initMaskData(const OutputData<double>& data)
{
    ASSERT(m_shapes.size() == m_mask_of_shape.size());
    m_mask_data.clear();

    for (size_t dim = 0; dim < data.getRank(); ++dim)
        m_mask_data.addAxis(data.getAxis(dim));

    process_masks();
}

bool DetectorMask::isMasked(size_t index) const
{
    return m_number_of_masked_channels == 0 ? false : m_mask_data[index];
}

Histogram2D* DetectorMask::createHistogram() const
{
    OutputData<double> data;
    data.copyShapeFrom(m_mask_data);
    for (size_t i = 0; i < m_mask_data.getAllocatedSize(); ++i)
        data[i] = static_cast<double>(m_mask_data[i]);
    return dynamic_cast<Histogram2D*>(IHistogram::createHistogram(data));
}

void DetectorMask::removeMasks()
{
    m_shapes.clear();
    m_mask_of_shape.clear();
    m_mask_data.clear();
}

size_t DetectorMask::numberOfMasks() const
{
    return m_shapes.size();
}

const IShape2D* DetectorMask::getMaskShape(size_t mask_index, bool& mask_value) const
{
    if (mask_index >= numberOfMasks())
        return nullptr;
    mask_value = m_mask_of_shape[mask_index];
    return m_shapes[mask_index];
}

void DetectorMask::process_masks()
{
    m_mask_data.setAllTo(false);
    if (!m_shapes.size())
        return;

    m_number_of_masked_channels = 0;
    for (size_t index = 0; index < m_mask_data.getAllocatedSize(); ++index) {
        Bin1D binx = m_mask_data.getAxisBin(index, 0);
        Bin1D biny = m_mask_data.getAxisBin(index, 1);
        // setting mask to the data starting from last shape added
        bool is_masked(false);
        for (size_t i_shape = m_shapes.size(); i_shape > 0; --i_shape) {
            const IShape2D* shape = m_shapes[i_shape - 1];
            if (shape->contains(binx, biny)) {
                if (m_mask_of_shape[i_shape - 1])
                    is_masked = true;
                m_mask_data[index] = m_mask_of_shape[i_shape - 1];
                break; // index is covered by the shape, stop looking further
            }
        }
        if (is_masked)
            ++m_number_of_masked_channels;
    }
}
