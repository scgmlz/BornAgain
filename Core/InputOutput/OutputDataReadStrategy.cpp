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
#include "TiffHandler.h"
#include <stdexcept> // need overlooked by g++ 5.4

OutputData<double>* OutputDataReadINTStrategy::readOutputData(std::istream& input_stream)
{
    OutputData<double>* result = new OutputData<double>;
    std::string line;

    while( std::getline(input_stream, line) ) {
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
