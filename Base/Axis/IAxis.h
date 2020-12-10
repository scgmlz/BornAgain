//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Base/Axis/IAxis.h
//! @brief     Defines interface IAxis.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef USER_API
#ifndef BORNAGAIN_BASE_AXIS_IAXIS_H
#define BORNAGAIN_BASE_AXIS_IAXIS_H

#include "Base/Axis/Bin.h"
#include <vector>

//! Interface for one-dimensional axes.
//! @ingroup tools_internal

class IAxis {
public:
    //! constructors
    IAxis(const std::string& name) : m_name(name) {}

    //! clone function
    virtual IAxis* clone() const = 0;

    //! destructor
    virtual ~IAxis() {}

    //! retrieve the number of bins
    virtual size_t size() const = 0;

    //! retrieve the label of the axis
    std::string getName() const { return m_name; }

    //! Sets the axis label
    void setName(std::string name) { m_name = name; }

    //! indexed accessor retrieves a sample
    virtual double operator[](size_t index) const = 0;

    //! retrieve a 1d bin for the given index
    virtual Bin1D bin(size_t index) const = 0;

    //! Returns value of first point of axis
    virtual double lowerBound() const = 0;

    //! Returns value of last point of axis
    virtual double upperBound() const = 0;

    //! Returns distance from first to last point
    double span() const;

    //! Returns midpoint of axis
    double center() const;

    virtual double binCenter(size_t index) const = 0;

    //! find bin index which is best match for given value
    virtual size_t findClosestIndex(double value) const = 0;

    //! test for equality
    bool operator==(const IAxis& right) const { return equals(right); }
    bool operator!=(const IAxis& right) const { return !(*this == right); }

    friend std::ostream& operator<<(std::ostream& ostr, const IAxis& m) {
        m.print(ostr);
        return ostr;
    }

    virtual std::vector<double> binCenters() const;

    virtual std::vector<double> binBoundaries() const;

    //! Creates a new clipped axis
    virtual IAxis* createClippedAxis(double left, double right) const;

    //! Returns true if axis contains given point
    virtual bool contains(double value) const;

protected:
    virtual void print(std::ostream& ostr) const = 0;
    virtual bool equals(const IAxis& other) const; // overloaded in child classes

private:
    IAxis(const IAxis&);
    IAxis& operator=(const IAxis&);

    std::string m_name; //!< axis name
};

//! global helper function for comparison of axes
inline bool HaveSameNameAndShape(const IAxis& left, const IAxis& right) {
    return left == right;
}

#endif // BORNAGAIN_BASE_AXIS_IAXIS_H
#endif // USER_API
