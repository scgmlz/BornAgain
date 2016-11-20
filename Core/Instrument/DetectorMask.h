// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Instrument/DetectorMask.h
//! @brief     Defines class DetectorMask.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef DETECTORMASK_H
#define DETECTORMASK_H

#include "IShape2D.h"
#include "OutputData.h"

class IDetector2D;
template <class T> class OutputData;
class Histogram2D;

//! Collection of detector masks.
//! @ingroup simulation

class BA_CORE_API_ DetectorMask
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
    bool hasMasks() const { return numberOfMasks()>0; }

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

#endif // DETECTORMASK_H
