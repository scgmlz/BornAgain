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

#include "ImportDataUtils.h"
#include "AppSvc.h"
#include "AxesItems.h"
#include "BornAgainNamespace.h"
#include "GUIHelpers.h"
#include "InstrumentItems.h"
#include "IntensityDataIOFactory.h"
#include "IntensityDataItem.h"
#include "RealDataItem.h"
#include "CsvImportAssistant.h"
#include "projectmanager.h"
#include <QFileDialog>
#include <QFileInfo>
#include <QMessageBox>

namespace
{
const QString filter_string = "Intensity File (*.int *.gz *.tif *.tiff *.txt *.csv);;"
                              "Other (*)";

int getRank(const RealDataItem& item)
{
    return static_cast<int>(item.shape().size());
}

int getRank(const InstrumentItem& item) {
    return static_cast<int>(item.shape().size());
}
}

std::unique_ptr<OutputData<double>> ImportDataUtils::ImportData(QString& baseNameOfLoadedFile)
{
    QString dirname = AppSvc::projectManager()->userImportDir();
    QString fileName = QFileDialog::getOpenFileName(Q_NULLPTR, QStringLiteral("Open Intensity File"),
                                                    dirname, filter_string);

    std::unique_ptr<OutputData<double>> result;

    QString newImportDir = GUIHelpers::fileDir(fileName);
    if (newImportDir != dirname)
        AppSvc::projectManager()->setImportDir(newImportDir);

    if (fileName.isEmpty())
        return nullptr;

    QFileInfo info(fileName);
    baseNameOfLoadedFile = info.baseName();

    //Try to use the canonical tools for importing data
    try {
        std::unique_ptr<OutputData<double>> data(
                    IntensityDataIOFactory::readOutputData(fileName.toStdString()));
        result = CreateSimplifiedOutputData(*data.get());

    } catch(std::exception& e)
            //Try to import data using the GUI importer
    {
        std::unique_ptr<OutputData<double>> data;
        if(!UseImportAssistant(dirname, fileName, data))
            return nullptr;

        result = CreateSimplifiedOutputData(*data.get());
    }
    return result;
}

bool ImportDataUtils::UseImportAssistant(QString& dirname, QString& fileName, std::unique_ptr<OutputData<double>>& result){
    try{
        CsvImportAssistant assistant(dirname,fileName);
        int res = assistant.exec();
        if(res == assistant.Accepted){
            result = assistant.getData();
            return true;
        }
    }catch(std::exception& e){
        QString message = QString("Unable to read file:\n\n'%1'\n\n%2\n\nCheck that the file exists and it is not being used by other program.\n\n")
                .arg(fileName)
                .arg(QString::fromStdString(std::string(e.what())));
        QMessageBox::warning(nullptr, "IO Problem", message);
        return false;
    }
    return false;
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
