// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/InputOutput/OutputDataWriteFactory.cpp
//! @brief     Implements class OutputDataWriteFactory.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //
#include "OutputDataWriteFactory.h"
#include "Exceptions.h"
#include "DataFormatUtils.h"

OutputDataWriter *OutputDataWriteFactory::getWriter(const std::string &file_name)
{
    OutputDataWriter *result = new OutputDataWriter(file_name);
    result->setStrategy(getWriteStrategy(file_name));
    return result;
}


IOutputDataWriteStrategy *OutputDataWriteFactory::getWriteStrategy(const std::string &file_name)
{
    IOutputDataWriteStrategy *result(0);
    if(DataFormatUtils::isIntFile(file_name)) {
        result = new OutputDataWriteINTStrategy();
    }

    else if(DataFormatUtils::isTxtFile(file_name)) {
        result = new OutputDataWriteNumpyTXTStrategy();
    }

#ifdef BORNAGAIN_TIFF_SUPPORT
    else if(DataFormatUtils::isTiffFile(file_name)) {
        result = new OutputDataWriteTiffStrategy();
    }
#endif // BORNAGAIN_TIFF_SUPPORT

    else {
        throw Exceptions::LogicErrorException("OutputDataWriteFactory::getWriter() -> Error. "
                "Don't know how to write file '" + file_name+std::string("'"));
    }

    return result;
}
