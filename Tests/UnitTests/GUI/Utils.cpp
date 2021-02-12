//  ************************************************************************************************
//
//  BornAgain: simulate and fit reflection and scattering
//
//! @file      Tests/UnitTests/GUI/Utils.cpp
//! @brief     Implements auxiliary test functions in a namespace.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
//  ************************************************************************************************

#include "Tests/UnitTests/GUI/Utils.h"
#include "Device/Data/DataUtils.h"
#include "Device/Histo/IntensityDataIOFactory.h"
#include "GUI/coregui/Models/RealDataItem.h"
#include "GUI/coregui/Models/SessionModel.h"
#include "GUI/coregui/mainwindow/ProjectUtils.h"
#include "GUI/coregui/utils/GUIHelpers.h"
#include <QDir>

namespace {
const int nxsize = 5;
const int nysize = 10;
} // namespace

void GuiUnittestUtils::create_dir(const QString& dir_name)
{
    if (ProjectUtils::exists(dir_name))
        ProjectUtils::removeRecursively(dir_name);

    if (!QDir(".").mkdir(dir_name))
        throw GUIHelpers::Error("GuiUnittestUtils::create_dir() -> Error. Can't create '" + dir_name
                                + "' in parent directory '.'.");
}

std::unique_ptr<OutputData<double>> GuiUnittestUtils::createData(double value, DIM n_dim)
{
    std::unique_ptr<OutputData<double>> result(new OutputData<double>());
    result->addAxis("x", nxsize, -1.0, 1.0);
    if (n_dim == DIM::D2)
        result->addAxis("y", nysize, 0.0, 2.0);
    result->setAllTo(value);
    return result;
}

RealDataItem* GuiUnittestUtils::createRealData(const QString& name, SessionModel& model,
                                               double value, DIM n_dim)
{
    auto result = model.insertItem<RealDataItem>();
    result->setOutputData(createData(value, n_dim).release());
    result->setName(name);
    return result;
}

bool GuiUnittestUtils::isTheSame(const OutputData<double>& data1, const OutputData<double>& data2)
{
    double diff = DataUtils::relativeDataDifference(data1, data2);
    return diff < 1e-10;
}

bool GuiUnittestUtils::isTheSame(const QString& fileName, const OutputData<double>& data)
{
    std::unique_ptr<OutputData<double>> dataOnDisk(
        IntensityDataIOFactory::readOutputData(fileName.toStdString()));
    return isTheSame(*dataOnDisk, data);
}
