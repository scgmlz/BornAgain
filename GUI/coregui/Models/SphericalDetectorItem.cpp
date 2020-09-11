// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/SphericalDetectorItem.cpp
//! @brief     Implements class SphericalDetectorItem
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/coregui/Models/SphericalDetectorItem.h"
#include "Core/Basics/Units.h"
#include "Core/Detector/SphericalDetector.h"
#include "GUI/coregui/Models/AxesItems.h"

const QString SphericalDetectorItem::P_PHI_AXIS = "Phi axis";
const QString SphericalDetectorItem::P_ALPHA_AXIS = "Alpha axis";

SphericalDetectorItem::SphericalDetectorItem() : DetectorItem("SphericalDetector")
{
    SessionItem* item = addGroupProperty(P_PHI_AXIS, "BasicAxis");
    item->getItem(BasicAxisItem::P_TITLE)->setVisible(false);
    item->setItemValue(BasicAxisItem::P_MIN_DEG, -1.0);
    item->setItemValue(BasicAxisItem::P_MAX_DEG, 1.0);

    item->getItem(BasicAxisItem::P_NBINS)->setToolTip("Number of phi-axis bins");
    item->getItem(BasicAxisItem::P_MIN_DEG)->setToolTip("Low edge of first phi-bin (in deg)");
    item->getItem(BasicAxisItem::P_MAX_DEG)->setToolTip("Upper edge of last phi-bin (in deg)");

    item = addGroupProperty(P_ALPHA_AXIS, "BasicAxis");
    item->getItem(BasicAxisItem::P_TITLE)->setVisible(false);
    item->setItemValue(BasicAxisItem::P_MIN_DEG, 0.0);
    item->setItemValue(BasicAxisItem::P_MAX_DEG, 2.0);

    item->getItem(BasicAxisItem::P_NBINS)->setToolTip("Number of alpha-axis bins");
    item->getItem(BasicAxisItem::P_MIN_DEG)->setToolTip("Low edge of first alpha-bin (in deg)");
    item->getItem(BasicAxisItem::P_MAX_DEG)->setToolTip("Upper edge of last alpha-bin (in deg)");

    register_resolution_function();
}

std::unique_ptr<IDetector2D> SphericalDetectorItem::createDomainDetector() const
{
    std::unique_ptr<SphericalDetector> result(new SphericalDetector());

    auto x_axis = dynamic_cast<BasicAxisItem*>(getItem(SphericalDetectorItem::P_PHI_AXIS));
    ASSERT(x_axis);
    int n_x = x_axis->getItemValue(BasicAxisItem::P_NBINS).toInt();
    double x_min = Units::deg2rad(x_axis->getItemValue(BasicAxisItem::P_MIN_DEG).toDouble());
    double x_max = Units::deg2rad(x_axis->getItemValue(BasicAxisItem::P_MAX_DEG).toDouble());

    auto y_axis = dynamic_cast<BasicAxisItem*>(getItem(SphericalDetectorItem::P_ALPHA_AXIS));
    ASSERT(y_axis);
    int n_y = y_axis->getItemValue(BasicAxisItem::P_NBINS).toInt();
    double y_min = Units::deg2rad(y_axis->getItemValue(BasicAxisItem::P_MIN_DEG).toDouble());
    double y_max = Units::deg2rad(y_axis->getItemValue(BasicAxisItem::P_MAX_DEG).toDouble());

    result->setDetectorParameters(n_x, x_min, x_max, n_y, y_min, y_max);

    return std::unique_ptr<IDetector2D>(result.release());
}

int SphericalDetectorItem::xSize() const
{
    return getItem(SphericalDetectorItem::P_PHI_AXIS)->getItemValue(BasicAxisItem::P_NBINS).toInt();
}

int SphericalDetectorItem::ySize() const
{
    return getItem(SphericalDetectorItem::P_ALPHA_AXIS)
        ->getItemValue(BasicAxisItem::P_NBINS)
        .toInt();
}

void SphericalDetectorItem::setXSize(int nx)
{
    getItem(SphericalDetectorItem::P_PHI_AXIS)->setItemValue(BasicAxisItem::P_NBINS, nx);
}

void SphericalDetectorItem::setYSize(int ny)
{
    getItem(SphericalDetectorItem::P_ALPHA_AXIS)->setItemValue(BasicAxisItem::P_NBINS, ny);
}

double SphericalDetectorItem::axesToDomainUnitsFactor() const
{
    return Units::degree;
}
