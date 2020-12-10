//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/Core/Consistence/CompareTwoReferences.cpp
//! @brief     Implements function compareTwoReferences for use in core consistence test
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "BATesting.h"
#include "Base/Utils/FileSystemUtils.h"
#include "Device/Data/DataUtils.h"
#include "Device/Histo/IntensityDataIOFactory.h"
#include <iostream>

namespace {

std::unique_ptr<OutputData<double>> load(const std::string& name) {
    ASSERT(name != "");
    const std::string path =
        FileSystemUtils::jointPath(BATesting::ReferenceDir_Std(), name + ".int.gz");
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

} // namespace

int compareTwoReferences(const std::string& name0, const std::string& name1, const double limit) {
    std::unique_ptr<OutputData<double>> data0 = load(name0);
    std::unique_ptr<OutputData<double>> data1 = load(name1);

    return DataUtils::checkRelativeDifference(*data0, *data1, limit);
}
