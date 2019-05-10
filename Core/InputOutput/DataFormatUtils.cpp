// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/InputOutput/DataFormatUtils.cpp
//! @brief     Implements class DataFormatUtils.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "DataFormatUtils.h"
#include "ConstKBinAxis.h"
#include "CustomBinAxis.h"
#include "FileSystemUtils.h"
#include "PointwiseAxis.h"
#include "OutputData.h"
#include "StringUtils.h"
#include <iterator>
#include <iostream>

namespace {
std::istringstream getAxisStringRepresentation(std::istream& input_stream);

template<class Axis>
std::unique_ptr<IAxis> createFixedBinLikeAxis(std::istringstream iss);
std::unique_ptr<IAxis> createVariableBinAxis(std::istringstream iss);
std::unique_ptr<IAxis> createPointwiseAxis(std::istringstream iss);

using createAxisFun = std::function<std::unique_ptr<IAxis>(std::istringstream iss)>;
const std::vector<std::pair<std::string, createAxisFun>> type_map = {
    {"ConstKBinAxis", createFixedBinLikeAxis<ConstKBinAxis>},
    {"CustomBinAxis", createFixedBinLikeAxis<CustomBinAxis>},
    {"FixedBinAxis", createFixedBinLikeAxis<FixedBinAxis>},
    {"PointwiseAxis", createPointwiseAxis},
    {"VariableBinAxis", createVariableBinAxis}};

const std::string GzipExtension = ".gz";
const std::string BzipExtension = ".bz2";
const std::string IntExtension = ".int";
const std::string TiffExtension = ".tif";
const std::string TiffExtension2 = ".tiff";
}

bool DataFormatUtils::isCompressed(const std::string& name)
{
    return isGZipped(name) || isBZipped(name);
}

//! Does name contain *.gz extension?

bool DataFormatUtils::isGZipped(const std::string& name)
{
    return FileSystemUtils::extension(name) == GzipExtension;
}

bool DataFormatUtils::isBZipped(const std::string& name)
{
    return FileSystemUtils::extension(name) == BzipExtension;
}


//! Returns file main extension (without .gz).

std::string DataFormatUtils::GetFileMainExtension(const std::string& name)
{
    std::string stripped_name(name);
    if(isGZipped(name)) {
        stripped_name = name.substr(0, name.size()-GzipExtension.size());
    } else if(isBZipped(name)) {
        stripped_name = name.substr(0, name.size()-BzipExtension.size());
    }
    return FileSystemUtils::extension(stripped_name);
}

bool DataFormatUtils::isIntFile(const std::string& file_name)
{
    return GetFileMainExtension(file_name) == IntExtension;
}

bool DataFormatUtils::isTiffFile(const std::string& file_name)
{
    return (GetFileMainExtension(file_name) == TiffExtension ||
            GetFileMainExtension(file_name) == TiffExtension2 );
}

//! Creates axis of certain type from input stream
std::unique_ptr<IAxis> DataFormatUtils::createAxis(std::istream& input_stream)
{
    auto iss = getAxisStringRepresentation(input_stream);
    std::string type;
    if (!(iss >> type))
        throw Exceptions::FormatErrorException(
            "Error in DataFormatUtils::createAxis:: couldn't read axis type from input");

    for (auto iter = type_map.cbegin(); iter != type_map.end(); ++iter)
        if (iter->first == type)
            return iter->second(std::move(iss));
    throw Exceptions::LogicErrorException("Error in DataFormatUtils::createAxis:"
                                          "Unknown axis type '"
                                          + type + "'");
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
        std::string out = str;
        const size_t max_string_length(10);
        if(out.size() > max_string_length)
            out.resize(max_string_length, ' ');
        out += " ...";
        throw std::runtime_error("DataFormatUtils::parse_doubles -> Error! Can't parse double "
                                 "values from a string '"+out+"'");
    }
    return result;
}

void DataFormatUtils::readLineOfDoubles(std::vector<double>& buffer, std::istringstream& iss)
{
    iss.imbue(std::locale::classic());
    std::copy(std::istream_iterator<double>(iss),
              std::istream_iterator<double>(), back_inserter(buffer));
}

namespace {
std::istringstream getAxisStringRepresentation(std::istream& input_stream)
{
    std::string line;
    std::getline(input_stream, line);
    const std::vector<std::string> to_replace = {",", "\"", "(", ")", "[", "]"};
    StringUtils::replaceItemsFromString(line, to_replace, " ");
    return std::istringstream(line);
}

//! Create one of FixedBinAxis from string representation
//! FixedBinAxis("axis0", 10, -1, 1)
//! ConstKBinAxis("axis0", 10, -1, 1)
//! CustomBinAxis("axis0", 10, -1, 1)
template<class Axis>
std::unique_ptr<IAxis> createFixedBinLikeAxis(std::istringstream iss)
{
    std::string name;
    size_t nbins(0);
    if( !(iss >> name >> nbins) )
        throw Exceptions::FormatErrorException(
            "createFixedBinLikeAxis() -> Error. Can't parse the string.");

    std::vector<double> boundaries;
    DataFormatUtils::readLineOfDoubles(boundaries, iss);
    if(boundaries.size() != 2)
        throw Exceptions::FormatErrorException(
            "Error in createFixedBinLikeAxis: Can't parse the string while "
            "reading boundaries.");

    return std::make_unique<Axis>(name, nbins, boundaries[0], boundaries[1]);
}


//! Create VariableBinAxis from string representation
//! VariableBinAxis("axis0", 4, [-1, -0.5, 0.5, 1, 2])
std::unique_ptr<IAxis> createVariableBinAxis(std::istringstream iss)
{
    std::string name;
    size_t nbins(0);
    if( !(iss >> name >> nbins) )
        throw Exceptions::FormatErrorException(
            "Error in createVariableBinAxis: Can't parse the string.");

    std::vector<double> boundaries;
    DataFormatUtils::readLineOfDoubles(boundaries, iss);
    if(boundaries.size() != nbins+1)
        throw Exceptions::FormatErrorException(
            "Error in createVariableBinAxis: wrong number of boundaries read.");

    return std::make_unique<VariableBinAxis>(name, nbins, boundaries);
}

//! Create createPointwiseAxis from string representation
//! PointwiseAxis("axis0", [-0.5, 0.5, 1, 2])
std::unique_ptr<IAxis> createPointwiseAxis(std::istringstream iss)
{
    std::string name;
    if (!(iss >> name))
        throw Exceptions::FormatErrorException(
            "Error in createPointwiseAxis:Can't parse the string.");

    std::vector<double> coordinates;
    DataFormatUtils::readLineOfDoubles(coordinates, iss);

    return std::make_unique<PointwiseAxis>(name, coordinates);
}
}
