// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Instrument/DetectorFunctions.cpp
//! @brief     Implements namespace DetectorFunctions.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "DetectorFunctions.h"
#include "IDetector2D.h"
#include "Instrument.h"
#include "OutputData.h"
#include "SimulationArea.h"
#include <sstream>

bool DetectorFunctions::hasSameDimensions(
    const IDetector2D& detector, const OutputData<double>& data)
{
    if (data.getRank() != detector.getDimension())
        return false;

    for (size_t i = 0; i < detector.getDimension(); ++i)
        if (data.getAxis(i).size() != detector.getAxis(i).size())
            return false;

    return true;
}

std::string DetectorFunctions::axesToString(const IDetector2D& detector)
{
    std::ostringstream result;

    result << "(";
    for (size_t i = 0; i < detector.getDimension(); ++i) {
        result << detector.getAxis(i).size();
        if (i != detector.getDimension() - 1)
            result << ",";
    }
    result << ")";

    return result.str();
}

std::string DetectorFunctions::axesToString(const OutputData<double>& data)
{
    std::ostringstream result;

    result << "(";
    for (size_t i = 0; i < data.getRank(); ++i) {
        result << data.getAxis(i).size();
        if (i != data.getRank() - 1)
            result << ",";
    }
    result << ")";

    return result.str();
}

std::unique_ptr<OutputData<double>> DetectorFunctions::createDataSet(
    const Instrument& instrument, const OutputData<double>& data, bool put_masked_areas_to_zero,
    IDetector2D::EAxesUnits units)
{
    if (!DetectorFunctions::hasSameDimensions(*instrument.getDetector(), data)) {
        std::ostringstream message;
        message << "DetectorFunctions::createDataSet -> Error. Axes of the real data doesn't match "
                << "the detector. Real data:" << DetectorFunctions::axesToString(data)
                << ", detector:" << DetectorFunctions::axesToString(*instrument.getDetector())
                << ".";
        throw Exceptions::RuntimeErrorException(message.str());
    }

    std::unique_ptr<OutputData<double>> result(instrument.createDetectorMap(units));

    if (put_masked_areas_to_zero) {

        SimulationArea area(instrument.getDetector());
        for (SimulationArea::iterator it = area.begin(); it != area.end(); ++it) {
            (*result)[it.roiIndex()] = data[it.detectorIndex()];
        }

    } else {
        SimulationRoiArea area(instrument.getDetector());
        for (SimulationRoiArea::iterator it = area.begin(); it != area.end(); ++it) {
            (*result)[it.roiIndex()] = data[it.detectorIndex()];
        }
    }

    return result;
}
