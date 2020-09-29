// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/InputOutput/OutputDataReader.h
//! @brief     Defines class OutputDataReader.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_CORE_INPUTOUTPUT_OUTPUTDATAREADER_H
#define BORNAGAIN_CORE_INPUTOUTPUT_OUTPUTDATAREADER_H

#include "Core/InputOutput/OutputDataReadStrategy.h"
#include <memory>

template <class T> class OutputData;

//! Reads OutputData from file using different reading strategies.
//! @ingroup input_output_internal

class OutputDataReader
{
public:
    OutputDataReader(const std::string& file_name);

    //! read output data from file (file name was set already from OutputDataIOFactory)
    OutputData<double>* getOutputData();

    //! Sets concrete reading strategy
    void setStrategy(IOutputDataReadStrategy* read_strategy);

private:
    std::string m_file_name;
    std::unique_ptr<IOutputDataReadStrategy> m_read_strategy;
};

#endif // BORNAGAIN_CORE_INPUTOUTPUT_OUTPUTDATAREADER_H
