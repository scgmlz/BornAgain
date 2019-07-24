// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/InputOutput/OutputDataWriter.cpp
//! @brief     Implements class OutputDataWriter.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "OutputDataWriter.h"
#include "OutputData.h"
#include "DataFormatUtils.h"
#ifdef _WIN32
#pragma warning ( push )
#pragma warning ( disable: 4244 4275 )
#include "boost_streams.h"
#pragma warning ( pop )
#else
#include "boost_streams.h"
#endif
#include <fstream>
#include "FileSystemUtils.h"

OutputDataWriter::OutputDataWriter(const std::string& file_name)
    : m_file_name(file_name)
{
}

void OutputDataWriter::writeOutputData(const OutputData<double>& data)
{
    using namespace DataFormatUtils;
    if(!m_write_strategy)
        throw Exceptions::NullPointerException("OutputDataWriter::getOutputData() ->"
                                               " Error! No read strategy defined");

    std::ofstream fout;
    std::ios_base::openmode openmode = std::ios::out;
    if(isTiffFile(m_file_name) || isCompressed(m_file_name))
        openmode = std::ios::out | std::ios_base::binary;

#ifdef _WIN32
    fout.open(FileSystemUtils::convert_utf8_to_utf16(m_file_name), openmode);
#else
    fout.open(m_file_name, openmode);
#endif

    if(!fout.is_open())
        throw Exceptions::FileNotIsOpenException("OutputDataWriter::writeOutputData() -> Error. "
                                                 "Can't open file '"+m_file_name+"' for writing.");
    if (!fout.good())
        throw Exceptions::FileIsBadException("OutputDataReader::writeOutputData() -> Error! "
                                             "File is not good, probably it is a directory.");
    std::stringstream ss;
    m_write_strategy->writeOutputData(data, ss);

    boost::iostreams::filtering_streambuf<boost::iostreams::input> input_filtered;
    if(DataFormatUtils::isGZipped(m_file_name))
        input_filtered.push(boost::iostreams::gzip_compressor());
    else if(DataFormatUtils::isBZipped(m_file_name))
        input_filtered.push(boost::iostreams::bzip2_compressor());
    input_filtered.push(ss);

    boost::iostreams::copy(input_filtered, fout);

    fout.close();
}


void OutputDataWriter::setStrategy(IOutputDataWriteStrategy* write_strategy)
{
    m_write_strategy.reset(write_strategy);
}
