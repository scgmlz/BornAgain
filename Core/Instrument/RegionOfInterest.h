// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Instrument/RegionOfInterest.h
//! @brief     Defines class RegionOfInterest.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef REGIONOFINTEREST_H
#define REGIONOFINTEREST_H

#include "ICloneable.h"
#include <memory>
#include <vector>

class Rectangle;
class IDetector2D;
class IAxis;
template<class T> class OutputData;

//! Defines rectangular area for the detector which will be simulated/fitted.
//! @ingroup simulation

class BA_CORE_API_ RegionOfInterest : public ICloneable
{
public:
    RegionOfInterest(const IDetector2D& detector,
                     double xlow, double ylow, double xup, double yup);
    RegionOfInterest(const OutputData<double>& data,
                     double xlow, double ylow, double xup, double yup);

    RegionOfInterest& operator=(const RegionOfInterest &other) = delete;
    RegionOfInterest* clone() const;
    ~RegionOfInterest();

    double getXlow() const;
    double getYlow() const;
    double getXup()  const;
    double getYup()  const;

    //! Converts roi index to the detector index.
    size_t detectorIndex(size_t roiIndex) const;

    //! Converts global detector index to ROI index.
    size_t roiIndex(size_t detectorIndex) const;

    //! Number of detector bins in ROI area
    size_t roiSize() const;

    //! Number of detector bins.
    size_t detectorSize() const;

    bool isInROI(size_t detectorIndex) const;

    std::unique_ptr<IAxis> clipAxisToRoi(size_t axis_index, const IAxis &axis) const;

private:
    RegionOfInterest(double xlow, double ylow, double xup, double yup);
    RegionOfInterest(const RegionOfInterest& other);

    size_t xcoord(size_t index, const std::vector<size_t> &dims) const;
    size_t ycoord(size_t index, const std::vector<size_t> &dims) const;

    void initFrom(const IAxis& x_axis, const IAxis& y_axis);

    std::unique_ptr<Rectangle> m_rectangle;
    //!< Number of bins on detector axes corresponding to roi-rectanle.
    size_t m_ax1, m_ay1, m_ax2, m_ay2;
    //!< Detector global index corresponding to the lower left corner of ROI
    size_t m_glob_index0;
    std::vector<size_t> m_detector_dims;
    std::vector<size_t> m_roi_dims;
};

inline
size_t RegionOfInterest::xcoord(size_t index, const std::vector<size_t>& dims) const
{
    return index/dims[1] % dims[0];
}

inline
size_t RegionOfInterest::ycoord(size_t index, const std::vector<size_t>& dims) const
{
    return index % dims[1];
}

#endif // REGIONOFINTEREST_H
