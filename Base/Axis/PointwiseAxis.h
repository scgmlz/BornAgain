//  ************************************************************************************************
//
//  BornAgain: simulate and fit reflection and scattering
//
//! @file      Base/Axis/PointwiseAxis.h
//! @brief     Defines class PointwiseAxis.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifdef SWIG
#error no need to expose this header to Swig
#endif

#ifndef USER_API
#ifndef BORNAGAIN_BASE_AXIS_POINTWISEAXIS_H
#define BORNAGAIN_BASE_AXIS_POINTWISEAXIS_H

#include "Base/Axis/IAxis.h"

//! Axis containing arbitrary (non-equidistant) coordinate values.
//! Lower boundary of the first bin and upper boundary of the
//! last bin correspond to first and last passed coordinates.
//! Other bin boundaries are computed as arithmetical mean of
//! two adjacent coordinates.
//! One should be aware, that bin centers reported
//! by PointwiseAxis::binCenter do not coincide with the
//! values produced by Bin1D::getMidPoint.
//! On-axis values are bounded by minimum/maximum
//! values passed to the constructor.
//! @ingroup tools

class PointwiseAxis : public IAxis {
public:
    template <class String, class Vector>
    PointwiseAxis(String&& name, Vector&& coordinate_values)
        : IAxis(std::forward<String>(name)), m_coordinates(std::forward<Vector>(coordinate_values))
    {
        sanityCheck();
    }

    //! clone function
    PointwiseAxis* clone() const override;

    ~PointwiseAxis() override = default;

    //! retrieve the number of bins
    size_t size() const override { return m_coordinates.size(); }

    //! indexed accessor retrieves a sample
    double operator[](size_t index) const override { return binCenter(index); }

    //! retrieve a 1d bin for the given index
    Bin1D bin(size_t index) const override;

    //! Returns value of first on-axis point
    double lowerBound() const override;

    //! Returns value of last on-axis point
    double upperBound() const override;

    //! Returns the coordinate corresponding to the
    //! given index. For this type of axis ("pointwise")
    //! this equals returning an explicitly defined coordinate.
    double binCenter(size_t index) const override;

    //! find index of the coordinate closest to the given value
    size_t findClosestIndex(double value) const override;

    std::vector<double> binCenters() const override { return m_coordinates; }

    std::vector<double> binBoundaries() const override;

    //! Creates a new clipped axis
    PointwiseAxis* createClippedAxis(double left, double right) const override;

private:
    void print(std::ostream& ostr) const override;
    bool equals(const IAxis& other) const override;

    double lowerBoundary(size_t index) const;
    double upperBoundary(size_t index) const;
    void checkIndex(size_t index) const;
    void sanityCheck() const;

    std::vector<double> m_coordinates;
};

#endif // BORNAGAIN_BASE_AXIS_POINTWISEAXIS_H
#endif // USER_API
