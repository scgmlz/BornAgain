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
#include "PointwiseAxis.h"
#include "ArrayUtils.h"
#include "TiffHandler.h"
#include "Units.h"
#include <stdexcept> // need overlooked by g++ 5.4
#include <map>

namespace{
inline std::string trim(const std::string& str,
                        const std::string& whitespace = " \t")
{
    const auto strBegin = str.find_first_not_of(whitespace);

    if (strBegin == std::string::npos)
        return "";

    const auto strEnd = str.find_last_not_of(whitespace);
    const auto strRange = strEnd - strBegin + 1;

    return str.substr(strBegin, strRange);
}
}



OutputData<double>* OutputDataReadINTStrategy::readOutputData(std::istream& input_stream)
{
    OutputData<double>* result = new OutputData<double>;
    std::string line;

    while( std::getline(input_stream, line) ) {
        line = trim(line);
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

OutputData<double>* OutputDataReadReflectometryStrategy::readOutputData(std::istream& fin)
{
    OutputData<double> *oData = new OutputData<double>();
    std::string line;
    std::vector<std::vector<double>> vecVec;
    std::map<double,double> QvsR;
    std::map<double,double> QvsDR;
    std::map<double,double> QvsDQ;

    //Read numbers from file:
    while( std::getline(fin, line) ) {
        line = trim(line);
        try {
            std::vector<double> rowVec = DataFormatUtils::parse_doubles(line);
            vecVec.push_back(rowVec);
        } catch (...) {
            continue;
        }
    }

    // validate - There is at least one row and at least two columns
    size_t nrows = vecVec.size();
    if (nrows < 1)
        throw std::runtime_error("Import1dTextData: no numerical values found");
    size_t ncols = vecVec[0].size();
    if (ncols < 2)
        throw std::runtime_error("Import1dTextData: Minimum 2 columns required");

    // Assign Q vs R, dR, dQ:
    for(size_t row=0; row<nrows; row++) {
        if(vecVec[row].size() != ncols)
            throw std::runtime_error("The number of columns varies among the rows");
        double Q = vecVec[row][0];
        switch(ncols){
        case 1:
            break;
        case 2:
            QvsR[Q]  = vecVec[row][1];
            QvsDR[Q] = 0;
            QvsDQ[Q] = 0;
            break;
        case 3:
            QvsR[Q]  = vecVec[row][1];
            QvsDR[Q] = vecVec[row][2];
            QvsDQ[Q] = 0;
            break;
        default:
            QvsR[Q]  = vecVec[row][1];
            QvsDR[Q] = vecVec[row][2];
            QvsDQ[Q] = vecVec[row][3];
            break;
        }
    }


    std::vector<double> qVec;
    std::vector<double> rVec;
    for(auto it = QvsR.begin(); it != QvsR.end(); ++it) {
        if(it->second <= 0)
            continue;
        qVec.push_back(it->first);
        rVec.push_back(it->second);
    }

    // translate q values from inv. angstroms into inv. nm
    std::transform(qVec.begin(), qVec.end(), qVec.begin(),
                   [](double val) { return val / Units::angstrom; });

    oData->addAxis(PointwiseAxis("qVector", qVec));
    oData->setRawDataVector(rVec);
    return oData;
}

OutputData<double>* OutputDataReadNumpyTXTStrategy::readOutputData(std::istream& input_stream)
{
    std::string line;
    std::vector<std::vector<double>> data;

    //Read numbers from input stream:
    while( std::getline(input_stream, line) ) {
        line = trim(line);
        if(line.empty() || !isdigit(line[0]))
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
