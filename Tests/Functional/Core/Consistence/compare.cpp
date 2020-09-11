// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/Core/Consistence/compare.cpp
//! @brief     Implements function compare for core consistence test
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "BABuild.h"
#include "BATesting.h"
#include "Core/Basics/Assert.h"
#include "Core/InputOutput/IntensityDataIOFactory.h"
#include "Core/Intensity/IntensityDataFunctions.h"
#include "Core/Multilayer/IMultiLayerBuilder.h"
#include "Core/Multilayer/MultiLayer.h"
#include "Core/Simulation/Simulation.h"
#include "Core/Simulation/SimulationFactory.h"
#include "Core/StandardSamples/SampleBuilderFactory.h"
#include "Core/Tools/FileSystemUtils.h"
#include <iostream>

std::unique_ptr<OutputData<double>> load(const std::string& name)
{
    ASSERT(name != "");
    const std::string path =
        FileSystemUtils::jointPath(BATesting::StdReferenceDir(), name + ".int.gz");
    std::unique_ptr<OutputData<double>> data;
    try {
        data.reset(IntensityDataIOFactory::readOutputData(path));
    } catch (const std::exception&) {
        std::cout << "Data file " << path << "not found.\n"
                  << "Run the pertinent Core standard test, copy the fresh data file"
                  << " to the reference directory,\n"
                  << "then rerun this test." << std::endl;
    }
    return data;
}

int compare(const std::string& name0, const std::string& name1, const double limit)
{
    std::unique_ptr<OutputData<double>> data0 = load(name0);
    std::unique_ptr<OutputData<double>> data1 = load(name1);

    return IntensityDataFunctions::checkRelativeDifference(*data0, *data1, limit);
}
