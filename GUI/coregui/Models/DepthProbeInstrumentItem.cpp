//  ************************************************************************************************
//
//  BornAgain: simulate and fit reflection and scattering
//
//! @file      GUI/coregui/Models/DepthProbeInstrumentItem.cpp
//! @brief     Implements DepthProbeInstrumentItem class
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "GUI/coregui/Models/DepthProbeInstrumentItem.h"
#include "Base/Const/Units.h"
#include "Core/Simulation/DepthProbeSimulation.h"
#include "Device/Detector/SimpleUnitConverters.h"
#include "GUI/coregui/Models/AxesItems.h"
#include "GUI/coregui/Models/BeamItems.h"
#include "GUI/coregui/Models/BeamWavelengthItem.h"
#include "GUI/coregui/Models/SpecularBeamInclinationItem.h"
#include "GUI/coregui/Models/TransformToDomain.h"

const QString DepthProbeInstrumentItem::P_BEAM = "Beam";
const QString DepthProbeInstrumentItem::P_Z_AXIS = "Z axis";

DepthProbeInstrumentItem::DepthProbeInstrumentItem() : InstrumentItem("DepthProbeInstrument")
{
    setItemName("DepthProbeInstrument");

    addProperty<SpecularBeamItem>(P_BEAM);

    auto axisItem = beamItem()->currentInclinationAxisItem();
    axisItem->setLowerBound(0.0);
    axisItem->setUpperBound(1.0);
    axisItem->setBinCount(500);

    auto axis = addProperty<BasicAxisItem>(P_Z_AXIS);
    axis->setLowerBound(-100.0);
    axis->setUpperBound(100.0);
    axis->getItem(BasicAxisItem::P_TITLE)->setVisible(false);
    axis->getItem(BasicAxisItem::P_NBINS)
        ->setToolTip("Number of points in scan across sample bulk");
    axis->getItem(BasicAxisItem::P_MIN_DEG)
        ->setToolTip("Starting value below sample horizont in nm");
    axis->getItem(BasicAxisItem::P_MAX_DEG)->setToolTip("Ending value above sample horizont in nm");
}

SpecularBeamItem* DepthProbeInstrumentItem::beamItem() const
{
    return item<SpecularBeamItem>(P_BEAM);
}

std::unique_ptr<Instrument> DepthProbeInstrumentItem::createInstrument() const
{
    throw std::runtime_error("DepthProbeInstrumentItem::createInstrument()");
}

std::vector<int> DepthProbeInstrumentItem::shape() const
{
    return std::vector<int>(); // no certain shape to avoid linking to real data
}

void DepthProbeInstrumentItem::updateToRealData(const RealDataItem*)
{
    throw std::runtime_error("DepthProbeInstrumentItem::updateToRealData()");
}

QString DepthProbeInstrumentItem::defaultName() const
{
    return "DepthProbe";
}

std::unique_ptr<DepthProbeSimulation> DepthProbeInstrumentItem::createSimulation() const
{
    std::unique_ptr<DepthProbeSimulation> simulation = std::make_unique<DepthProbeSimulation>();

    const auto axis_item = beamItem()->currentInclinationAxisItem();

    auto axis = axis_item->createAxis(Units::deg);

    simulation->setBeamParameters(beamItem()->wavelength(), static_cast<int>(axis->size()),
                                  axis->lowerBound(), axis->upperBound());

    auto depthAxisItem = dynamic_cast<BasicAxisItem*>(getItem(P_Z_AXIS));
    auto depthAxis = depthAxisItem->createAxis(1.0);
    simulation->setZSpan(depthAxis->size(), depthAxis->lowerBound(), depthAxis->upperBound());

    TransformToDomain::setBeamDistribution(
        "Wavelength", *beamItem()->item<BeamWavelengthItem>(SpecularBeamItem::P_WAVELENGTH),
        *simulation.get());

    TransformToDomain::setBeamDistribution(
        "InclinationAngle",
        *beamItem()->item<SpecularBeamInclinationItem>(SpecularBeamItem::P_INCLINATION_ANGLE),
        *simulation.get());

    return simulation;
}

std::unique_ptr<IUnitConverter> DepthProbeInstrumentItem::createUnitConverter() const
{
    return createSimulation()->createUnitConverter();
}
