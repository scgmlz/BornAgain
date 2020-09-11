// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Detector/DetectorFunctions.cpp
//! @brief     Implements namespace DetectorFunctions.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Core/Detector/DetectorFunctions.h"
#include "Core/Detector/SimulationArea.h"
#include "Core/Detector/SimulationAreaIterator.h"
#include "Core/Intensity/OutputData.h"
#include "Fit/Tools/StringUtils.h"
#include <algorithm>
#include <cctype>
#include <map>
#include <sstream>

bool DetectorFunctions::hasSameDimensions(const IDetector& detector, const OutputData<double>& data)
{
    if (data.getRank() != detector.dimension())
        return false;

    for (size_t i = 0; i < detector.dimension(); ++i)
        if (data.getAxis(i).size() != detector.getAxis(i).size())
            return false;

    return true;
}

std::string DetectorFunctions::axesToString(const IDetector& detector)
{
    std::ostringstream result;

    result << "(";
    for (size_t i = 0; i < detector.dimension(); ++i) {
        result << detector.getAxis(i).size();
        if (i != detector.dimension() - 1)
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
