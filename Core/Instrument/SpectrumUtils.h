// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Instrument/SpectrumUtils.h
//! @brief     PyObvject forward declaration.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_CORE_INSTRUMENT_SPECTRUMUTILS_H
#define BORNAGAIN_CORE_INSTRUMENT_SPECTRUMUTILS_H

#include "Core/Intensity/Histogram2D.h"
#include <string>
#include <vector>

class Histogram2D;

//! Collection of utils for 1D and 2D spectrum processing (background, peaks, ets).

namespace SpectrumUtils
{

std::vector<std::pair<double, double>> FindPeaks(const Histogram2D& hist, double sigma = 2,
                                                 const std::string& option = {},
                                                 double threshold = 0.05);
}

#endif // BORNAGAIN_CORE_INSTRUMENT_SPECTRUMUTILS_H
