// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Mask/Line.cpp
//! @brief     Implements class Line.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "Line.h"
#include "Bin.h"
#include "Macros.h"
#include "Numeric.h"
#include <limits>
GCC_DIAG_OFF(unused-parameter)
#include <boost/geometry.hpp>
#include <boost/geometry/geometries/point_xy.hpp>
GCC_DIAG_ON(unused-parameter)

using namespace boost::geometry;
typedef model::d2::point_xy<double> point_t;
typedef model::box<point_t> box_t;
typedef model::linestring<point_t> line_t;

Line::Line(double x1, double y1, double x2, double y2)
    : IShape2D("Line"), m_x1(x1), m_y1(y1), m_x2(x2), m_y2(y2)
{}

bool Line::contains(double x, double y) const
{
    point_t p(x, y);
    line_t line;
    line.push_back(point_t(m_x1, m_y1));
    line.push_back(point_t(m_x2, m_y2));

    double d = distance(p, line);

    return d<std::numeric_limits<double>::epsilon();
}

// Calculates if line crosses the box made out of our bins.
// Ugly implementation, see discussion at http://stackoverflow.com/questions/21408977
bool Line::contains(const Bin1D& binx, const Bin1D& biny) const
{
    std::vector<point_t> box_points;
    box_points.push_back(point_t(binx.m_lower, biny.m_lower));
    box_points.push_back(point_t(binx.m_lower, biny.m_upper));
    box_points.push_back(point_t(binx.m_upper, biny.m_upper));
    box_points.push_back(point_t(binx.m_upper, biny.m_lower));
    box_points.push_back(point_t(binx.m_lower, biny.m_lower));

    std::vector<point_t> line_points;
    line_points.push_back(point_t(m_x1, m_y1));
    line_points.push_back(point_t(m_x2, m_y2));

    return intersects(line_t(box_points.begin(),box_points.end()),
                      line_t(line_points.begin(),line_points.end()));
}


// ------------------------------------------------------------------------- //

//! @param x The value at which it crosses x-axes
VerticalLine::VerticalLine(double x)
    : IShape2D("VerticalLine"), m_x(x)
{}

bool VerticalLine::contains(double x, double /*y*/) const
{
    return Numeric::areAlmostEqual(x, m_x);
}

bool VerticalLine::contains(const Bin1D& binx, const Bin1D& /*biny*/) const
{
    return m_x>=binx.m_lower && m_x <= binx.m_upper;
}


// ------------------------------------------------------------------------- //

//! @param y The value at which it crosses y-axes
HorizontalLine::HorizontalLine(double y)
    : IShape2D("HorizontalLine"), m_y(y)
{}

bool HorizontalLine::contains(double /*x*/, double y) const
{
    return Numeric::areAlmostEqual(y, m_y);
}

bool HorizontalLine::contains(const Bin1D& /*binx*/, const Bin1D& biny) const
{
    return m_y>=biny.m_lower && m_y <= biny.m_upper;
}
