//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Device/InputOutput/OutputDataReadWriteNumpyTXT.cpp
//! @brief     Implements class OutputDataReadWriteNumpyTXT.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "Device/InputOutput/OutputDataReadWriteNumpyTXT.h"
#include "Base/Utils/StringUtils.h"
#include "Device/InputOutput/DataFormatUtils.h"
#include "Device/Data/ArrayUtils.h"
#include <string>
#include <vector>

namespace {
inline bool isDoubleStartChar(char c) {
    return isdigit(c) || c == '-' || c == '+';
}
} // namespace

OutputData<double>* OutputDataReadWriteNumpyTXT::readOutputData(std::istream& input_stream) {
    std::string line;
    std::vector<std::vector<double>> data;

    // Read numbers from input stream:
    while (std::getline(input_stream, line)) {
        line = StringUtils::trim(line);
        if (line.empty() || !isDoubleStartChar(line[0]))
            continue;

        try {
            std::vector<double> dataInRow = DataFormatUtils::parse_doubles(line);
            data.push_back(dataInRow);
        } catch (...) {
            continue;
        }
    }

    // validating
    size_t nrows = data.size();
    size_t ncols(0);
    if (nrows)
        ncols = data[0].size();

    if (ncols == 0)
        throw std::runtime_error("OutputDataReadNumpyTXTStrategy::readOutputData() -> Error. "
                                 "Can't parse file");

    for (size_t row = 0; row < nrows; row++) {
        if (data[row].size() != ncols)
            throw std::runtime_error("OutputDataReadNumpyTXTStrategy::readOutputData() -> Error. "
                                     "Number of elements is different from row to row.");
    }

    if (nrows < 2)
        return ArrayUtils::createData(std::move(data[0])).release();

    if (ncols < 2) {
        const size_t size = data.size();
        std::vector<double> vector1d(size);
        for (size_t i = 0; i < size; ++i)
            vector1d[i] = data[i][0];
        return ArrayUtils::createData(std::move(vector1d)).release();
    }

    return ArrayUtils::createData(data).release();
}

void OutputDataReadWriteNumpyTXT::writeOutputData(const OutputData<double>& data,
                                                  std::ostream& output_stream) {
    output_stream << "# BornAgain Intensity Data" << std::endl;
    output_stream << "# Simple array suitable for numpy, matlab etc." << std::endl;

    const size_t dim = data.rank();
    switch (dim) {
    case 1:
        write1DRepresentation(data, output_stream);
        break;
    case 2:
        write2DRepresentation(data, output_stream);
        break;
    default:
        throw std::runtime_error("Error in OutputDataWriteNumpyTXTStrategy::writeOutputData: data "
                                 "of unsupported dimensions");
    }
}

void OutputDataReadWriteNumpyTXT::write1DRepresentation(const OutputData<double>& data,
                                                        std::ostream& output_stream) {
    output_stream << "# coordinates         intensities" << std::endl;
    output_stream.imbue(std::locale::classic());
    output_stream << std::scientific << std::setprecision(12);

    const std::vector<double> axis_values = data.axis(0).binCenters();

    // printing coordinate and associated intensity
    for (size_t i = 0, nrows = axis_values.size(); i < nrows; ++i)
        output_stream << axis_values[i] << "    " << ignoreDenormalized(data[i]) << std::endl;
}

void OutputDataReadWriteNumpyTXT::write2DRepresentation(const OutputData<double>& data,
                                                        std::ostream& output_stream) {
    const size_t nrows = data.axis(1).size();
    const size_t ncols = data.axis(0).size();

    output_stream << "# [nrows=" << nrows << ", ncols=" << ncols << "]" << std::endl;

    std::vector<std::vector<double>> dataArray = ArrayUtils::createVector2D(data);
    output_stream.imbue(std::locale::classic());
    output_stream << std::scientific << std::setprecision(12);

    for (size_t i = 0; i < nrows; i++) {
        for (size_t j = 0; j < ncols; j++) {
            double z_value = dataArray[i][j];
            output_stream << ignoreDenormalized(z_value) << "    ";
        }
        output_stream << std::endl;
    }
}

double OutputDataReadWriteNumpyTXT::ignoreDenormalized(double value) {
    return (std::fpclassify(value) == FP_SUBNORMAL) ? 0.0 : value;
}
