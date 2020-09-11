// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/BeamItems.cpp
//! @brief     Implements BeamItem hierarchy
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/coregui/Models/BeamItems.h"
#include "Core/Basics/Assert.h"
#include "Core/Basics/Units.h"
#include "Core/Beam/Beam.h"
#include "Core/Binning/IAxis.h"
#include "GUI/coregui/Models/AxesItems.h"
#include "GUI/coregui/Models/BeamAngleItems.h"
#include "GUI/coregui/Models/BeamDistributionItem.h"
#include "GUI/coregui/Models/BeamWavelengthItem.h"
#include "GUI/coregui/Models/FootprintItems.h"
#include "GUI/coregui/Models/GroupItem.h"
#include "GUI/coregui/Models/ParameterTranslators.h"
#include "GUI/coregui/Models/PointwiseAxisItem.h"
#include "GUI/coregui/Models/SessionItemUtils.h"
#include "GUI/coregui/Models/SpecularBeamInclinationItem.h"
#include "GUI/coregui/utils/GUIHelpers.h"
#include <cmath>

using SessionItemUtils::GetVectorItem;

namespace
{
const QString polarization_tooltip = "Polarization of the beam, given as the Bloch vector";

// defines wavelength limits according to given maximum q value
RealLimits getLimits(double max_q);
} // namespace

const QString BeamItem::P_INTENSITY = QString::fromStdString("Intensity");
const QString BeamItem::P_WAVELENGTH = QString::fromStdString("Wavelength");
const QString BeamItem::P_INCLINATION_ANGLE = QString::fromStdString("InclinationAngle");
const QString BeamItem::P_AZIMUTHAL_ANGLE = QString::fromStdString("AzimuthalAngle");
const QString BeamItem::P_POLARIZATION = "Polarization";

BeamItem::BeamItem(const QString& beam_model) : SessionItem(beam_model)
{
    addProperty(P_INTENSITY, 1e+08)
        ->setLimits(RealLimits::limited(0.0, 1e+32))
        .setToolTip("Beam intensity in neutrons (or gammas) per sec.")
        .setEditorType("ScientificDouble");

    addGroupProperty(P_AZIMUTHAL_ANGLE, "BeamAzimuthalAngle");
    addGroupProperty(P_POLARIZATION, "Vector")->setToolTip(polarization_tooltip);

    addTranslator(VectorParameterTranslator(P_POLARIZATION, "BlochVector"));
}

BeamItem::~BeamItem() = default;

double BeamItem::getIntensity() const
{
    return getItemValue(P_INTENSITY).toDouble();
}

void BeamItem::setIntensity(double value)
{
    setItemValue(P_INTENSITY, value);
}

double BeamItem::getWavelength() const
{
    BeamWavelengthItem* beamWavelength = dynamic_cast<BeamWavelengthItem*>(getItem(P_WAVELENGTH));
    return beamWavelength->wavelength();
}

void BeamItem::setWavelength(double value)
{
    auto beam_wavelength = dynamic_cast<BeamWavelengthItem*>(getItem(P_WAVELENGTH));
    ASSERT(beam_wavelength);
    beam_wavelength->resetToValue(value);
}

void BeamItem::setInclinationAngle(double value)
{
    auto angleItem = dynamic_cast<BeamDistributionItem*>(getItem(P_INCLINATION_ANGLE));
    ASSERT(angleItem);
    angleItem->resetToValue(value);
}

double BeamItem::getAzimuthalAngle() const
{
    const auto inclination = dynamic_cast<BeamAzimuthalAngleItem*>(getItem(P_AZIMUTHAL_ANGLE));
    ASSERT(inclination);
    return inclination->azimuthalAngle();
}

void BeamItem::setAzimuthalAngle(double value)
{
    auto angleItem = dynamic_cast<BeamDistributionItem*>(getItem(P_AZIMUTHAL_ANGLE));
    ASSERT(angleItem);
    angleItem->resetToValue(value);
}

std::unique_ptr<Beam> BeamItem::createBeam() const
{
    double lambda = getWavelength();
    double inclination_angle = Units::deg2rad(getInclinationAngle());
    double azimuthal_angle = Units::deg2rad(getAzimuthalAngle());

    auto result =
        std::make_unique<Beam>(lambda, inclination_angle, azimuthal_angle, getIntensity());

    result->setPolarization(GetVectorItem(*this, P_POLARIZATION));

    return result;
}

void BeamItem::setInclinationProperty(const QString& inclination_type)
{
    addGroupProperty(P_INCLINATION_ANGLE, inclination_type);
}

void BeamItem::setWavelengthProperty(const QString& wavelength_type)
{
    addGroupProperty(P_WAVELENGTH, wavelength_type);
}

// Specular beam item
/* ------------------------------------------------------------------------- */

const QString SpecularBeamItem::P_FOOPTPRINT = "Footprint";

const QString footprint_group_label("Type");

SpecularBeamItem::SpecularBeamItem() : BeamItem("SpecularBeam")
{
    setInclinationProperty("SpecularBeamInclinationAxis");
    setWavelengthProperty("SpecularBeamWavelength");

    getItem(P_AZIMUTHAL_ANGLE)->setVisible(false);
    getItem(P_POLARIZATION)->setVisible(false);

    auto item = addGroupProperty(P_FOOPTPRINT, "Footprint group");
    item->setDisplayName(footprint_group_label);
    item->setToolTip("Footprint type");

    getItem(P_WAVELENGTH)
        ->mapper()
        ->setOnChildPropertyChange(
            [this](SessionItem*, QString property) {
                if (property != SymmetricDistributionItem::P_MEAN)
                    return;
                if (auto axis_item = dynamic_cast<PointwiseAxisItem*>(currentInclinationAxisItem()))
                    axis_item->updateIndicators();
            },
            this);

    inclinationAxisGroup()->mapper()->setOnValueChange([this]() { updateWavelength(); }, this);
}

SpecularBeamItem::~SpecularBeamItem() = default;

double SpecularBeamItem::getInclinationAngle() const
{
    return 0.0;
}

void SpecularBeamItem::setInclinationAngle(double value)
{
    ASSERT(value == 0.0);
    value = 0.0;
    BeamItem::setInclinationAngle(value);
}

GroupItem* SpecularBeamItem::inclinationAxisGroup()
{
    return dynamic_cast<GroupItem*>(
        getItem(P_INCLINATION_ANGLE)->getItem(SpecularBeamInclinationItem::P_ALPHA_AXIS));
}

BasicAxisItem* SpecularBeamItem::currentInclinationAxisItem()
{
    return dynamic_cast<BasicAxisItem*>(inclinationAxisGroup()->currentItem());
}

FootprintItem* SpecularBeamItem::currentFootprintItem() const
{
    return &groupItem<FootprintItem>(P_FOOPTPRINT);
}

void SpecularBeamItem::updateFileName(const QString& filename)
{
    item<SpecularBeamInclinationItem>(BeamItem::P_INCLINATION_ANGLE).updateFileName(filename);
}

void SpecularBeamItem::updateToData(const IAxis& axis, QString units)
{
    if (units == "nbins") {
        inclinationAxisGroup()->setCurrentType("BasicAxis");
        auto axis_item = currentInclinationAxisItem();
        axis_item->setItemValue(BasicAxisItem::P_NBINS, static_cast<int>(axis.size()));
        return;
    }

    auto axis_group = inclinationAxisGroup();
    auto axis_item = static_cast<PointwiseAxisItem*>(axis_group->getChildOfType("PointwiseAxis"));
    axis_item->init(axis, units);
    axis_group->setCurrentType("PointwiseAxis"); // calls updateWavelength()
    axis_item->updateIndicators();
}

void SpecularBeamItem::updateWavelength()
{
    auto item = inclinationAxisGroup()->currentItem();
    auto wl_item = static_cast<SpecularBeamWavelengthItem*>(getItem(P_WAVELENGTH));
    if (auto axis_item = dynamic_cast<PointwiseAxisItem*>(item)) {
        auto axis = axis_item->getAxis();
        if (axis && axis_item->getUnitsLabel() == "q-space")
            wl_item->setToRange(getLimits(axis->getMax()));
    } else
        wl_item->setToRange(RealLimits::positive());
}

// GISAS beam item
/* ------------------------------------------------------------------------- */

GISASBeamItem::GISASBeamItem() : BeamItem("GISASBeam")
{
    setInclinationProperty("BeamInclinationAngle");
    setWavelengthProperty("BeamWavelength");
}

GISASBeamItem::~GISASBeamItem() = default;

double GISASBeamItem::getInclinationAngle() const
{
    const auto inclination = dynamic_cast<BeamInclinationAngleItem*>(getItem(P_INCLINATION_ANGLE));
    ASSERT(inclination);
    return inclination->inclinationAngle();
}

namespace
{
RealLimits getLimits(double max_q)
{
    double upper_lim = std::nextafter(4.0 * M_PI / max_q, 0.0);
    RealLimits result = RealLimits::positive();
    result.setUpperLimit(upper_lim);
    return result;
}
} // namespace
