// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/InputOutput/OutputDataReader.cpp
//! @brief     Implements class OutputDataReader.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "OutputDataReader.h"
#include "OutputData.h"
#include "DataFormatUtils.h"
#include "boost_streams.h"
#include <fstream>

OutputDataReader::OutputDataReader(const std::string& file_name)
    : m_file_name(file_name)
{}

OutputData<double>* OutputDataReader::getOutputData()
{
    if(!m_read_strategy)
        throw Exceptions::NullPointerException(
            "OutputDataReader::getOutputData() -> Error! No read strategy defined");

    std::ifstream fin;
    std::ios_base::openmode openmode = std::ios::in;
    if (DataFormatUtils::isBinaryFile(m_file_name))
        openmode = std::ios::in | std::ios_base::binary;

    fin.open(m_file_name.c_str(), openmode );
    if(!fin.is_open())
        throw Exceptions::FileNotIsOpenException(
            "OutputDataReader::getOutputData() -> Error. Can't open file '"
            + m_file_name + "' for reading.");
    if (!fin.good())
        throw Exceptions::FileIsBadException(
            "OutputDataReader::getOutputData() -> Error! "
            "File is not good, probably it is a directory.");
    OutputData<double>* result = getFromFilteredStream(fin);
    fin.close();
    return result;
}

void OutputDataReader::setStrategy(IOutputDataReadStrategy* read_strategy)
{
    m_read_strategy.reset(read_strategy);
}

OutputData<double>* OutputDataReader::getFromFilteredStream(std::istream& input_stream)
{
    boost::iostreams::filtering_streambuf<boost::iostreams::input> input_filtered;
    if (DataFormatUtils::isGZipped(m_file_name))
        input_filtered.push(boost::iostreams::gzip_decompressor());
    else if (DataFormatUtils::isBZipped(m_file_name))
        input_filtered.push(boost::iostreams::bzip2_decompressor());
    input_filtered.push(input_stream);
    // we use stringstream since it provides random access which is important for tiff files
    std::stringstream strstream;
    boost::iostreams::copy(input_filtered, strstream);
    return m_read_strategy->readOutputData(strstream);
}
