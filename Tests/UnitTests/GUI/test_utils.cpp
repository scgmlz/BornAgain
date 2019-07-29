// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/UnitTests/GUI/test_utils.cpp
//! @brief     Implements auxiliary test functions in a namespace.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "test_utils.h"
#include "GUIHelpers.h"
#include "IntensityDataIOFactory.h"
#include "IntensityDataFunctions.h"
#include "OutputData.h"
#include "ProjectUtils.h"
#include "RealDataItem.h"
#include "SessionModel.h"

namespace {
const int nxsize = 5;
const int nysize = 10;
}

void TestUtils::create_dir(const QString& dir_name)
{
    if (ProjectUtils::exists(dir_name))
        ProjectUtils::removeRecursively(dir_name);

    GUIHelpers::createSubdir(".", dir_name);
}

std::unique_ptr<OutputData<double>> TestUtils::createData(double value, DIM n_dim)
{
    std::unique_ptr<OutputData<double>> result(new OutputData<double>());
    result->addAxis("x", nxsize, -1.0, 1.0);
    if (n_dim == DIM::D2)
        result->addAxis("y", nysize, 0.0, 2.0);
    result->setAllTo(value);
    return result;
}

RealDataItem* TestUtils::createRealData(const QString& name, SessionModel& model, double value,
                                        DIM n_dim)
{
    RealDataItem* result = dynamic_cast<RealDataItem*>(
        model.insertNewItem(Constants::RealDataType));
    result->setOutputData(createData(value, n_dim).release());
    result->setItemValue(SessionItem::P_NAME, name);
    return result;
}

bool TestUtils::isTheSame(const OutputData<double>& data1, const OutputData<double>& data2)
{
    double diff = IntensityDataFunctions::getRelativeDifference(data1, data2);
    return diff < 1e-10;
}

bool TestUtils::isTheSame(const QString& fileName, const OutputData<double>& data)
{
    std::unique_ptr<OutputData<double>> dataOnDisk(
        IntensityDataIOFactory::readOutputData(fileName.toStdString()));
    return isTheSame(*dataOnDisk, data);
}
