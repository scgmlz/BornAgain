// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Binning/PointwiseAxis.h
//! @brief     Defines class PointwiseAxis.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_CORE_BINNING_POINTWISEAXIS_H
#define BORNAGAIN_CORE_BINNING_POINTWISEAXIS_H

#include "Core/Binning/IAxis.h"

//! Axis containing arbitrary (non-equidistant) coordinate values.
//! Lower boundary of the first bin and upper boundary of the
//! last bin correspond to first and last passed coordinates.
//! Other bin boundaries are computed as arithmetical mean of
//! two adjacent coordinates.
//! One should be aware, that bin centers reported
//! by PointwiseAxis::getBinCenter do not coincide with the
//! values produced by Bin1D::getMidPoint.
//! On-axis values are bounded by minimum/maximum
//! values passed to the constructor.
//! @ingroup tools

class BA_CORE_API_ PointwiseAxis : public IAxis
{
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
    double operator[](size_t index) const override { return getBinCenter(index); }

    //! retrieve a 1d bin for the given index
    Bin1D getBin(size_t index) const override;

    //! Returns value of first on-axis point
    double getMin() const override;

    //! Returns value of last on-axis point
    double getMax() const override;

    //! Returns the coordinate corresponding to the
    //! given index.
    double getBinCenter(size_t index) const override;

    //! find index of the coordinate closest to the given value
    size_t findClosestIndex(double value) const override;

    std::vector<double> getBinCenters() const override { return m_coordinates; }

    std::vector<double> getBinBoundaries() const override;

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

#endif // BORNAGAIN_CORE_BINNING_POINTWISEAXIS_H
