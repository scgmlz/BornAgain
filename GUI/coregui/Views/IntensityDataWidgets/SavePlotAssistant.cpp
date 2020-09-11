// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/IntensityDataWidgets/SavePlotAssistant.cpp
//! @brief     Implements class SavePlotAssistant
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/coregui/Views/IntensityDataWidgets/SavePlotAssistant.h"
#include "Core/Basics/Assert.h"
#include "Core/InputOutput/IntensityDataIOFactory.h"
#include "GUI/coregui/Views/IntensityDataWidgets/ColorMap.h"
#include <QFileDialog>
#include <QMessageBox>

namespace
{
const QString png_extension = ".png";
const QString jpg_extension = ".jpg";
const QString pdf_extension = ".pdf";
const QString int_extension = ".int";
const QString tif_extension = ".tif";
const QString txt_extension = ".txt";

QVector<SavePlotAssistant::Format> initializeFormats()
{
    QVector<SavePlotAssistant::Format> result;
    result.push_back(SavePlotAssistant::Format(png_extension, "png Image (*.png)"));
    result.push_back(SavePlotAssistant::Format(jpg_extension, "jpg Image (*.jpg)"));
    result.push_back(SavePlotAssistant::Format(pdf_extension, "pdf File (*.pdf)"));
    result.push_back(SavePlotAssistant::Format(int_extension, "BornAgain ASCII format (*.int)"));
    result.push_back(SavePlotAssistant::Format(txt_extension, "Simple ASCII table (*.txt)"));
#ifdef BORNAGAIN_TIFF_SUPPORT
    result.push_back(SavePlotAssistant::Format(tif_extension, "32-bits TIFF files (*.tif)"));
#endif
    return result;
}

} // namespace

QVector<SavePlotAssistant::Format> SavePlotAssistant::m_formats = initializeFormats();

SavePlotAssistant::Format::Format(const QString& file_extention, const QString& filter)
    : m_file_extention(file_extention), m_filter(filter)
{
}

void SavePlotAssistant::savePlot(const QString& dirname, QCustomPlot* plot,
                                 OutputData<double>* output_data)

{
    QString selectedFilter("*.png");
    QString defaultName = dirname + "/untitled";
    QString fileName = QFileDialog::getSaveFileName(0, "Save Plot", defaultName, getFilterString(),
                                                    &selectedFilter);

    QString nameToSave = composeFileName(fileName, selectedFilter);

    if (!nameToSave.isEmpty()) {
        try {
            saveToFile(nameToSave, plot, output_data);
        } catch (const std::exception& ex) {
            QString message = "Attempt to save file with the name '";
            message.append(nameToSave);
            message.append("' has failed with following error message\n\n");
            message.append(QString::fromStdString(ex.what()));
            QMessageBox::warning(0, "Houston, we have a problem.", message);
        }
    }
}

void SavePlotAssistant::saveToFile(const QString& fileName, QCustomPlot* plot,
                                   OutputData<double>* output_data)
{
    if (isPngFile(fileName)) {
        plot->savePng(fileName);
    }

    else if (isJpgFile(fileName)) {
        plot->saveJpg(fileName);
    }

    else if (isPdfFile(fileName)) {
        plot->savePdf(fileName, plot->width(), plot->height());
    }

    else {
        ASSERT(output_data);
        IntensityDataIOFactory::writeOutputData(*output_data, fileName.toStdString());
    }
}

//! Returns string contraining all defined filters in the format suitable for QFileDialog
QString SavePlotAssistant::getFilterString() const
{
    QString result;
    for (int i = 0; i < m_formats.size(); ++i) {
        result.append(m_formats[i].m_filter);
        if (i != m_formats.size() - 1)
            result.append(";;");
    }
    return result;
}

//! Compose file name to save plot from information provided by QFileDialog
QString SavePlotAssistant::composeFileName(const QString& fileName, const QString& filterName) const
{
    QString result;
    if (!fileName.isEmpty() && !filterName.isEmpty()) {
        if (isValidExtension(fileName)) {
            result = fileName;
        } else {
            result = fileName + getExtensionFromFilterName(filterName);
        }
    }
    return result;
}

bool SavePlotAssistant::isValidExtension(const QString& fileName) const
{
    for (int i = 0; i < m_formats.size(); ++i) {
        if (fileName.endsWith(m_formats[i].m_file_extention, Qt::CaseInsensitive)) {
            return true;
        }
    }
    return false;
}

QString SavePlotAssistant::getExtensionFromFilterName(const QString& filterName) const
{
    for (int i = 0; i < m_formats.size(); ++i) {
        if (m_formats[i].m_filter == filterName) {
            return m_formats[i].m_file_extention;
        }
    }
    return "";
}

bool SavePlotAssistant::isPngFile(const QString& fileName) const
{
    return fileName.endsWith(png_extension, Qt::CaseInsensitive);
}

bool SavePlotAssistant::isJpgFile(const QString& fileName) const
{
    return fileName.endsWith(jpg_extension, Qt::CaseInsensitive);
}

bool SavePlotAssistant::isPdfFile(const QString& fileName) const
{
    return fileName.endsWith(pdf_extension, Qt::CaseInsensitive);
}
