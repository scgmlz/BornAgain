// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Instrument/SpectrumUtils.cpp
//! @brief     PyObvject forward declaration.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Core/Instrument/SpectrumUtils.h"
#include "Core/Intensity/ArrayUtils.h"
#include "tspectrum.h"
#include <cmath>

std::vector<std::pair<double, double>> SpectrumUtils::FindPeaks(const Histogram2D& hist,
                                                                double sigma,
                                                                const std::string& option,
                                                                double threshold)
{
    std::unique_ptr<OutputData<double>> data(hist.createOutputData());
    std::vector<std::vector<double>> arr = ArrayUtils::createVector2D(*data);
    tspectrum::Spectrum2D spec;
    auto peaks = spec.find_peaks(arr, sigma, option, threshold);

    // coordinates of peaks in histogram axes units
    std::vector<std::pair<double, double>> result;

    for (const auto& p : peaks) {
        double row_value = p.first;
        double col_value = p.second;

        size_t xaxis_index = static_cast<size_t>(col_value);
        size_t yaxis_index = hist.getYaxis().size() - 1 - static_cast<size_t>(row_value);

        Bin1D xbin = hist.getXaxis().getBin(xaxis_index);
        Bin1D ybin = hist.getYaxis().getBin(yaxis_index);

        double dx = col_value - static_cast<size_t>(col_value);
        double dy = -1.0 * (row_value - static_cast<size_t>(row_value));

        double x = xbin.getMidPoint() + xbin.getBinSize() * dx;
        double y = ybin.getMidPoint() + ybin.getBinSize() * dy;

        result.push_back(std::make_pair(x, y));
    }
    return result;
}
