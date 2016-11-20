// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Mask/Polygon.cpp
//! @brief     Implements class Polygon.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "Polygon.h"
#include "Bin.h"
#include "Exceptions.h"
#include "Macros.h"
GCC_DIAG_OFF(unused-parameter)
#include <boost/geometry.hpp>
#include <boost/geometry/geometries/point_xy.hpp>
GCC_DIAG_ON(unused-parameter)

using namespace boost::geometry;

//! The private data for polygons to hide boost dependency from the header
class PolygonPrivate {
public:
    typedef model::d2::point_xy<double> point_t;
    typedef model::polygon<point_t> polygon_t;
    polygon_t polygon;
    void init_from(const std::vector<double>& x, const std::vector<double>& y);
    void get_points(std::vector<double>& xpos, std::vector<double>& ypos);
};


void PolygonPrivate::init_from(const std::vector<double>& x, const std::vector<double>& y)
{
    if(x.size() != y.size())
        throw Exceptions::LogicErrorException(
            "Polygon::Polygon(const std::vector<double>& x, const std::vector<double>& y) "
            "Error. Sizes of arrays must conincide.");
    std::vector<point_t> points;
    for(size_t i=0; i<x.size(); ++i)
        points.push_back(point_t(x[i], y[i]));
    assign_points(polygon, points);
    correct(polygon);
}

void PolygonPrivate::get_points(std::vector<double>& xpos, std::vector<double>& ypos)
{
    xpos.clear();
    ypos.clear();
    for(auto it = polygon.outer().begin(); it != polygon.outer().end(); ++it ) {
         // for vectors of x and y, extract the x/y from the point
         xpos.push_back( boost::geometry::get<0>( *it ) );
         ypos.push_back( boost::geometry::get<1>( *it ) );
    }
}


//! @param x Vector of x-coordinates of polygon points.
//! @param y Vector of y-coordinates of polygon points.

// IMPORTANT Input parameters are not "const reference" to be able to work from python
// (auto convertion of python list to vector<double>).
Polygon::Polygon(const std::vector<double>& x, const std::vector<double>& y)
    : IShape2D("Polygon"), m_d(new PolygonPrivate)
{
    m_d->init_from(x, y);
}

// IMPORTANT Input parameter is not "const reference" to be able to work from python
// (auto convertion of python list to vector<vector<double>>).
    //! Polygon defined by two  dimensional array with (x,y) coordinates of polygon points.
    //! The size of second dimension should be 2. If polygon is unclosed (the last point
    //! doesn't repeat the first one), it will be closed automatically.
    //! @param points Two dimensional vector of (x,y) coordinates of polygon points.
Polygon::Polygon(const std::vector<std::vector<double>>& points)
    : IShape2D("Polygon"), m_d(new PolygonPrivate)
{
    std::vector<double> x;
    std::vector<double> y;
    for(size_t i=0; i<points.size(); ++i) {
        if(points[i].size() != 2)
            throw Exceptions::LogicErrorException(
                "Polygon(const std::vector<std::vector<double> >& points) -> Error. "
                " Should be two-dimensional array with second dimension of 2 size.");
        x.push_back(points[i][0]);
        y.push_back(points[i][1]);
    }
    m_d->init_from(x, y);
}

Polygon::Polygon(const PolygonPrivate* d)
    : IShape2D("Polygon"), m_d(new PolygonPrivate(*d))
{}

Polygon::~Polygon()
{
    delete m_d;
}

bool Polygon::contains(double x, double y) const
{
//    return within(PolygonPrivate::point_t(x, y), m_d->polygon); // not including borders
    return covered_by(PolygonPrivate::point_t(x, y), m_d->polygon); // including borders
}

bool Polygon::contains(const Bin1D& binx, const Bin1D& biny) const
{
    return contains(binx.getMidPoint(), biny.getMidPoint());
}

double Polygon::getArea() const
{
    return area(m_d->polygon);
}

void Polygon::getPoints(std::vector<double>& xpos, std::vector<double>& ypos) const
{
    m_d->get_points(xpos, ypos);
}

void Polygon::print(std::ostream &ostr) const
{
    ostr << wkt<PolygonPrivate::polygon_t>(m_d->polygon);
}
