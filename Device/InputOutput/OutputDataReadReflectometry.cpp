//  ************************************************************************************************
//
//  BornAgain: simulate and fit reflection and scattering
//
//! @file      Device/InputOutput/OutputDataReadReflectometry.cpp
//! @brief     Implements class OutputDataReadWriteReflectometry.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "Device/InputOutput/OutputDataReadReflectometry.h"
#include "Base/Axis/PointwiseAxis.h"
#include "Base/Utils/StringUtils.h"
#include "Device/Data/OutputData.h"
#include "Device/InputOutput/DataFormatUtils.h"
#include <map>

// #migration +++ this works only if separator is space or tab; it does not
// work e.g. with comma or semicolon
OutputData<double>* OutputDataReadReflectometry::readOutputData(std::istream& fin)
{
    OutputData<double>* oData = new OutputData<double>();
    std::string line;
    std::vector<std::vector<double>> vecVec;
    std::map<double, double> QvsR;
    std::map<double, double> QvsDR;
    std::map<double, double> QvsDQ;

    // Read numbers from file:
    while (std::getline(fin, line)) {
        line = StringUtils::trim(line);
        try {
            // #migration +++ this works only if separator is space or tab; it does not
            // work e.g. with comma or semicolon
            std::vector<double> rowVec = DataFormatUtils::parse_doubles(line);
            vecVec.push_back(rowVec);
        } catch (...) { // #migration +++ This eats useful errors away...
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
    for (size_t row = 0; row < nrows; row++) {
        if (vecVec[row].size() != ncols)
            throw std::runtime_error("The number of columns varies among the rows");
        double Q = vecVec[row][0];
        switch (ncols) {
        case 1:
            break;
        case 2:
            QvsR[Q] = vecVec[row][1];
            QvsDR[Q] = 0;
            QvsDQ[Q] = 0;
            break;
        case 3:
            QvsR[Q] = vecVec[row][1];
            QvsDR[Q] = vecVec[row][2];
            QvsDQ[Q] = 0;
            break;
        default:
            QvsR[Q] = vecVec[row][1];
            QvsDR[Q] = vecVec[row][2];
            QvsDQ[Q] = vecVec[row][3];
            break;
        }
    }

    std::vector<double> qVec;
    std::vector<double> rVec;
    for (auto it = QvsR.begin(); it != QvsR.end(); ++it) {
        if (it->second <= 0)
            continue;
        qVec.push_back(it->first);
        rVec.push_back(it->second);
    }

    oData->addAxis(PointwiseAxis("qVector", qVec));
    oData->setRawDataVector(rVec);
    return oData;
}
