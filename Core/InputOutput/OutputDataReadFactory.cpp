// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/InputOutput/OutputDataReadFactory.cpp
//! @brief     Implements class OutputDataReadFactory.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "OutputDataReadFactory.h"
#include "Exceptions.h"
#include "DataFormatUtils.h"

OutputDataReader* OutputDataReadFactory::getReader(const std::string& file_name)
{
    OutputDataReader* result = new OutputDataReader(file_name);
    result->setStrategy(getReadStrategy(file_name));
    return result;
}

IOutputDataReadStrategy* OutputDataReadFactory::getReadStrategy(const std::string& file_name)
{
    IOutputDataReadStrategy* result(nullptr);
    if(DataFormatUtils::isIntFile(file_name))
        result = new OutputDataReadINTStrategy();
    else if(DataFormatUtils::isTxtFile(file_name))
        result = new OutputDataReadNumpyTXTStrategy();
#ifdef BORNAGAIN_TIFF_SUPPORT
    else if(DataFormatUtils::isTiffFile(file_name))
       result = new OutputDataReadTiffStrategy();
#endif // BORNAGAIN_TIFF_SUPPORT
    else
        throw Exceptions::LogicErrorException(
            "OutputDataReadFactory::getReader() -> Error. Don't know how to read file '"
            + file_name+"'");
    return result;
}
