// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/InputOutput/OutputDataReadStrategy.cpp
//! @brief     Implements class OutputDataReadStrategy.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "OutputDataReadStrategy.h"
#include "OutputData.h"
#include "DataFormatUtils.h"
#include "ArrayUtils.h"
#include "TiffHandler.h"
#include <stdexcept> // need overlooked by g++ 5.4

OutputData<double>* OutputDataReadINTStrategy::readOutputData(std::istream& input_stream)
{
    OutputData<double>* result = new OutputData<double>;
    std::string line;

    while( std::getline(input_stream, line) ) {
        if (line.find("axis") != std::string::npos) {
            std::unique_ptr<IAxis> axis = DataFormatUtils::createAxis(input_stream);
            result->addAxis(*axis);
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

    if (ncols == 0)
        throw std::runtime_error("OutputDataReadNumpyTXTStrategy::readOutputData() -> Error. "
                                     "Can't parse file");

    for(size_t row=0; row<nrows; row++) {
        if(data[row].size() != ncols)
            throw std::runtime_error("OutputDataReadNumpyTXTStrategy::readOutputData() -> Error. "
                                         "Number of elements is different from row to row.");
    }

    if(nrows < 2){
        return ArrayUtils::createData1D(std::move(data[0])).release();
    }
    else if(ncols < 2){
        const size_t size = data.size();
        std::vector<double> vector1d(size);
        for(size_t i = 0; i < size; ++i){
            vector1d[i] = data[i][0];
        }
        return ArrayUtils::createData1D(std::move(vector1d)).release();
    }
    else{
        return ArrayUtils::createData2D(data).release();
    }
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
