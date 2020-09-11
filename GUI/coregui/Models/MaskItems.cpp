// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/MaskItems.cpp
//! @brief     Implements MaskItems classes
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/coregui/Models/MaskItems.h"
#include "Core/Mask/Ellipse.h"
#include "Core/Mask/InfinitePlane.h"
#include "Core/Mask/Line.h"
#include "Core/Mask/Polygon.h"
#include "Core/Mask/Rectangle.h"
#include "GUI/coregui/utils/GUIHelpers.h"

MaskContainerItem::MaskContainerItem() : SessionItem("MaskContainer")
{
    const QString T_MASKS = "Mask Tag";
    QStringList allowedMasks = QStringList() << "RectangleMask"
                                             << "PolygonMask"
                                             << "EllipseMask"
                                             << "VerticalLineMask"
                                             << "HorizontalLineMask"
                                             << "MaskAllMask"
                                             << "RegionOfInterest";
    registerTag(T_MASKS, 0, -1, allowedMasks);
    setDefaultTag(T_MASKS);
}

/* ------------------------------------------------------------------------- */

const QString MaskItem::P_MASK_VALUE = "Mask value";
const QString MaskItem::P_IS_VISIBLE = "Visibility";

MaskItem::MaskItem(const QString& name) : SessionItem(name)
{
    addProperty(P_MASK_VALUE, true);
    addProperty(P_IS_VISIBLE, true);
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

RectangleItem::RectangleItem(const QString& modelType) : MaskItem(modelType)
{
    setItemName(modelType);
    addProperty(P_XLOW, 0.0)->setLimits(RealLimits::limitless());
    addProperty(P_YLOW, 0.0)->setLimits(RealLimits::limitless());
    addProperty(P_XUP, 0.0)->setLimits(RealLimits::limitless());
    addProperty(P_YUP, 0.0)->setLimits(RealLimits::limitless());
}

std::unique_ptr<IShape2D> RectangleItem::createShape(double scale) const
{
    double xlow = scale * getItemValue(P_XLOW).toDouble();
    double ylow = scale * getItemValue(P_YLOW).toDouble();
    double xup = scale * getItemValue(P_XUP).toDouble();
    double yup = scale * getItemValue(P_YUP).toDouble();
    return std::make_unique<Rectangle>(xlow, ylow, xup, yup);
}

/* ------------------------------------------------------------------------- */

RegionOfInterestItem::RegionOfInterestItem() : RectangleItem("RegionOfInterest")
{
    setItemValue(P_MASK_VALUE, false);
}

/* ------------------------------------------------------------------------- */

const QString PolygonPointItem::P_POSX = "X position";
const QString PolygonPointItem::P_POSY = "Y position";

PolygonPointItem::PolygonPointItem() : SessionItem("PolygonPoint")
{
    setItemName("PolygonPoint");
    addProperty(P_POSX, 0.0)->setLimits(RealLimits::limitless());
    addProperty(P_POSY, 0.0)->setLimits(RealLimits::limitless());
}

/* ------------------------------------------------------------------------- */

const QString PolygonItem::P_ISCLOSED = "Is closed";

PolygonItem::PolygonItem() : MaskItem("PolygonMask")
{
    setItemName("PolygonMask");
    const QString T_POINTS = "Point tag";
    registerTag(T_POINTS, 0, -1, QStringList() << "PolygonPoint");
    setDefaultTag(T_POINTS);
    addProperty(P_ISCLOSED, false)->setVisible(false);
}

std::unique_ptr<IShape2D> PolygonItem::createShape(double scale) const
{
    std::vector<double> x, y;
    for (auto item : this->getChildrenOfType("PolygonPoint")) {
        x.push_back(scale * item->getItemValue(PolygonPointItem::P_POSX).toDouble());
        y.push_back(scale * item->getItemValue(PolygonPointItem::P_POSY).toDouble());
    }
    return std::make_unique<Polygon>(x, y);
}

/* ------------------------------------------------------------------------- */
const QString VerticalLineItem::P_POSX = "X position";

VerticalLineItem::VerticalLineItem() : MaskItem("VerticalLineMask")
{
    setItemName("VerticalLineMask");
    addProperty(P_POSX, 0.0)->setLimits(RealLimits::limitless());
}

std::unique_ptr<IShape2D> VerticalLineItem::createShape(double scale) const
{
    return std::make_unique<VerticalLine>(scale
                                          * getItemValue(VerticalLineItem::P_POSX).toDouble());
}

/* ------------------------------------------------------------------------- */
const QString HorizontalLineItem::P_POSY = "Y position";

HorizontalLineItem::HorizontalLineItem() : MaskItem("HorizontalLineMask")
{
    setItemName("HorizontalLineMask");
    addProperty(P_POSY, 0.0)->setLimits(RealLimits::limitless());
}

std::unique_ptr<IShape2D> HorizontalLineItem::createShape(double scale) const
{
    return std::make_unique<HorizontalLine>(scale
                                            * getItemValue(HorizontalLineItem::P_POSY).toDouble());
}

/* ------------------------------------------------------------------------- */

const QString EllipseItem::P_XCENTER = "X position";
const QString EllipseItem::P_YCENTER = "Y position";
const QString EllipseItem::P_XRADIUS = "X radius";
const QString EllipseItem::P_YRADIUS = "Y radius";
const QString EllipseItem::P_ANGLE = "Angle";

EllipseItem::EllipseItem() : MaskItem("EllipseMask")
{
    setItemName("EllipseMask");
    addProperty(P_XCENTER, 0.0)->setLimits(RealLimits::limitless());
    addProperty(P_YCENTER, 0.0)->setLimits(RealLimits::limitless());
    addProperty(P_XRADIUS, 0.0);
    addProperty(P_YRADIUS, 0.0);
    addProperty(P_ANGLE, 0.0)->setLimits(RealLimits::limitless());
}

std::unique_ptr<IShape2D> EllipseItem::createShape(double scale) const
{
    double xcenter = scale * getItemValue(EllipseItem::P_XCENTER).toDouble();
    double ycenter = scale * getItemValue(EllipseItem::P_YCENTER).toDouble();
    double xradius = scale * getItemValue(EllipseItem::P_XRADIUS).toDouble();
    double yradius = scale * getItemValue(EllipseItem::P_YRADIUS).toDouble();
    double angle = scale * getItemValue(EllipseItem::P_ANGLE).toDouble();

    return std::make_unique<Ellipse>(xcenter, ycenter, xradius, yradius, angle);
}

/* ------------------------------------------------------------------------- */

MaskAllItem::MaskAllItem() : MaskItem("MaskAllMask")
{
    setItemName("MaskAllMask");
    getItem(MaskItem::P_MASK_VALUE)->setEnabled(false);
}

std::unique_ptr<IShape2D> MaskAllItem::createShape(double scale) const
{
    Q_UNUSED(scale);
    return std::make_unique<InfinitePlane>();
}
