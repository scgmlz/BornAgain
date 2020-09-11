// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/InputOutput/OutputDataWriteFactory.cpp
//! @brief     Implements class OutputDataWriteFactory.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //
#include "Core/InputOutput/OutputDataWriteFactory.h"
#include "Core/Basics/Exceptions.h"
#include "Core/InputOutput/DataFormatUtils.h"

OutputDataWriter* OutputDataWriteFactory::getWriter(const std::string& file_name)
{
    OutputDataWriter* result = new OutputDataWriter(file_name);
    result->setStrategy(getWriteStrategy(file_name));
    return result;
}

IOutputDataWriteStrategy* OutputDataWriteFactory::getWriteStrategy(const std::string& file_name)
{
    IOutputDataWriteStrategy* result(nullptr);
    if (DataFormatUtils::isIntFile(file_name)) {
        result = new OutputDataWriteINTStrategy();
    }

#ifdef BORNAGAIN_TIFF_SUPPORT
    else if (DataFormatUtils::isTiffFile(file_name)) {
        result = new OutputDataWriteTiffStrategy();
    }
#endif // BORNAGAIN_TIFF_SUPPORT

    else {
        result = new OutputDataWriteNumpyTXTStrategy();
    }

    return result;
}
