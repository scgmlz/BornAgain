//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Simulation/UnitConverterUtils.cpp
//! @brief     Implements utilities for unit convertion.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "Core/Simulation/UnitConverterUtils.h"
#include "Core/Scan/UnitConverter1D.h"
#include "Core/Simulation/DepthProbeSimulation.h"
#include "Core/Simulation/GISASSimulation.h"
#include "Core/Simulation/OffSpecularSimulation.h"
#include "Core/Simulation/SpecularSimulation.h"
#include "Device/Detector/RectangularDetector.h"
#include "Device/Detector/SimpleUnitConverters.h"
#include "Device/Detector/SphericalDetector.h"

std::unique_ptr<OutputData<double>>
UnitConverterUtils::createOutputData(const IUnitConverter& converter, Axes::Units units) {
    std::unique_ptr<OutputData<double>> result = std::make_unique<OutputData<double>>();
    for (size_t i = 0; i < converter.dimension(); ++i)
        result->addAxis(*converter.createConvertedAxis(i, units));
    result->setAllTo(0.0);
    return result;
}

std::unique_ptr<IUnitConverter>
UnitConverterUtils::createConverterForGISAS(const Instrument& instrument) {
    const IDetector* const detector = instrument.getDetector();

    if (const auto* const det = dynamic_cast<const SphericalDetector*>(detector))
        return std::make_unique<SphericalConverter>(*det, instrument.beam());
    else if (const auto* const det = dynamic_cast<const RectangularDetector*>(detector))
        return std::make_unique<RectangularConverter>(*det, instrument.beam());

    throw std::runtime_error("Error in createConverterForGISAS: wrong or absent detector type");
}

std::unique_ptr<IUnitConverter> UnitConverterUtils::createConverter(const ISimulation& simulation) {
    if (auto gisas = dynamic_cast<const GISASSimulation*>(&simulation)) {
        return createConverterForGISAS(gisas->instrument());

    } else if (auto spec = dynamic_cast<const SpecularSimulation*>(&simulation)) {
        return UnitConverter1D::createUnitConverter(*spec->dataHandler());

    } else if (auto probe = dynamic_cast<const DepthProbeSimulation*>(&simulation)) {
        return probe->createUnitConverter();

    } else if (auto off_spec = dynamic_cast<const OffSpecularSimulation*>(&simulation)) {
        return off_spec->createUnitConverter();

    } else {
        throw std::runtime_error("UnitConverterUtils::createConverter -> "
                                 "Not implemented simulation.");
    }
}
