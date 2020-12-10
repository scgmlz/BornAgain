//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Device/InputOutput/OutputDataReadWriteINT.cpp
//! @brief     Implements class OutputDataReadWriteINT.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "Device/InputOutput/OutputDataReadWriteINT.h"
#include "Base/Utils/StringUtils.h"
#include "Device/InputOutput/DataFormatUtils.h"
#include "Device/Data/ArrayUtils.h"

OutputData<double>* OutputDataReadWriteINT::readOutputData(std::istream& input_stream) {
    OutputData<double>* result = new OutputData<double>;
    std::string line;

    while (std::getline(input_stream, line)) {
        line = StringUtils::trim(line);
        if (line.find("axis") != std::string::npos) {
            std::unique_ptr<IAxis> axis = DataFormatUtils::createAxis(input_stream);
            result->addAxis(*axis);
        }

        if (line.find("data") != std::string::npos)
            DataFormatUtils::fillOutputData(result, input_stream);
    }
    return result;
}

void OutputDataReadWriteINT::writeOutputData(const OutputData<double>& data,
                                             std::ostream& output_stream) {
    output_stream << "# BornAgain Intensity Data\n\n";

    for (size_t i = 0; i < data.rank(); ++i) {
        std::string axis_name = std::string("axis") + std::to_string(i);
        std::unique_ptr<IAxis> P_axis(data.axis(i).clone());
        P_axis->setName(axis_name);
        output_stream << std::endl;
        output_stream << "# axis-" << i << "\n";
        output_stream << (*P_axis) << "\n";
    }
    size_t n_columns = data.axis(data.rank() - 1).size();

    output_stream << "\n# data\n";
    writeOutputDataDoubles(data, output_stream, n_columns);
    output_stream << std::endl;
}

void OutputDataReadWriteINT::writeOutputDataDoubles(const OutputData<double>& data,
                                                    std::ostream& output_stream, size_t n_columns) {

    OutputData<double>::const_iterator it = data.begin();
    output_stream.imbue(std::locale::classic());
    output_stream << std::scientific << std::setprecision(12);
    size_t ncol(0);
    while (it != data.end()) {
        ncol++;
        double z_value = *it++;
        output_stream << ignoreDenormalized(z_value) << "    ";
        if (ncol == n_columns) {
            output_stream << std::endl;
            ncol = 0;
        }
    }
}

double OutputDataReadWriteINT::ignoreDenormalized(double value) {
    return (std::fpclassify(value) == FP_SUBNORMAL) ? 0.0 : value;
}
