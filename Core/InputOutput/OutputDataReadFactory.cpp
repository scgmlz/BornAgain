// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/InputOutput/OutputDataReadFactory.cpp
//! @brief     Implements class OutputDataReadFactory.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Core/InputOutput/OutputDataReadFactory.h"
#include "Core/Basics/Exceptions.h"
#include "Core/InputOutput/DataFormatUtils.h"

OutputDataReader* OutputDataReadFactory::getReader(const std::string& file_name)
{
    OutputDataReader* result = new OutputDataReader(file_name);
    result->setStrategy(getReadStrategy(file_name));
    return result;
}

OutputDataReader* OutputDataReadFactory::getReflectometryReader(const std::string& file_name)
{
    OutputDataReader* result = new OutputDataReader(file_name);
    result->setStrategy(new OutputDataReadReflectometryStrategy());
    return result;
}

IOutputDataReadStrategy* OutputDataReadFactory::getReadStrategy(const std::string& file_name)
{
    IOutputDataReadStrategy* result(nullptr);
    if (DataFormatUtils::isIntFile(file_name))
        result = new OutputDataReadINTStrategy();
#ifdef BORNAGAIN_TIFF_SUPPORT
    else if (DataFormatUtils::isTiffFile(file_name))
        result = new OutputDataReadTiffStrategy();
#endif // BORNAGAIN_TIFF_SUPPORT
    else
        // Try to read ASCII by default. Binary maps to ASCII.
        // If the file is not actually a matrix of numbers,
        // the error will be thrown during the reading.
        result = new OutputDataReadNumpyTXTStrategy();
    return result;
}
