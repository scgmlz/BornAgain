//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Device/Histo/IntensityDataIOFactory.cpp
//! @brief     Implements class OutputDataIOFactory.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "Device/Histo/IntensityDataIOFactory.h"
#include "Base/Utils/FileSystemUtils.h"
#include "Device/Histo/IHistogram.h"
#include "Device/Histo/SimulationResult.h"
#include "Device/InputOutput/OutputDataReadReflectometry.h"
#include "Device/InputOutput/OutputDataReadWriteINT.h"
#include "Device/InputOutput/OutputDataReadWriteNumpyTXT.h"
#include "Device/InputOutput/OutputDataReadWriteTiff.h"
#include <exception>
#include <fstream>
#include <memory>

#include "Device/InputOutput/DataFormatUtils.h"

#ifdef _WIN32
#pragma warning(push)
#pragma warning(disable : 4244 4275)
#include "Device/InputOutput/boost_streams.h"
#pragma warning(pop)
#else
#include "Device/InputOutput/boost_streams.h"
#endif

OutputData<double>* IntensityDataIOFactory::readOutputData(const std::string& file_name) {
    if (DataFormatUtils::isIntFile(file_name))
        return readOutputData(
            file_name, [](std::istream& s) { return OutputDataReadWriteINT().readOutputData(s); });
#ifdef BORNAGAIN_TIFF_SUPPORT
    else if (DataFormatUtils::isTiffFile(file_name))
        return readOutputData(
            file_name, [](std::istream& s) { return OutputDataReadWriteTiff().readOutputData(s); });
#endif // BORNAGAIN_TIFF_SUPPORT

    // Try to read ASCII by default. Binary maps to ASCII.
    // If the file is not actually a matrix of numbers,
    // the error will be thrown during the reading.
    return readOutputData(
        file_name, [](std::istream& s) { return OutputDataReadWriteNumpyTXT().readOutputData(s); });
}

OutputData<double>* IntensityDataIOFactory::readReflectometryData(const std::string& file_name) {
    return readOutputData(
        file_name, [](std::istream& s) { return OutputDataReadReflectometry().readOutputData(s); });
}

IHistogram* IntensityDataIOFactory::readIntensityData(const std::string& file_name) {
    std::unique_ptr<OutputData<double>> data(readOutputData(file_name));
    if (!data)
        throw std::runtime_error("Could not read " + file_name);
    return IHistogram::createHistogram(*data);
}

void IntensityDataIOFactory::writeOutputData(const OutputData<double>& data,
                                             const std::string& file_name) {
    if (DataFormatUtils::isIntFile(file_name))
        writeOutputData(
            file_name, [&](std::ostream& s) { OutputDataReadWriteINT().writeOutputData(data, s); });
#ifdef BORNAGAIN_TIFF_SUPPORT
    else if (DataFormatUtils::isTiffFile(file_name))
        writeOutputData(file_name, [&](std::ostream& s) {
            OutputDataReadWriteTiff().writeOutputData(data, s);
        });
#endif // BORNAGAIN_TIFF_SUPPORT
    else
        writeOutputData(file_name, [&](std::ostream& s) {
            OutputDataReadWriteNumpyTXT().writeOutputData(data, s);
        });
}

void IntensityDataIOFactory::writeOutputData(const std::string& file_name,
                                             std::function<void(std::ostream&)> writeData) {
    using namespace DataFormatUtils;

    std::ofstream fout;
    std::ios_base::openmode openmode = std::ios::out;
    if (isTiffFile(file_name) || isCompressed(file_name))
        openmode = std::ios::out | std::ios_base::binary;

#ifdef _WIN32
    fout.open(FileSystemUtils::convert_utf8_to_utf16(file_name), openmode);
#else
    fout.open(file_name, openmode);
#endif

    if (!fout.is_open())
        throw std::runtime_error("IntensityDataIOFactory::writeOutputData() -> Error. "
                                 "Can't open file '"
                                 + file_name + "' for writing.");
    if (!fout.good())
        throw std::runtime_error("IntensityDataIOFactory::writeOutputData() -> Error! "
                                 "File is not good, probably it is a directory.");
    std::stringstream ss;
    writeData(ss);

    boost::iostreams::filtering_streambuf<boost::iostreams::input> input_filtered;
    if (DataFormatUtils::isGZipped(file_name))
        input_filtered.push(boost::iostreams::gzip_compressor());
    else if (DataFormatUtils::isBZipped(file_name))
        input_filtered.push(boost::iostreams::bzip2_compressor());
    input_filtered.push(ss);

    boost::iostreams::copy(input_filtered, fout);

    fout.close();
}

void IntensityDataIOFactory::writeIntensityData(const IHistogram& histogram,
                                                const std::string& file_name) {
    std::unique_ptr<OutputData<double>> data(histogram.createOutputData());
    writeOutputData(*data, file_name);
}

void IntensityDataIOFactory::writeSimulationResult(const SimulationResult& result,
                                                   const std::string& file_name) {
    auto data = result.data();
    writeOutputData(*data, file_name);
}

OutputData<double>*
IntensityDataIOFactory::readOutputData(const std::string& file_name,
                                       std::function<OutputData<double>*(std::istream&)> readData) {

    if (!FileSystemUtils::IsFileExists(file_name))
        return nullptr;

    using namespace DataFormatUtils;
    std::ifstream input_stream;
    std::ios_base::openmode openmode = std::ios::in;
    if (isTiffFile(file_name) || isCompressed(file_name))
        openmode = std::ios::in | std::ios_base::binary;

#ifdef _WIN32
    input_stream.open(FileSystemUtils::convert_utf8_to_utf16(file_name), openmode);
#else
    input_stream.open(file_name, openmode);
#endif

    if (!input_stream.is_open())
        throw std::runtime_error(
            "IntensityDataIOFactory::getFromFilteredStream() -> Error. Can't open file '"
            + file_name + "' for reading.");
    if (!input_stream.good())
        throw std::runtime_error("IntensityDataIOFactory::getFromFilteredStream() -> Error! "
                                 "File is not good, probably it is a directory.");

    boost::iostreams::filtering_streambuf<boost::iostreams::input> input_filtered;
    if (DataFormatUtils::isGZipped(file_name))
        input_filtered.push(boost::iostreams::gzip_decompressor());
    else if (DataFormatUtils::isBZipped(file_name))
        input_filtered.push(boost::iostreams::bzip2_decompressor());
    input_filtered.push(input_stream);
    // we use stringstream since it provides random access which is important for tiff files
    std::stringstream str;
    boost::iostreams::copy(input_filtered, str);

    return readData(str);
}
