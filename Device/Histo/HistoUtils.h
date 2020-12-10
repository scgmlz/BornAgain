//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Device/Histo/HistoUtils.h
//! @brief     PyObvject forward declaration.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_DEVICE_HISTO_HISTOUTILS_H
#define BORNAGAIN_DEVICE_HISTO_HISTOUTILS_H

#include "Device/Data/OutputData.h"
#include <string>
#include <vector>

class Histogram2D;
class IHistogram;
class SimulationResult;

//! Collection of utils for 1D and 2D image processing (background, peaks, ets).

namespace HistoUtils {

//! Returns vector of peak center coordinates, for peaks in given histogram.

std::vector<std::pair<double, double>> FindPeaks(const Histogram2D& hist, double sigma = 2,
                                                 const std::string& option = {},
                                                 double threshold = 0.05);

//! Returns sum of relative differences between each pair of elements:
//! (a, b) -> 2*abs(a - b)/(a + b)      ( and zero if  a-b=0 )
double RelativeDifference(const SimulationResult& dat, const SimulationResult& ref);

double getRelativeDifference(const IHistogram& dat, const IHistogram& ref);

} // namespace HistoUtils

#endif // BORNAGAIN_DEVICE_HISTO_HISTOUTILS_H
