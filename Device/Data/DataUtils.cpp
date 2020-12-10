//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Device/Data/DataUtils.cpp
//! @brief     Implements namespace DataUtils.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "Device/Data/DataUtils.h"
#include "Device/Data/ArrayUtils.h"
#include "Base/Math/FourierTransform.h"
#include "Base/Math/Numeric.h"
#include <iostream>

namespace {

std::vector<std::vector<double>> FT2DArray(const std::vector<std::vector<double>>& signal) {
    FourierTransform ft;
    std::vector<std::vector<double>> ret;
    ft.fft(signal, ret);
    ft.fftshift(ret); // low frequency to center of array
    return ret;
}

} // namespace

//! Returns relative difference between two data sets sum(dat[i] - ref[i])/ref[i]).
double DataUtils::relativeDataDifference(const OutputData<double>& dat,
                                         const OutputData<double>& ref) {
    if (!dat.hasSameDimensions(ref))
        throw std::runtime_error("OutputData dimension differs from reference");

    double diff = 0.0;
    for (size_t i = 0; i < dat.getAllocatedSize(); ++i)
        diff += Numeric::GetRelativeDifference(dat[i], ref[i]);
    diff /= dat.getAllocatedSize();
    if (std::isnan(diff))
        throw std::runtime_error("diff=NaN!");
    return diff;
}

//! Returns true is relative difference is below threshold; prints informative output
bool DataUtils::checkRelativeDifference(const OutputData<double>& dat,
                                        const OutputData<double>& ref, const double threshold) {
    const double diff = relativeDataDifference(dat, ref);
    if (diff > threshold) {
        std::cerr << "FAILED: relative deviation of dat from ref is " << diff
                  << ", above given threshold " << threshold << "\n";
        return false;
    }
    if (diff)
        std::cerr << "- OK: relative deviation of dat from ref is " << diff
                  << ", within given threshold " << threshold << "\n";
    else
        std::cout << "- OK: dat = ref\n";
    return true;
}

std::unique_ptr<OutputData<double>>
DataUtils::createRelativeDifferenceData(const OutputData<double>& data,
                                        const OutputData<double>& reference) {
    if (!data.hasSameDimensions(reference))
        throw std::runtime_error("DataUtils::createRelativeDifferenceData() -> "
                                 "Error. Different dimensions of data and reference.");
    std::unique_ptr<OutputData<double>> result(reference.clone());
    for (size_t i = 0; i < result->getAllocatedSize(); ++i)
        (*result)[i] = Numeric::GetRelativeDifference(data[i], reference[i]);
    return result;
}

std::unique_ptr<OutputData<double>>
DataUtils::createRearrangedDataSet(const OutputData<double>& data, int n) {
    if (data.rank() != 2)
        throw std::runtime_error("DataUtils::rotateDataByN90Deg()"
                                 " -> Error! Works only on two-dimensional data");
    n = (4 + n % 4) % 4;
    if (n == 0)
        return std::unique_ptr<OutputData<double>>(data.clone());
    std::unique_ptr<OutputData<double>> output(new OutputData<double>());

    // swapping axes if necessary
    const IAxis& x_axis = data.axis(0);
    const IAxis& y_axis = data.axis(1);
    output->addAxis(n == 2 ? x_axis : y_axis);
    output->addAxis(n == 2 ? y_axis : x_axis);

    // creating index mapping
    std::function<void(std::vector<int>&)> index_mapping;
    if (n == 2) {
        const int end_bin_x = static_cast<int>(x_axis.size()) - 1;
        const int end_bin_y = static_cast<int>(y_axis.size()) - 1;
        index_mapping = [end_bin_x, end_bin_y](std::vector<int>& inds) {
            inds[0] = end_bin_x - inds[0];
            inds[1] = end_bin_y - inds[1];
        };
    } else {
        const size_t rev_axis_i = n % 3;
        const size_t end_bin = data.axis(rev_axis_i).size() - 1;
        index_mapping = [rev_axis_i, end_bin](std::vector<int>& inds) {
            const int tm_index = inds[rev_axis_i];
            inds[rev_axis_i] = inds[rev_axis_i ^ 1];
            inds[rev_axis_i ^ 1] = static_cast<int>(end_bin) - tm_index;
        };
    }

    for (size_t index = 0, size = data.getAllocatedSize(); index < size; ++index) {
        std::vector<int> axis_inds = data.getAxesBinIndices(index);
        index_mapping(axis_inds);
        size_t output_index = output->toGlobalIndex(
            {static_cast<unsigned>(axis_inds[0]), static_cast<unsigned>(axis_inds[1])});
        (*output)[output_index] = data[index];
    }
    return output;
}

std::unique_ptr<OutputData<double>>
DataUtils::createClippedDataSet(const OutputData<double>& origin, double x1, double y1, double x2,
                                double y2) {
    if (origin.rank() != 2)
        throw std::runtime_error("DataUtils::createClippedData()"
                                 " -> Error! Works only on two-dimensional data");

    std::unique_ptr<OutputData<double>> result(new OutputData<double>);
    for (size_t i_axis = 0; i_axis < origin.rank(); i_axis++) {
        const IAxis& axis = origin.axis(i_axis);
        IAxis* new_axis;
        if (i_axis == 0)
            new_axis = axis.createClippedAxis(x1, x2);
        else
            new_axis = axis.createClippedAxis(y1, y2);
        result->addAxis(*new_axis);
        delete new_axis;
    }
    result->setAllTo(0.0);

    OutputData<double>::const_iterator it_origin = origin.begin();
    OutputData<double>::iterator it_result = result->begin();
    while (it_origin != origin.end()) {
        double x = origin.getAxisValue(it_origin.getIndex(), 0);
        double y = origin.getAxisValue(it_origin.getIndex(), 1);
        if (result->axis(0).contains(x) && result->axis(1).contains(y)) {
            *it_result = *it_origin;
            ++it_result;
        }
        ++it_origin;
    }

    return result;
}

// For axis FixedBinAxis("axis", 8, -5.0, 3.0) the coordinate x=-4.5 (center of bin #0) will
// be converted into 0.5 (which is a bin center expressed in bin fraction coordinates).
// The coordinate -5.0 (outside of axis definition) will be converted to -0.5
// (center of non-existing bin #-1).
// Used for Mask conversion.

double DataUtils::coordinateToBinf(double coordinate, const IAxis& axis) {
    size_t index = axis.findClosestIndex(coordinate);
    Bin1D bin = axis.bin(index);
    double f = (coordinate - bin.m_lower) / bin.binSize();
    return static_cast<double>(index) + f;
}

double DataUtils::coordinateFromBinf(double value, const IAxis& axis) {
    int index = static_cast<int>(value);

    double result(0);
    if (index < 0) {
        Bin1D bin = axis.bin(0);
        result = bin.m_lower + value * bin.binSize();
    } else if (index >= static_cast<int>(axis.size())) {
        Bin1D bin = axis.bin(axis.size() - 1);
        result = bin.m_upper + (value - axis.size()) * bin.binSize();
    } else {
        Bin1D bin = axis.bin(static_cast<size_t>(index));
        result = bin.m_lower + (value - static_cast<double>(index)) * bin.binSize();
    }

    return result;
}

void DataUtils::coordinateToBinf(double& x, double& y, const OutputData<double>& data) {
    x = coordinateToBinf(x, data.axis(0));
    y = coordinateToBinf(y, data.axis(1));
}

void DataUtils::coordinateFromBinf(double& x, double& y, const OutputData<double>& data) {
    x = coordinateFromBinf(x, data.axis(0));
    y = coordinateFromBinf(y, data.axis(1));
}

std::vector<std::vector<double>>
DataUtils::create2DArrayfromOutputData(const OutputData<double>& data) {
    if (data.rank() != 2)
        throw std::runtime_error("DataUtils::create2DArrayfromOutputData() -> "
                                 "Error! Works only on two-dimensional data");

    std::vector<std::vector<double>> array_2d;
    std::vector<double> row_vec; // row vector for constructing each row of 2D array

    size_t nrows = data.axis(0).size();
    size_t ncols = data.axis(1).size();

    size_t it = 0; // iterator of 'data'
    for (size_t row = 0; row < nrows; row++) {
        row_vec.clear();
        for (size_t col = 0; col < ncols; col++) {
            row_vec.push_back(data[it]);
            it++;
        }
        array_2d.push_back(row_vec);
    }

    return array_2d;
}

std::unique_ptr<OutputData<double>>
DataUtils::createOutputDatafrom2DArray(const std::vector<std::vector<double>>& array_2d) {
    std::unique_ptr<OutputData<double>> result(new OutputData<double>);
    size_t nrows = array_2d.size();
    size_t ncols = array_2d[0].size();

    result->addAxis("x", nrows, 0.0, double(nrows));
    result->addAxis("y", ncols, 0.0, double(ncols));
    std::vector<unsigned> axes_indices(2);
    for (unsigned row = 0; row < nrows; row++) {
        for (unsigned col = 0; col < ncols; col++) {
            axes_indices[0] = row;
            axes_indices[1] = col;
            size_t global_index = result->toGlobalIndex(axes_indices);
            (*result)[global_index] = array_2d[row][col];
        }
    }

    return result;
}

std::unique_ptr<OutputData<double>> DataUtils::createFFT(const OutputData<double>& data) {
    auto array_2d = DataUtils::create2DArrayfromOutputData(data);
    auto fft_array_2d = FT2DArray(array_2d);
    return DataUtils::createOutputDatafrom2DArray(fft_array_2d);
}

OutputData<double>* DataUtils::importArrayToOutputData(const std::vector<double>& vec) {
    return ArrayUtils::createData(vec).release();
}

OutputData<double>*
DataUtils::importArrayToOutputData(const std::vector<std::vector<double>>& vec) {
    return ArrayUtils::createData(vec).release();
}
