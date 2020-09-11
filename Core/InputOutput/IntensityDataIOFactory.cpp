// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/InputOutput/IntensityDataIOFactory.cpp
//! @brief     Implements class OutputDataIOFactory.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Core/InputOutput/IntensityDataIOFactory.h"
#include "Core/InputOutput/OutputDataReadFactory.h"
#include "Core/InputOutput/OutputDataWriteFactory.h"
#include "Core/Instrument/SimulationResult.h"
#include "Core/Intensity/IHistogram.h"
#include "Core/Tools/FileSystemUtils.h"
#include <exception>
#include <fstream>
#include <memory>

OutputData<double>* IntensityDataIOFactory::readOutputData(const std::string& file_name)
{
    if (!FileSystemUtils::IsFileExists(file_name))
        return nullptr;
    std::unique_ptr<OutputDataReader> reader(OutputDataReadFactory::getReader(file_name));
    if (reader)
        return reader->getOutputData();
    return nullptr;
}

OutputData<double>* IntensityDataIOFactory::readReflectometryData(const std::string& file_name)
{
    if (!FileSystemUtils::IsFileExists(file_name))
        return nullptr;
    std::unique_ptr<OutputDataReader> reader(
        OutputDataReadFactory::getReflectometryReader(file_name));
    if (reader)
        return reader->getOutputData();
    return nullptr;
}

IHistogram* IntensityDataIOFactory::readIntensityData(const std::string& file_name)
{
    std::unique_ptr<OutputData<double>> data(readOutputData(file_name));
    if (!data)
        throw std::runtime_error("Could not read " + file_name);
    return IHistogram::createHistogram(*data);
}

void IntensityDataIOFactory::writeOutputData(const OutputData<double>& data,
                                             const std::string& file_name)
{
    auto* writer = OutputDataWriteFactory::getWriter(file_name);
    writer->writeOutputData(data);
    delete writer;
}

void IntensityDataIOFactory::writeIntensityData(const IHistogram& histogram,
                                                const std::string& file_name)
{
    std::unique_ptr<OutputData<double>> data(histogram.createOutputData());
    writeOutputData(*data, file_name);
}

void IntensityDataIOFactory::writeSimulationResult(const SimulationResult& result,
                                                   const std::string& file_name)
{
    auto data = result.data();
    writeOutputData(*data, file_name);
}
