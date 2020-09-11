// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/ImportDataWidgets/ImportDataUtils.cpp
//! @brief     Implements ImportDataUtils namespace
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/coregui/Views/ImportDataWidgets/ImportDataUtils.h"
#include "Core/Binning/PointwiseAxis.h"
#include "Core/InputOutput/IntensityDataIOFactory.h"
#include "GUI/coregui/Models/AxesItems.h"
#include "GUI/coregui/Models/InstrumentItems.h"
#include "GUI/coregui/Models/IntensityDataItem.h"
#include "GUI/coregui/Models/RealDataItem.h"
#include "GUI/coregui/Views/ImportDataWidgets/CsvImportAssistant/CsvImportAssistant.h"
#include "GUI/coregui/mainwindow/AppSvc.h"
#include "GUI/coregui/mainwindow/projectmanager.h"
#include "GUI/coregui/utils/GUIHelpers.h"
#include <QFileDialog>
#include <QFileInfo>
#include <QMessageBox>

namespace
{
const QString filter_string_ba = "Intensity File (*.int *.gz *.tif *.tiff *.txt *.csv);;"
                                 "Other (*.*)";
const QString filter_string_ascii = "Intensity File (*.int *.int.gz *.txt *.csv *.dat *.ascii);;"
                                    "Ascii column-wise data (*.*)";

int getRank(const RealDataItem& item)
{
    return static_cast<int>(item.shape().size());
}

int getRank(const InstrumentItem& item)
{
    return static_cast<int>(item.shape().size());
}
} // namespace

std::unique_ptr<OutputData<double>> ImportDataUtils::ImportKnownData(QString& fileName)
{
    // Try to use the canonical tools for importing data
    std::unique_ptr<OutputData<double>> result;
    try {
        std::unique_ptr<OutputData<double>> data(
            IntensityDataIOFactory::readOutputData(fileName.toStdString()));
        result = CreateSimplifiedOutputData(*data);
    } catch (std::exception& ex) {
        QString message = QString("Error while trying to read file\n\n'%1'\n\n%2")
                              .arg(fileName)
                              .arg(QString::fromStdString(std::string(ex.what())));
        QMessageBox::warning(nullptr, "IO Problem", message);
    }
    return result;
}

std::unique_ptr<OutputData<double>> ImportDataUtils::ImportReflectometryData(QString& fileName)
{
    std::unique_ptr<OutputData<double>> result;
    try {
        std::unique_ptr<OutputData<double>> data(
            IntensityDataIOFactory::readReflectometryData(fileName.toStdString()));
        result.swap(data);
    } catch (std::exception& ex) {
        QString message = QString("Error while trying to read file\n\n'%1'\n\n%2")
                              .arg(fileName)
                              .arg(QString::fromStdString(std::string(ex.what())));
        QMessageBox::warning(nullptr, "IO Problem", message);
    }
    return result;
}

std::unique_ptr<OutputData<double>> ImportDataUtils::Import2dData(QString& fileName)
{
    return ImportKnownData(fileName);
}

ImportDataInfo ImportDataUtils::Import1dData(QString& fileName)
{
    if (DataFormatUtils::isCompressed(fileName.toStdString())
        || DataFormatUtils::isIntFile(fileName.toStdString())
        || DataFormatUtils::isTiffFile(fileName.toStdString())) {
        try {
            return ImportDataInfo(ImportKnownData(fileName), AxesUnits::QSPACE);
        } catch (...) {
            return getFromImportAssistant(fileName);
        }
    } else {
        try {
            return ImportDataInfo(ImportReflectometryData(fileName), AxesUnits::QSPACE);
        } catch (...) {
            QString message =
                QString("There was a problem while trying to import data from "
                        "file:\n\n'%1'\n--\n%2\n--\n")
                    .arg(fileName)
                    .arg(
                        "Data format not supported. Please check your file in an external editor.");
            QMessageBox::warning(nullptr, "Unable to read.", message);

            return ImportDataInfo();
        }
    }
}

ImportDataInfo ImportDataUtils::getFromImportAssistant(QString& fileName)
{
    if (!csv::isAscii(fileName)) {
        QString message =
            QString(
                "There was a problem while trying to import data from file:\n\n'%1'\n--\n%2\n--\n")
                .arg(fileName)
                .arg("The file seems to contain binary data");
        QMessageBox::warning(nullptr, "Unable to read.", message);
        return ImportDataInfo();
    }
    try {
        CsvImportAssistant assistant(fileName, true);
        return assistant.getData();
    } catch (std::exception& e) {
        QString message =
            QString(
                "There was a problem while trying to import data from file:\n\n'%1'\n--\n%2\n--\n")
                .arg(fileName)
                .arg(QString::fromStdString(std::string(e.what())));
        QMessageBox::warning(nullptr, "IO Problem", message);
    }
    return ImportDataInfo();
}

bool ImportDataUtils::Compatible(const InstrumentItem& instrumentItem,
                                 const RealDataItem& realDataItem)
{
    return getRank(instrumentItem) == getRank(realDataItem);
}

std::unique_ptr<OutputData<double>>
ImportDataUtils::CreateSimplifiedOutputData(const OutputData<double>& data)
{
    const size_t data_rank = data.getRank();
    if (data_rank > 2 || data_rank < 1)
        throw std::runtime_error("Error in ImportDataUtils::CreateSimplifiedOutputData: passed "
                                 "array is neither 1D nor 2D");

    std::unique_ptr<OutputData<double>> result(new OutputData<double>);
    for (size_t i = 0; i < data_rank; ++i) {
        const IAxis& axis = data.getAxis(i);
        const size_t axis_size = axis.size();
        const double min = 0.0;
        const double max = axis_size;
        result->addAxis(FixedBinAxis(axis.getName(), axis_size, min, max));
    }
    result->setRawDataVector(data.getRawDataVector());

    return result;
}

QString ImportDataUtils::printShapeMessage(const std::vector<int>& instrument_shape,
                                           const std::vector<int>& data_shape)
{
    auto to_str = [](const std::vector<int>& shape) {
        std::string result;
        for (size_t i = 0, size = shape.size(); i < size; ++i) {
            result += std::to_string(shape[i]);
            if (i + 1 != size)
                result += ", ";
        }
        return result;
    };

    std::string message_string = "instrument [";
    message_string += to_str(instrument_shape);
    message_string += "], data [";
    message_string += to_str(data_shape);
    message_string += "]";
    return QString::fromStdString(std::move(message_string));
}
