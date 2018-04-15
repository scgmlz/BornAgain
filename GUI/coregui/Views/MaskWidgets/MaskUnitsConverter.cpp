// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/MaskWidgets/MaskUnitsConverter.cpp
//! @brief     Implements class MaskUnitsConverter
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "MaskUnitsConverter.h"
#include "IntensityDataItem.h"
#include "MaskItems.h"
#include "ProjectionItems.h"
#include "BornAgainNamespace.h"
#include "IntensityDataFunctions.h"
#include "GUIHelpers.h"

MaskUnitsConverter::MaskUnitsConverter() : mp_data(nullptr), m_direction(UNDEFINED) {}

//! Converts all masks on board of IntensityDataItem into bin-fraction coordinates.

void MaskUnitsConverter::convertToNbins(IntensityDataItem* intensityData)
{
    m_direction = TO_NBINS;
    convertIntensityDataItem(intensityData);
}

//! Converts all masks on board of IntensityDataItem from bin-fraction coordinates to coordinates
//! of axes currently defined in OutputData.

void MaskUnitsConverter::convertFromNbins(IntensityDataItem* intensityData)
{
    m_direction = FROM_NBINS;
    convertIntensityDataItem(intensityData);
}

//! Converts all masks on board of IntensityDataItem from/to bin-fraction coordinates

void MaskUnitsConverter::convertIntensityDataItem(IntensityDataItem* intensityData)
{
    if (!intensityData || !intensityData->getOutputData())
        return;

    mp_data = intensityData->getOutputData();

    if (intensityData->maskContainerItem())
        foreach (SessionItem* maskItem, intensityData->maskContainerItem()->getItems())
            convertMask(maskItem);

    if (intensityData->projectionContainerItem())
        foreach (SessionItem* maskItem, intensityData->projectionContainerItem()->getItems())
            convertMask(maskItem);
}

//! Converts single mask from/to bin-fraction coordinates

void MaskUnitsConverter::convertMask(SessionItem* maskItem)
{
    if (maskItem->modelType() == Constants::RectangleMaskType
        || maskItem->modelType() == Constants::RegionOfInterestType) {
        convertCoordinate(maskItem, RectangleItem::P_XLOW, RectangleItem::P_YLOW);
        convertCoordinate(maskItem, RectangleItem::P_XUP, RectangleItem::P_YUP);
    }

    else if (maskItem->modelType() == Constants::PolygonMaskType) {
        foreach (SessionItem* pointItem, maskItem->getChildrenOfType(Constants::PolygonPointType))
            convertCoordinate(pointItem, PolygonPointItem::P_POSX, PolygonPointItem::P_POSY);
    }

    else if (maskItem->modelType() == Constants::VerticalLineMaskType) {
        convertCoordinate(maskItem, VerticalLineItem::P_POSX, QString());
    }

    else if (maskItem->modelType() == Constants::HorizontalLineMaskType) {
        convertCoordinate(maskItem, QString(), HorizontalLineItem::P_POSY);
    }

    else if (maskItem->modelType() == Constants::EllipseMaskType) {
        double xc = maskItem->getItemValue(EllipseItem::P_XCENTER).toDouble();
        double yc = maskItem->getItemValue(EllipseItem::P_YCENTER).toDouble();
        double xR = maskItem->getItemValue(EllipseItem::P_XRADIUS).toDouble();
        double yR = maskItem->getItemValue(EllipseItem::P_YRADIUS).toDouble();

        double x2 = xc + xR;
        double y2 = yc + yR;

        if (m_direction == TO_NBINS) {
            IntensityDataFunctions::coordinateToBinf(xc, yc, *mp_data);
            IntensityDataFunctions::coordinateToBinf(x2, y2, *mp_data);
        } else {
            IntensityDataFunctions::coordinateFromBinf(xc, yc, *mp_data);
            IntensityDataFunctions::coordinateFromBinf(x2, y2, *mp_data);
        }

        maskItem->setItemValue(EllipseItem::P_XCENTER, xc);
        maskItem->setItemValue(EllipseItem::P_YCENTER, yc);
        maskItem->setItemValue(EllipseItem::P_XRADIUS, x2 - xc);
        maskItem->setItemValue(EllipseItem::P_YRADIUS, y2 - yc);
    }
}

//! Convert (x,y) coordinates registered as property (i.e. under P_XPOS, P_YPOS) from/to
//! bin-fraction coordinates. Result of operation are new values for registered properties.

void MaskUnitsConverter::convertCoordinate(SessionItem* maskItem, const QString& xname,
                                           const QString& yname)
{
    if (maskItem->isTag(xname)) {
        double x = convert(maskItem->getItemValue(xname).toDouble(), BornAgain::X_AXIS_INDEX);
        maskItem->setItemValue(xname, x);
    }

    if (maskItem->isTag(yname)) {
        double y = convert(maskItem->getItemValue(yname).toDouble(), BornAgain::Y_AXIS_INDEX);
        maskItem->setItemValue(yname, y);
    }
}

//! Convert value of axis from/to bin-fraction coordinates.

double MaskUnitsConverter::convert(double value, int axis_index)
{
    Q_ASSERT(mp_data);
    Q_ASSERT(axis_index == BornAgain::X_AXIS_INDEX || axis_index == BornAgain::Y_AXIS_INDEX);

    if (m_direction == TO_NBINS) {
        return IntensityDataFunctions::coordinateToBinf(value, mp_data->getAxis(axis_index));

    } else if (m_direction == FROM_NBINS) {
        return IntensityDataFunctions::coordinateFromBinf(value, mp_data->getAxis(axis_index));
    }

    throw GUIHelpers::Error("MaskUnitsConverter::convertX() -> Error. Unknown conversion");
}
