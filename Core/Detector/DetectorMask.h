// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Detector/DetectorMask.h
//! @brief     Defines class DetectorMask.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_CORE_DETECTOR_DETECTORMASK_H
#define BORNAGAIN_CORE_DETECTOR_DETECTORMASK_H

#include "Core/Intensity/OutputData.h"
#include "Core/Mask/IShape2D.h"

class IDetector2D;
template <class T> class OutputData;
class Histogram2D;

//! Collection of detector masks.
//! @ingroup detector

class DetectorMask
{
public:
    DetectorMask();
    DetectorMask(const DetectorMask& other);
    DetectorMask& operator=(const DetectorMask& other);

    //! Add mask to the stack of detector masks.
    //! The value "true" means that the area will be excluded from the analysis.
    //! @param shape The shape of mask.
    //! @param mask_value The value of mask
    void addMask(const IShape2D& shape, bool mask_value);

    //! Init the map of masks for the given detector plane
    void initMaskData(const IDetector2D& detector);

    void initMaskData(const OutputData<double>& data);

    bool isMasked(size_t index) const;

    const OutputData<bool>* getMaskData() const { return &m_mask_data; }

    Histogram2D* createHistogram() const;

    //! remove all masks and return object to initial state
    void removeMasks();

    //! returns true if has masks
    bool hasMasks() const { return !m_shapes.empty(); }

    int numberOfMaskedChannels() const { return m_number_of_masked_channels; }

    size_t numberOfMasks() const;

    const IShape2D* getMaskShape(size_t mask_index, bool& mask_value) const;

private:
    void process_masks();

    SafePointerVector<IShape2D> m_shapes;
    std::vector<bool> m_mask_of_shape;
    OutputData<bool> m_mask_data;
    int m_number_of_masked_channels;
};

#endif // BORNAGAIN_CORE_DETECTOR_DETECTORMASK_H
