// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/InputOutput/OutputDataWriter.h
//! @brief     Defines class OutputDataWriter.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_CORE_INPUTOUTPUT_OUTPUTDATAWRITER_H
#define BORNAGAIN_CORE_INPUTOUTPUT_OUTPUTDATAWRITER_H

#include "Core/InputOutput/OutputDataWriteStrategy.h"
#include <memory>

template <class T> class OutputData;

//! Write OutputData to file using different witing strategies.
//! @ingroup input_output_internal

class BA_CORE_API_ OutputDataWriter
{
public:
    OutputDataWriter(const std::string& file_name);

    //! Writes output data to file.
    void writeOutputData(const OutputData<double>& data);

    //! Sets concrete writing strategy.
    void setStrategy(IOutputDataWriteStrategy* write_strategy);

private:
    std::string m_file_name;
    std::unique_ptr<IOutputDataWriteStrategy> m_write_strategy;
};

#endif // BORNAGAIN_CORE_INPUTOUTPUT_OUTPUTDATAWRITER_H
