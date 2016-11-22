// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/InputOutput/DataFormatUtils.cpp
//! @brief     Implements class DataFormatUtils.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "DataFormatUtils.h"
#include "ConstKBinAxis.h"
#include "CustomBinAxis.h"
#include "FileSystemUtils.h"
#include "OutputData.h"
#include "StringUtils.h"
#include <iterator>
#include <iostream>

bool DataFormatUtils::isCompressed(const std::string& name)
{
    return isGZipped(name) || isBZipped(name);
}

//! Does name contain *.gz extension?

bool DataFormatUtils::isGZipped(const std::string& name)
{
    return FileSystemUtils::extension(name) == GzipExtention;
}

bool DataFormatUtils::isBZipped(const std::string& name)
{
    return FileSystemUtils::extension(name) == BzipExtention;
}


//! Returns file main extension (without .gz).

std::string DataFormatUtils::GetFileMainExtension(const std::string& name)
{
    std::string stripped_name(name);
    if(isGZipped(name)) {
        stripped_name = name.substr(0, name.size()-GzipExtention.size());
    }
    else if(isBZipped(name)) {
        stripped_name = name.substr(0, name.size()-BzipExtention.size());
    }
    return FileSystemUtils::extension(stripped_name);
}

bool DataFormatUtils::isBinaryFile(const std::string& file_name)
{
    // all compressed files are always binary.
    if(isCompressed(file_name)) return true;
    // uncompressed "int" or "txt" files are ascii
    if(isIntFile(file_name)) return false;
    if(isTxtFile(file_name)) return false;
    // the rest (e.g. tif) is also binary
    return true;
}

bool DataFormatUtils::isIntFile(const std::string& file_name)
{
    return GetFileMainExtension(file_name) == IntExtention;
}

bool DataFormatUtils::isTxtFile(const std::string& file_name)
{
    return GetFileMainExtension(file_name) == TxtExtention;
}

bool DataFormatUtils::isTiffFile(const std::string& file_name)
{
    return GetFileMainExtension(file_name) == TiffExtention;
}

//! Returns true if string representation of the axis contains one of
//! FixedBinAxis, ConstKBinAxis or CustomBinAxis to parse it later in
//! similar way.
bool DataFormatUtils::isSimilarToFixedBinAxisType(const std::string& line)
{
    return line.find(FixedBinAxisType) != std::string::npos ||
        line.find(ConstKBinAxisType) != std::string::npos ||
        line.find(CustomBinAxisType) != std::string::npos;
}

bool DataFormatUtils::isVariableBinAxisType(const std::string& line)
{
    return line.find(VariableBinAxisType) != std::string::npos;
}


//! Creates axis of certain type from input stream
IAxis *DataFormatUtils::createAxis(std::istream& input_stream)
{
    std::string line;
    std::getline(input_stream, line);

    if(isSimilarToFixedBinAxisType(line))
    {
        return createFixedBinAxis(line);
    }
    else if(isVariableBinAxisType(line))
    {
        return createVariableBinAxis(line);
    }
    else {
        throw Exceptions::LogicErrorException("DataFormatUtils::createAxis() -> Error. "
                                              "Unknown axis '"+line+"'");
    }
}

//! Create one of FixedBinAxis from string representation
//! FixedBinAxis("axis0", 10, -1, 1)
//! ConstKBinAxis("axis0", 10, -1, 1)
//! CustomBinAxis("axis0", 10, -1, 1)
IAxis *DataFormatUtils::createFixedBinAxis(std::string line)
{
    std::vector<std::string> to_replace = {",", "\"", "(", ")"};
    StringUtils::replaceItemsFromString(line, to_replace, " ");

    std::string type, name;
    size_t nbins(0);

    std::istringstream iss(line);
    if( !(iss >> type >> name >> nbins) )
        throw Exceptions::FormatErrorException(
            "DataFormatUtils::createFixedBinAxis() -> Error. Can't parse the string.");

    std::vector<double> boundaries;
    readLineOfDoubles(boundaries, iss);

    if(boundaries.size() != 2)
        throw Exceptions::FormatErrorException(
            "DataFormatUtils::createFixedBinAxis() -> Error. Can't parse the string at p2.");

    if(type == FixedBinAxisType) {
        return new FixedBinAxis(name, nbins, boundaries[0], boundaries[1]);
    }
    else if(type == ConstKBinAxisType) {
        return new ConstKBinAxis(name, nbins, boundaries[0], boundaries[1]);
    }
    else if(type == CustomBinAxisType) {
        return new CustomBinAxis(name, nbins, boundaries[0], boundaries[1]);
    }
    else {
        throw Exceptions::LogicErrorException(
            "DataFormatUtils::createOneOfFixedBinAxis() -> Error. Unexpected place.");
    }
}


//! Create VariableBinAxis from string representation
//! VariableBinAxis("axis0", 4, [-1, -0.5, 0.5, 1, 2])
IAxis *DataFormatUtils::createVariableBinAxis(std::string line)
{
    std::vector<std::string> to_replace = {",", "\"", "(", ")", "[", "]"};
    StringUtils::replaceItemsFromString(line, to_replace, " ");

    std::string type, name;
    size_t nbins(0);

    std::istringstream iss(line);
    if( !(iss >> type >> name >> nbins) )
        throw Exceptions::FormatErrorException(
            "DataFormatUtils::createVariableBinAxis() -> Error. Can't parse the string.");
    std::vector<double> boundaries;
    readLineOfDoubles(boundaries, iss);
    if(boundaries.size() != nbins+1)
        throw Exceptions::FormatErrorException(
            "DataFormatUtils::createVariableBinAxis() -> Error. Can't parse the string at p2.");
    return new VariableBinAxis(name, nbins, boundaries);
}

//! Fills output data raw buffer from input stream
void DataFormatUtils::fillOutputData(OutputData<double>* data, std::istream& input_stream)
{
    std::string line;
    data->setAllTo(0.0);
    OutputData<double>::iterator it = data->begin();
    while( std::getline(input_stream, line) ) {
        if(line.empty() || line[0] == '#') break;

        std::istringstream iss(line);
        std::vector<double> buffer;
        readLineOfDoubles(buffer, iss);
        for (auto value : buffer) {
            *it = value;
            ++it;
        }
    }
    if(it!= data->end())
        throw Exceptions::FormatErrorException(
            "DataFormatUtils::fillOutputData() -> Error while parsing data.");
}

//! Parse double values from string to vector of double

std::vector<double> DataFormatUtils::parse_doubles(const std::string& str)
{
    std::vector<double> result;
    std::istringstream iss(str);
    DataFormatUtils::readLineOfDoubles(result, iss);
    if( result.empty() ) {
        std::cout << "StringUtils::parse_doubles -> "
            "Warning! No parsed values in 1d vector of doubles." << std::endl;
        std::cout << "Line '" << str << "'" << std::endl;
    }
    return result;
}

void DataFormatUtils::readLineOfDoubles(std::vector<double>& buffer, std::istringstream& iss)
{
    iss.imbue(std::locale::classic());
    std::copy(std::istream_iterator<double>(iss),
              std::istream_iterator<double>(), back_inserter(buffer));
}
