// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/MaskItems.cpp
//! @brief     Implements MaskItems classes
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "MaskItems.h"
#include "Ellipse.h"
#include "GUIHelpers.h"
#include "InfinitePlane.h"
#include "Line.h"
#include "Polygon.h"
#include "Rectangle.h"


MaskContainerItem::MaskContainerItem()
    : SessionItem(Constants::MaskContainerType)
{
    const QString T_MASKS = "Mask Tag";
    QStringList allowedMasks = QStringList()
            << Constants::RectangleMaskType << Constants::PolygonMaskType
            << Constants::EllipseMaskType << Constants::VerticalLineMaskType
            << Constants::HorizontalLineMaskType << Constants::MaskAllType
            << Constants::RegionOfInterestType;
    registerTag(T_MASKS, 0, -1, allowedMasks);
    setDefaultTag(T_MASKS);
}

/* ------------------------------------------------------------------------- */

const QString MaskItem::P_MASK_VALUE = "Mask value";

MaskItem::MaskItem(const QString &name)
    : SessionItem(name)
{
    addProperty(P_MASK_VALUE, true);
}

std::unique_ptr<IShape2D> MaskItem::createShape(double scale) const
{
    Q_UNUSED(scale);
    throw GUIHelpers::Error("MaskItem::createShape() -> Not implemented.");
}


/* ------------------------------------------------------------------------- */
const QString RectangleItem::P_XLOW = "xlow";
const QString RectangleItem::P_YLOW = "ylow";
const QString RectangleItem::P_XUP = "xup";
const QString RectangleItem::P_YUP = "yup";

RectangleItem::RectangleItem(const QString &modelType)
    : MaskItem(modelType)
{
    setItemName(modelType);
    addProperty(P_XLOW, 0.0)->setLimits(RealLimits::limitless());
    addProperty(P_YLOW, 0.0)->setLimits(RealLimits::limitless());
    addProperty(P_XUP, 0.0)->setLimits(RealLimits::limitless());
    addProperty(P_YUP, 0.0)->setLimits(RealLimits::limitless());
}

std::unique_ptr<IShape2D> RectangleItem::createShape(double scale) const
{
    double xlow = scale*getItemValue(P_XLOW).toDouble();
    double ylow = scale*getItemValue(P_YLOW).toDouble();
    double xup = scale*getItemValue(P_XUP).toDouble();
    double yup = scale*getItemValue(P_YUP).toDouble();
    return GUIHelpers::make_unique<Rectangle>(xlow, ylow, xup, yup);
}

/* ------------------------------------------------------------------------- */

RegionOfInterestItem::RegionOfInterestItem()
    : RectangleItem(Constants::RegionOfInterestType)
{
    setItemValue(P_MASK_VALUE, false);
}

/* ------------------------------------------------------------------------- */

const QString PolygonPointItem::P_POSX = "X position";
const QString PolygonPointItem::P_POSY = "Y position";

PolygonPointItem::PolygonPointItem()
    : SessionItem(Constants::PolygonPointType)
{
    setItemName(Constants::PolygonPointType);
    addProperty(P_POSX, 0.0)->setLimits(RealLimits::limitless());
    addProperty(P_POSY, 0.0)->setLimits(RealLimits::limitless());
}

/* ------------------------------------------------------------------------- */

const QString PolygonItem::P_ISCLOSED = "Is closed";

PolygonItem::PolygonItem()
    : MaskItem(Constants::PolygonMaskType)
{
    setItemName(Constants::PolygonMaskType);
    const QString T_POINTS = "Point tag";
    registerTag(T_POINTS, 0, -1, QStringList() << Constants::PolygonPointType);
    setDefaultTag(T_POINTS);
    addProperty(P_ISCLOSED, false)->setVisible(false);
}

std::unique_ptr<IShape2D> PolygonItem::createShape(double scale) const
{
    std::vector<double> x,y;
    foreach(SessionItem *item, this->getChildrenOfType(Constants::PolygonPointType)) {
        x.push_back(scale*item->getItemValue(PolygonPointItem::P_POSX).toDouble());
        y.push_back(scale*item->getItemValue(PolygonPointItem::P_POSY).toDouble());
    }
    return GUIHelpers::make_unique<Polygon>(x, y);
}

/* ------------------------------------------------------------------------- */
const QString VerticalLineItem::P_POSX = "X position";

VerticalLineItem::VerticalLineItem()
    : MaskItem(Constants::VerticalLineMaskType)
{
    setItemName(Constants::VerticalLineMaskType);
    addProperty(P_POSX, 0.0)->setLimits(RealLimits::limitless());
}

std::unique_ptr<IShape2D> VerticalLineItem::createShape(double scale) const
{
    return GUIHelpers::make_unique<VerticalLine>(
                scale*getItemValue(VerticalLineItem::P_POSX).toDouble());
}

/* ------------------------------------------------------------------------- */
const QString HorizontalLineItem::P_POSY = "Y position";

HorizontalLineItem::HorizontalLineItem()
    : MaskItem(Constants::HorizontalLineMaskType)
{
    setItemName(Constants::HorizontalLineMaskType);
    addProperty(P_POSY, 0.0)->setLimits(RealLimits::limitless());
}

std::unique_ptr<IShape2D> HorizontalLineItem::createShape(double scale) const
{
    return GUIHelpers::make_unique<HorizontalLine>(
                scale*getItemValue(HorizontalLineItem::P_POSY).toDouble());
}

/* ------------------------------------------------------------------------- */

const QString EllipseItem::P_XCENTER = "X position";
const QString EllipseItem::P_YCENTER = "Y position";
const QString EllipseItem::P_XRADIUS = "X radius";
const QString EllipseItem::P_YRADIUS = "Y radius";
const QString EllipseItem::P_ANGLE = "Angle";

EllipseItem::EllipseItem()
    : MaskItem(Constants::EllipseMaskType)
{
    setItemName(Constants::EllipseMaskType);
    addProperty(P_XCENTER, 0.0)->setLimits(RealLimits::limitless());
    addProperty(P_YCENTER, 0.0)->setLimits(RealLimits::limitless());
    addProperty(P_XRADIUS, 0.0);
    addProperty(P_YRADIUS, 0.0);
    addProperty(P_ANGLE, 0.0)->setLimits(RealLimits::limitless());
}

std::unique_ptr<IShape2D> EllipseItem::createShape(double scale) const
{
    double xcenter = scale*getItemValue(EllipseItem::P_XCENTER).toDouble();
    double ycenter = scale*getItemValue(EllipseItem::P_YCENTER).toDouble();
    double xradius = scale*getItemValue(EllipseItem::P_XRADIUS).toDouble();
    double yradius = scale*getItemValue(EllipseItem::P_YRADIUS).toDouble();
    double angle = scale*getItemValue(EllipseItem::P_ANGLE).toDouble();

    return GUIHelpers::make_unique<Ellipse>(xcenter, ycenter, xradius, yradius, angle);
}

/* ------------------------------------------------------------------------- */

MaskAllItem::MaskAllItem()
    : MaskItem(Constants::MaskAllType)
{
    setItemName(Constants::MaskAllType);
    getItem(MaskItem::P_MASK_VALUE)->setEnabled(false);
}

std::unique_ptr<IShape2D> MaskAllItem::createShape(double scale) const
{
    Q_UNUSED(scale);
    return GUIHelpers::make_unique<InfinitePlane>();
}

