// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/DepthProbeInstrumentItem.cpp
//! @brief     Implements DepthProbeInstrumentItem class
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/coregui/Models/DepthProbeInstrumentItem.h"
#include "Core/Basics/Units.h"
#include "Core/Intensity/SimpleUnitConverters.h"
#include "Core/Simulation/DepthProbeSimulation.h"
#include "GUI/coregui/Models/AxesItems.h"
#include "GUI/coregui/Models/BeamDistributionItem.h"
#include "GUI/coregui/Models/BeamWavelengthItem.h"
#include "GUI/coregui/Models/SpecularBeamInclinationItem.h"
#include "GUI/coregui/Models/TransformToDomain.h"

const QString DepthProbeInstrumentItem::P_BEAM = "Beam";
const QString DepthProbeInstrumentItem::P_Z_AXIS = "Z axis";

DepthProbeInstrumentItem::DepthProbeInstrumentItem() : InstrumentItem("DepthProbeInstrument")
{
    setItemName("DepthProbeInstrument");

    addGroupProperty(P_BEAM, "SpecularBeam");

    auto axisItem = beamItem()->currentInclinationAxisItem();
    axisItem->setItemValue(BasicAxisItem::P_MIN_DEG, 0.0);
    axisItem->setItemValue(BasicAxisItem::P_MAX_DEG, 1.0);
    axisItem->setItemValue(BasicAxisItem::P_NBINS, 500);

    auto axis = addGroupProperty(P_Z_AXIS, "BasicAxis");
    axis->getItem(BasicAxisItem::P_TITLE)->setVisible(false);
    axis->setItemValue(BasicAxisItem::P_MIN_DEG, -100.0);
    axis->setItemValue(BasicAxisItem::P_MAX_DEG, 100.0);
    axis->getItem(BasicAxisItem::P_NBINS)
        ->setToolTip("Number of points in scan across sample bulk");
    axis->getItem(BasicAxisItem::P_MIN_DEG)
        ->setToolTip("Starting value below sample horizont in nm");
    axis->getItem(BasicAxisItem::P_MAX_DEG)->setToolTip("Ending value above sample horizont in nm");
}

SpecularBeamItem* DepthProbeInstrumentItem::beamItem() const
{
    return &item<SpecularBeamItem>(P_BEAM);
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

std::unique_ptr<DepthProbeSimulation> DepthProbeInstrumentItem::createSimulation() const
{
    std::unique_ptr<DepthProbeSimulation> simulation = std::make_unique<DepthProbeSimulation>();

    const auto axis_item = beamItem()->currentInclinationAxisItem();

    auto axis = axis_item->createAxis(Units::degree);

    simulation->setBeamParameters(beamItem()->getWavelength(), static_cast<int>(axis->size()),
                                  axis->getMin(), axis->getMax());

    auto depthAxisItem = dynamic_cast<BasicAxisItem*>(getItem(P_Z_AXIS));
    auto depthAxis = depthAxisItem->createAxis(1.0);
    simulation->setZSpan(depthAxis->size(), depthAxis->getMin(), depthAxis->getMax());

    TransformToDomain::setBeamDistribution(
        "Wavelength", beamItem()->item<BeamWavelengthItem>(SpecularBeamItem::P_WAVELENGTH),
        *simulation.get());

    TransformToDomain::setBeamDistribution(
        "InclinationAngle",
        beamItem()->item<SpecularBeamInclinationItem>(SpecularBeamItem::P_INCLINATION_ANGLE),
        *simulation.get());

    return simulation;
}

std::unique_ptr<IUnitConverter> DepthProbeInstrumentItem::createUnitConverter() const
{
    return createSimulation()->createUnitConverter();
}
