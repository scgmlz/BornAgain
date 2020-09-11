// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/IntensityDataWidgets/SaveProjectionsAssistant.cpp
//! @brief     Implements class SaveProjectionsAssistant
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/coregui/Views/IntensityDataWidgets/SaveProjectionsAssistant.h"
#include "Core/Intensity/Histogram1D.h"
#include "Core/Intensity/Histogram2D.h"
#include "Core/Tools/PyFmt.h"
#include "GUI/coregui/Models/IntensityDataItem.h"
#include "GUI/coregui/Models/MaskItems.h"
#include "GUI/coregui/Models/ProjectionItems.h"
#include "GUI/coregui/mainwindow/ProjectUtils.h"
#include "GUI/coregui/utils/GUIHelpers.h"
#include <QFileDialog>
#include <QTextStream>

namespace
{
const int bin_centers_colwidth = 12;
const int bin_values_colwidth = 20;

QString to_scientific_str(double value)
{
    auto str = pyfmt::printScientificDouble(value);
    return QString("%1").arg(QString::fromStdString(str), -bin_values_colwidth);
}

QString to_double_str(double value)
{
    auto str = pyfmt::printDouble(value);
    return QString("%1").arg(QString::fromStdString(str), -bin_centers_colwidth);
}
} // unnamed namespace

SaveProjectionsAssistant::SaveProjectionsAssistant() = default;
SaveProjectionsAssistant::~SaveProjectionsAssistant() = default;

//! Calls file open dialog and writes projection data as ASCII

void SaveProjectionsAssistant::saveProjections(QWidget* parent, IntensityDataItem* intensityItem)
{
    ASSERT(intensityItem);

    QString defaultName = ProjectUtils::userExportDir() + "/untitled.txt";
    QString fileName = QFileDialog::getSaveFileName(parent, "Save projections data", defaultName);

    if (fileName.isEmpty())
        return;

    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        throw GUIHelpers::Error("TestProjectUtils::createTestFile() -> Error. "
                                "Can't create file");

    m_hist2d.reset(new Histogram2D(*intensityItem->getOutputData()));

    QTextStream out(&file);

    out << "# Projections along x-axis (horizontal projections) \n";
    out << projectionsToString("HorizontalLineMask", intensityItem);
    out << "\n";

    out << "# Projections along y-axis (vertical projections) \n";
    out << projectionsToString("VerticalLineMask", intensityItem);
    out << "\n";

    file.close();
}

//! Generates multi-line string with projections data of given type (horizontal, vertical).

QString SaveProjectionsAssistant::projectionsToString(const QString& projectionsType,
                                                      IntensityDataItem* intensityItem)
{
    QString result;
    QTextStream out(&result);

    auto projData = projectionsData(projectionsType, intensityItem);

    if (projData.projections.isEmpty())
        return result;

    out << projectionFileHeader(projData);

    auto bin_centers = projData.bin_centers;

    for (int i_point = 0; i_point < bin_centers.size(); ++i_point) {
        out << to_double_str(bin_centers[i_point]) << " ";
        for (auto& data : projData.projections) {
            out << to_scientific_str(data.bin_values[i_point]);
        }
        out << "\n";
    }
    return result;
}

//! Returns projections data for all projections of given type (horizontal, vertical).

SaveProjectionsAssistant::ProjectionsData
SaveProjectionsAssistant::projectionsData(const QString& projectionsType,
                                          IntensityDataItem* intensityItem)
{
    ProjectionsData result;
    projectionsType == "VerticalLineMask" ? result.is_horizontal = false
                                          : result.is_horizontal = true;

    for (auto item : projectionItems(projectionsType, intensityItem)) {
        std::unique_ptr<Histogram1D> hist;
        SaveProjectionsAssistant::Projection data;

        if (item->modelType() == "HorizontalLineMask") {
            data.axis_value = item->getItemValue(HorizontalLineItem::P_POSY).toDouble();
            hist.reset(m_hist2d->projectionX(data.axis_value));
        } else {
            data.axis_value = item->getItemValue(VerticalLineItem::P_POSX).toDouble();
            hist.reset(m_hist2d->projectionY(data.axis_value));
        }

#if QT_VERSION >= QT_VERSION_CHECK(5, 14, 0)
        auto values = hist->getBinValues();
        auto centers = hist->getBinCenters();
        data.bin_values = QVector<double>(values.begin(), values.end());
        if (result.bin_centers.isEmpty())
            result.bin_centers = QVector<double>(centers.begin(), centers.end());
#else
        data.bin_values = QVector<double>::fromStdVector(hist->getBinValues());
        if (result.bin_centers.isEmpty())
            result.bin_centers = QVector<double>::fromStdVector(hist->getBinCenters());
#endif

        result.projections.push_back(data);
    }
    return result;
}

//! Returns vector of ProjectionItems sorted according to axis value.

QVector<SessionItem*> SaveProjectionsAssistant::projectionItems(const QString& projectionsType,
                                                                IntensityDataItem* intensityItem)
{
    auto result = intensityItem->projectionContainerItem()->getChildrenOfType(projectionsType);
    std::sort(result.begin(), result.end(), [=](SessionItem* item1, SessionItem* item2) {
        QString propertyName = HorizontalLineItem::P_POSY;
        if (projectionsType != "HorizontalLineMask")
            propertyName = VerticalLineItem::P_POSX;

        return item1->getItemValue(propertyName).toDouble()
               < item2->getItemValue(propertyName).toDouble();
    });
    return result;
}

//! Returns projections header. For projections along x it will be
//! "# x         y=6.0194            y=33.5922           y=61.9417"

QString SaveProjectionsAssistant::projectionFileHeader(ProjectionsData& projectionsData)
{
    QString xcol, ycol;

    projectionsData.is_horizontal ? xcol = "# x" : xcol = "# y";
    projectionsData.is_horizontal ? ycol = " y=" : ycol = " x=";

    QString result;
    result.append(QString("%1").arg(xcol, -bin_centers_colwidth));

    for (auto& data : projectionsData.projections)
        result.append(QString("%1%2").arg(ycol).arg(data.axis_value,
                                                    -(bin_values_colwidth - ycol.size()), 'f', 4));
    result.append("\n");

    return result;
}
