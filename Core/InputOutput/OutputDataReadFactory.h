// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/InputOutput/OutputDataReadFactory.h
//! @brief     Defines class OutputDataReadFactory.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef OUTPUTDATAREADFACTORY_H
#define OUTPUTDATAREADFACTORY_H

#include "OutputDataReader.h"

//! Creates reader appropariate for given type of files.
//! @ingroup input_output_internal

class BA_CORE_API_ OutputDataReadFactory
{
public:
    static OutputDataReader* getReader(const std::string& file_name);

private:
    static IOutputDataReadStrategy* getReadStrategy(const std::string& file_name);
};

#endif // OUTPUTDATAREADFACTORY_H
