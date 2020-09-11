// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Mask/Polygon.h
//! @brief     Defines class Polygon.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_CORE_MASK_POLYGON_H
#define BORNAGAIN_CORE_MASK_POLYGON_H

#include "Core/Mask/IShape2D.h"
#include <vector>

class PolygonPrivate;

//! A polygon in 2D space.
//! @ingroup mask

//! Polygon defined by two arrays with x and y coordinates of points.
//! Sizes of arrays should coincide.  If polygon is unclosed (the last point
//! doesn't repeat the first one), it will be closed automatically.

class BA_CORE_API_ Polygon : public IShape2D
{
public:
    Polygon(const std::vector<double> x, const std::vector<double> y);
    Polygon(const std::vector<std::vector<double>> points);
    Polygon(const PolygonPrivate* d);

    virtual ~Polygon();

    virtual Polygon* clone() const { return new Polygon(m_d); }

    virtual bool contains(double x, double y) const;
    virtual bool contains(const Bin1D& binx, const Bin1D& biny) const;

    double getArea() const;

    void getPoints(std::vector<double>& xpos, std::vector<double>& ypos) const;

protected:
    virtual void print(std::ostream& ostr) const;

private:
    PolygonPrivate* m_d;
};

#endif // BORNAGAIN_CORE_MASK_POLYGON_H
