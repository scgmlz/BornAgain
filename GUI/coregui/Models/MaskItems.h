// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/MaskItems.h
//! @brief     Defines MaskItems classes
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef MASKITEMS_H
#define MASKITEMS_H

#include "SessionItem.h"

class IShape2D;

//! Container holding various masks as children

class BA_CORE_API_ MaskContainerItem : public SessionItem
{
public:
    MaskContainerItem();
};


//! A base class for all mask items

class BA_CORE_API_ MaskItem : public SessionItem
{
public:
    static const QString P_MASK_VALUE;
    explicit MaskItem(const QString& name);
    virtual std::unique_ptr<IShape2D> createShape(double scale = 1.0) const;
};

class BA_CORE_API_ RectangleItem : public MaskItem
{
public:
    static const QString P_XLOW;
    static const QString P_YLOW;
    static const QString P_XUP;
    static const QString P_YUP;
    explicit RectangleItem(const QString& modelType = Constants::RectangleMaskType);
    virtual std::unique_ptr<IShape2D> createShape(double scale) const;
};

class BA_CORE_API_ RegionOfInterestItem : public RectangleItem
{
public:
    RegionOfInterestItem();
};


class BA_CORE_API_ PolygonPointItem : public SessionItem
{

public:
    static const QString P_POSX;
    static const QString P_POSY;
    PolygonPointItem();
};

class BA_CORE_API_ PolygonItem : public MaskItem
{

public:
    static const QString P_ISCLOSED;
    PolygonItem();
    virtual std::unique_ptr<IShape2D> createShape(double scale) const;
};

class BA_CORE_API_ VerticalLineItem : public MaskItem
{

public:
    static const QString P_POSX;
    VerticalLineItem();
    virtual std::unique_ptr<IShape2D> createShape(double scale) const;
};

class BA_CORE_API_ HorizontalLineItem : public MaskItem
{

public:
    static const QString P_POSY;
    HorizontalLineItem();
    virtual std::unique_ptr<IShape2D> createShape(double scale) const;
};

class BA_CORE_API_ EllipseItem : public MaskItem
{

public:
    static const QString P_XCENTER;
    static const QString P_YCENTER;
    static const QString P_XRADIUS;
    static const QString P_YRADIUS;
    static const QString P_ANGLE;
    EllipseItem();
    virtual std::unique_ptr<IShape2D> createShape(double scale) const;
};

class BA_CORE_API_ MaskAllItem : public MaskItem
{
public:
    MaskAllItem();
    virtual std::unique_ptr<IShape2D> createShape(double scale) const;
};

#endif // MASKITEMS_H
