//  ************************************************************************************************
//
//  BornAgain: simulate and fit reflection and scattering
//
//! @file      GUI/coregui/DataLoaders/AutomaticDataLoader1D.cpp
//! @brief     Implements class AutomaticDataLoader1D
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2021
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "GUI/coregui/DataLoaders/AutomaticDataLoader1D.h"
#include "Base/Axis/PointwiseAxis.h"
#include "Device/Data/OutputData.h"
#include "Device/InputOutput/DataFormatUtils.h"
#include "qcustomplot.h"
#include <QFile>
#include <QString>
#include <QTextStream>
#include <QVector>

namespace {
QString bold(const QString& text)
{
    return "<b>" + text + "</b>";
}

QString table(int nColumns, const QStringList& entries, const QString& attributes /*= ""*/,
              bool bHasHorizontalHeader /*= false*/)
{
    QString result = "<table " + attributes + "><tr>";
    int col = 0;
    bool bShowAsHorizontalHeader = bHasHorizontalHeader;
    for (QStringList::size_type i = 0; i < entries.size(); i++) {
        if (bShowAsHorizontalHeader) {
            result += "<th>" + entries[i] + "</th>";
        } else {
            result += "<td valign=\"top\">" + entries[i] + "</td>";
        }

        col++;
        if ((col == nColumns) && (i < entries.size() - 1)) // start new line?
        {
            result += "</tr><tr>";
            col = 0;
            bShowAsHorizontalHeader = false;
        }
    }
    result += "</tr></table>";

    return result;
}
} // namespace

QString AutomaticDataLoader1D::name() const
{
    return "Automatic 1D import (legacy BornAgain 1.18.0)";
}

QString AutomaticDataLoader1D::info() const
{
    return "Supports 2 columns only (Q versus R). Separator only space or tab. Column order is "
           "fixed (Q,R). Additional columns are ignored.";
}

QString AutomaticDataLoader1D::persistentClassName() const
{
    return "AutomaticDataLoader1D";
}

QString AutomaticDataLoader1D::preview(const QString& filepath, QCustomPlot* plotWidget) const
{
    std::string line;
    std::vector<std::vector<double>> vecVec;
    std::map<double, double> QvsR;
    std::map<double, double> QvsDR;
    std::map<double, double> QvsDQ;

    // Read numbers from file:
    QFile file(filepath);
    if (!file.open(QFile::ReadOnly)) {
        return "File '" + filepath + "' could not be opened";
    }

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine().trimmed();
        try {
            // #migration +++ this works only if separator is space or tab; it does not
            // work e.g. with comma or semicolon
            std::vector<double> rowVec = DataFormatUtils::parse_doubles(line.toStdString());
            vecVec.push_back(rowVec);
        } catch (...) { // #migration +++ This eats useful errors away...
            continue;
        }
    }

    // validate - There is at least one row and at least two columns
    size_t nrows = vecVec.size();
    if (nrows < 1)
        return "Error: no numerical values found";
    size_t ncols = vecVec[0].size();
    if (ncols < 2)
        return "Error: Minimum 2 columns required";

    // Assign Q vs R, dR, dQ:
    for (size_t row = 0; row < nrows; row++) {
        if (vecVec[row].size() != ncols)
            throw std::runtime_error("The number of columns varies among the rows");
        double Q = vecVec[row][0];
        switch (ncols) {
        case 1:
            break;
        case 2:
            QvsR[Q] = vecVec[row][1];
            QvsDR[Q] = 0;
            QvsDQ[Q] = 0;
            break;
        case 3:
            QvsR[Q] = vecVec[row][1];
            QvsDR[Q] = vecVec[row][2];
            QvsDQ[Q] = 0;
            break;
        case 4:
            QvsR[Q] = vecVec[row][1];
            QvsDR[Q] = vecVec[row][2];
            QvsDQ[Q] = vecVec[row][3];
            break;
        }
    }

    QVector<double> qVec;
    QVector<double> rVec;
    for (auto it = QvsR.begin(); it != QvsR.end(); ++it) {
        if (it->second <= 0)
            continue;
        qVec.push_back(it->first);
        rVec.push_back(it->second);
    }

    if (qVec.empty())
        return "No data found";

    OutputData<double> oData;
    oData.addAxis(PointwiseAxis("qVector", qVec.toStdVector()));
    oData.setRawDataVector(rVec.toStdVector());

    auto graph = plotWidget->addGraph();
    graph->addData(qVec, rVec);
    plotWidget->rescaleAxes();
    return outputDataToTable(oData);
}

QString AutomaticDataLoader1D::outputDataToTable(const OutputData<double>& outputData) const
{
    auto size = outputData.axis(0).size();
    auto dataValues = outputData.getRawDataVector();

    if (size == 0)
        return "No data found";

    if (size != dataValues.size())
        return "Wrong content - value count does not match axis count";

    QStringList entries;
    entries << "Q"
            << "R";
    for (auto i = 0; i < size; i++) {
        entries << QString::number(outputData.axis(0).binCenter(i));
        entries << QString::number(dataValues[i]);
    }

    QString s = "Data table:";

    s += table(2, entries, "border=\"1\" cellspacing=\"0\"", true);

    return "<p>Information: " + info() + "</p><p>" + s + "</p>";
}
