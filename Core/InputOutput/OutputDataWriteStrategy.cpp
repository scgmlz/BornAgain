// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/InputOutput/OutputDataWriteStrategy.cpp
//! @brief     Implements class OutputDataWriteStrategy.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Core/InputOutput/OutputDataWriteStrategy.h"
#include "Core/InputOutput/TiffHandler.h"
#include "Core/Intensity/ArrayUtils.h"
#include "Core/Intensity/OutputData.h" // needed by some compilers
#include <cmath>
#include <iomanip>

namespace
{
const int precision{12};

double IgnoreDenormalized(double value)
{
    if (std::fpclassify(value) == FP_SUBNORMAL)
        return 0.0;
    return value;
}

void Write2DRepresentation(const OutputData<double>& data, std::ostream& output_stream)
{
    const size_t nrows = data.getAxis(1).size();
    const size_t ncols = data.getAxis(0).size();

    output_stream << "# [nrows=" << nrows << ", ncols=" << ncols << "]" << std::endl;

    std::vector<std::vector<double>> dataArray = ArrayUtils::createVector2D(data);
    output_stream.imbue(std::locale::classic());
    output_stream << std::scientific << std::setprecision(precision);

    for (size_t i = 0; i < nrows; i++) {
        for (size_t j = 0; j < ncols; j++) {
            double z_value = dataArray[i][j];
            output_stream << IgnoreDenormalized(z_value) << "    ";
        }
        output_stream << std::endl;
    }
}

void WriteOutputDataDoubles(const OutputData<double>& data, std::ostream& output_stream,
                            size_t n_columns)
{

    OutputData<double>::const_iterator it = data.begin();
    output_stream.imbue(std::locale::classic());
    output_stream << std::scientific << std::setprecision(precision);
    size_t ncol(0);
    while (it != data.end()) {
        ncol++;
        double z_value = *it++;
        output_stream << IgnoreDenormalized(z_value) << "    ";
        if (ncol == n_columns) {
            output_stream << std::endl;
            ncol = 0;
        }
    }
}

void Write1DRepresentation(const OutputData<double>& data, std::ostream& output_stream)
{
    output_stream << "# coordinates         intensities" << std::endl;
    output_stream.imbue(std::locale::classic());
    output_stream << std::scientific << std::setprecision(precision);

    const std::vector<double> axis_values = data.getAxis(0).getBinCenters();

    // printing coordinate and associated intensity
    for (size_t i = 0, nrows = axis_values.size(); i < nrows; ++i)
        output_stream << axis_values[i] << "    " << IgnoreDenormalized(data[i]) << std::endl;
}
} // namespace

// ----------------------------------------------------------------------------
// class OutputDataWriteINTStrategy
// ----------------------------------------------------------------------------

void OutputDataWriteINTStrategy::writeOutputData(const OutputData<double>& data,
                                                 std::ostream& output_stream)
{
    output_stream << "# BornAgain Intensity Data\n\n";

    for (size_t i = 0; i < data.getRank(); ++i) {
        std::string axis_name = std::string("axis") + std::to_string(i);
        std::unique_ptr<IAxis> P_axis(data.getAxis(i).clone());
        P_axis->setName(axis_name);
        output_stream << std::endl;
        output_stream << "# axis-" << i << "\n";
        output_stream << (*P_axis) << "\n";
    }
    size_t n_columns = data.getAxis(data.getRank() - 1).size();

    output_stream << "\n# data\n";
    WriteOutputDataDoubles(data, output_stream, n_columns);
    output_stream << std::endl;
}

// ----------------------------------------------------------------------------
// class OutputDataWriteNumpyTXTStrategy
// ----------------------------------------------------------------------------

void OutputDataWriteNumpyTXTStrategy::writeOutputData(const OutputData<double>& data,
                                                      std::ostream& output_stream)
{
    output_stream << "# BornAgain Intensity Data" << std::endl;
    output_stream << "# Simple array suitable for numpy, matlab etc." << std::endl;

    const size_t dim = data.getRank();
    switch (dim) {
    case 1:
        Write1DRepresentation(data, output_stream);
        break;
    case 2:
        Write2DRepresentation(data, output_stream);
        break;
    default:
        throw std::runtime_error("Error in OutputDataWriteNumpyTXTStrategy::writeOutputData: data "
                                 "of unsupported dimensions");
    }
}

// ----------------------------------------------------------------------------
// class OutputDataWriteTiffStrategy
// ----------------------------------------------------------------------------

#ifdef BORNAGAIN_TIFF_SUPPORT

OutputDataWriteTiffStrategy::OutputDataWriteTiffStrategy() : m_d(new TiffHandler) {}

OutputDataWriteTiffStrategy::~OutputDataWriteTiffStrategy()
{
    delete m_d;
}

void OutputDataWriteTiffStrategy::writeOutputData(const OutputData<double>& data,
                                                  std::ostream& output_stream)
{
    m_d->write(data, output_stream);
}

#endif
