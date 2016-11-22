// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/InputOutput/OutputDataReadStrategy.cpp
//! @brief     Implements class OutputDataReadStrategy.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "OutputDataReadStrategy.h"
#include "OutputData.h"
#include "DataFormatUtils.h"
#include "TiffHandler.h"
#include <stdexcept> // need overlooked by g++ 5.4

OutputData<double>* OutputDataReadINTStrategy::readOutputData(std::istream& input_stream)
{
    OutputData<double>* result = new OutputData<double>;
    std::string line;

    while( std::getline(input_stream, line) ) {
        if (line.find("reproducibility") != std::string::npos) {
            std::string line;
            std::getline(input_stream, line);
            result->setVariability( std::stod( line ) );
        }

        if (line.find("axis") != std::string::npos) {
            IAxis* axis = DataFormatUtils::createAxis(input_stream);
            result->addAxis(*axis);
            delete axis;
        }

        if (line.find("data") != std::string::npos) {
            DataFormatUtils::fillOutputData(result, input_stream);
        }
    }
    return result;
}


OutputData<double>* OutputDataReadNumpyTXTStrategy::readOutputData(std::istream& input_stream)
{
    std::string line;
    std::vector<std::vector<double>> data;

    while( std::getline(input_stream, line) ) {
        if(line.empty() || line[0] == '#')
            continue;
        std::vector<double> data_in_row = DataFormatUtils::parse_doubles(line);
        data.push_back(data_in_row);
    }
    // validating
    size_t nrows = data.size();
    size_t ncols(0);
    if(nrows) ncols = data[0].size();
    for(size_t row=0; row<nrows; row++) {
        if(data[row].size() != ncols)
            throw std::runtime_error("OutputDataReadNumpyTXTStrategy::readOutputData() -> Error. "
                                     "Number of elements is different from row to row.");
    }
    OutputData<double>* result = new OutputData<double>;
    result->addAxis("x", ncols, 0.0, double(ncols));
    result->addAxis("y", nrows, 0.0, double(nrows));
    std::vector<int> axes_indices(2);
    for(size_t row=0; row<nrows; row++) {
        for(size_t col=0; col<ncols; col++) {
            axes_indices[0] = col;
            axes_indices[1] = nrows - 1 - row;
            size_t global_index = result->toGlobalIndex(axes_indices);
            (*result)[global_index] = data[row][col];
        }
    }
    return result;
}


#ifdef BORNAGAIN_TIFF_SUPPORT

OutputDataReadTiffStrategy::OutputDataReadTiffStrategy()
    : m_d(new TiffHandler)
{}

OutputDataReadTiffStrategy::~OutputDataReadTiffStrategy()
{
    delete m_d;
}

OutputData<double>* OutputDataReadTiffStrategy::readOutputData(std::istream& input_stream)
{
    m_d->read(input_stream);
    return m_d->getOutputData()->clone();
}

#endif // BORNAGAIN_TIFF_SUPPORT
