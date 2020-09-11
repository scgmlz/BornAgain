// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/InputOutput/OutputDataWriteFactory.h
//! @brief     Defines class OutputDataWriteFactory.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_CORE_INPUTOUTPUT_OUTPUTDATAWRITEFACTORY_H
#define BORNAGAIN_CORE_INPUTOUTPUT_OUTPUTDATAWRITEFACTORY_H

#include "Core/InputOutput/OutputDataWriter.h"

//! Creates writer appropariate for given type of files.
//! @ingroup input_output_internal

class BA_CORE_API_ OutputDataWriteFactory
{
public:
    static OutputDataWriter* getWriter(const std::string& file_name);

private:
    static IOutputDataWriteStrategy* getWriteStrategy(const std::string& file_name);
};

#endif // BORNAGAIN_CORE_INPUTOUTPUT_OUTPUTDATAWRITEFACTORY_H
