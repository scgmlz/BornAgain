// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Mask/Line.h
//! @brief     Defines class Line.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef LINE_H
#define LINE_H

#include "IShape2D.h"

//! A line segment.
//! @ingroup mask

class  BA_CORE_API_ Line : public IShape2D {
public:
    Line(double x1, double y1, double x2, double y2);
    Line* clone() const { return new Line(m_x1, m_y1, m_x2, m_y2); }

    bool contains(double x, double y) const;
    bool contains(const Bin1D &binx, const Bin1D &biny) const;

private:
    double m_x1, m_y1, m_x2, m_y2;
};


//! An infinite vertical line.
//! @ingroup mask

class BA_CORE_API_ VerticalLine : public IShape2D {
public:
    VerticalLine(double x);
    VerticalLine* clone() const { return new VerticalLine(m_x); }

    bool contains(double x, double y) const;
    bool contains(const Bin1D& binx, const Bin1D& biny) const;

    double getXpos() const { return m_x; }

private:
    double m_x;
};


//! An infinite horizontal line.
//! @ingroup mask

class BA_CORE_API_ HorizontalLine : public IShape2D {
public:
    HorizontalLine(double y);
    HorizontalLine *clone() const { return new HorizontalLine(m_y); }

    bool contains(double x, double y) const;
    bool contains(const Bin1D& binx, const Bin1D& biny) const;

    double getYpos() const { return m_y; }

private:
    double m_y;
};

#endif // LINE_H
