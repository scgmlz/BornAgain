// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Binning/IAxis.h
//! @brief     Defines class IAxis.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef IAXIS_H
#define IAXIS_H

#include "Bin.h"
#include <vector>

//! Interface for one-dimensional axes.
//! @ingroup tools_internal

class BA_CORE_API_ IAxis
{
public:
    //! constructors
    IAxis(const std::string& name) : m_name(name) {}

    //! clone function
    virtual IAxis* clone() const=0;

    //! Creates a new axis with half the number of bins
    virtual IAxis* createDoubleBinSize() const;

    //! destructor
    virtual ~IAxis() {}

    //! retrieve the number of bins
    virtual size_t size() const=0;

    //! retrieve the label of the axis
    std::string getName() const { return m_name; }

    //! Sets the axis label
    void setName(std::string name) { m_name = name; }

    //! indexed accessor retrieves a sample
    virtual double operator[](size_t index) const=0;

    //! retrieve a 1d bin for the given index
    virtual Bin1D getBin(size_t index) const=0;

    //! Returns value of first point of axis
    virtual double getMin() const=0;

    //! Returns value of last point of axis
    virtual double getMax() const=0;

    virtual double getBinCenter(size_t index) const=0;

    //! find bin index which is best match for given value
    virtual size_t findClosestIndex(double value) const=0;

    //! find index of bin that contains the given value
    //! returns size() when value is not found
    size_t findIndex(double value) const;

    //! test for equality
    bool operator==(const IAxis& right) const { return equals(right); }
    bool operator!=(const IAxis& right) const { return !(*this==right); }

    friend std::ostream& operator<<(std::ostream& ostr, const IAxis& m) {
        m.print(ostr); return ostr; }

    virtual std::vector<double> getBinCenters() const;

    virtual std::vector<double> getBinBoundaries() const;

    //! Creates a new clipped axis
    virtual IAxis* createClippedAxis(double left, double right) const;

    //! Returns true if axis contains given point
    virtual bool contains(double value) const;

protected:
    virtual void print(std::ostream& ostr) const=0;
    virtual bool equals(const IAxis& other) const; // overloaded in child classes
    std::string m_name;  //!< axis label

private:
    IAxis(const IAxis&);
    IAxis& operator=(const IAxis&);
};

//! global helper function for comparison of axes
inline bool HaveSameNameAndShape(const IAxis& left, const IAxis& right)
{
    return left == right;
}

#endif // IAXIS_H
