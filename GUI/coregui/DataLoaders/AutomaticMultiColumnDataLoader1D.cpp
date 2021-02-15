//  ************************************************************************************************
//
//  BornAgain: simulate and fit reflection and scattering
//
//! @file      GUI/coregui/DataLoaders/AutomaticMultiRowDataLoader1D.cpp
//! @brief     Implements class AutomaticMultiRowDataLoader1D
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2021
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "GUI/coregui/DataLoaders/AutomaticMultiColumnDataLoader1D.h"
#include "Device/InputOutput/DataFormatUtils.h"
#include "qcustomplot.h"
#include <QFile>
#include <QString>
#include <QTextStream>

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

QString AutomaticMultiColumnDataLoader1D::name() const
{
    return "Automatic 1D import (multiple rows)";
}

QString AutomaticMultiColumnDataLoader1D::info() const
{
    return "Supports up to 4 columns (Q versus R, dR, dQ). Separator only space or tab. Column "
           "order is fixed (Q, R, dR, dQ)";
}

QString AutomaticMultiColumnDataLoader1D::persistentClassName() const
{
    return "AutomaticMultiColumnDataLoader1D";
}

QVector<QVector<QString>> AutomaticMultiColumnDataLoader1D::parsedData() const
{
    return QVector<QVector<QString>>();
}

QString AutomaticMultiColumnDataLoader1D::preview(const QString& filepath,
                                                  QCustomPlot* plotWidget) const
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
    QStringList entries;

    entries << "Q"
            << "R";
    if (ncols > 2)
        entries << "dR";
    if (ncols > 3)
        entries << "dQ";

    for (size_t row = 0; row < nrows; row++) {
        if (vecVec[row].size() != ncols)
            return "Error: The number of columns varies among the rows";

        entries << QString::number(vecVec[row][0]);
        double Q = vecVec[row][0];
        switch (ncols) {
        case 1:
            break;
        case 2:
            entries << QString::number(vecVec[row][1]);
            QvsR[Q] = vecVec[row][1];
            QvsDR[Q] = 0;
            QvsDQ[Q] = 0;
            break;
        case 3:
            entries << QString::number(vecVec[row][1]);
            entries << QString::number(vecVec[row][2]);
            QvsR[Q] = vecVec[row][1];
            QvsDR[Q] = vecVec[row][2];
            QvsDQ[Q] = 0;
            break;
        case 4:
            entries << QString::number(vecVec[row][1]);
            entries << QString::number(vecVec[row][2]);
            entries << QString::number(vecVec[row][3]);
            QvsR[Q] = vecVec[row][1];
            QvsDR[Q] = vecVec[row][2];
            QvsDQ[Q] = vecVec[row][3];
            break;
        }
    }

    if (entries.size() == ncols) // only header entries
        return "No data found";

    QString s = bold("Data table:");

    s += table((int)ncols, entries, "border=\"1\" cellpadding=\"10\" cellspacing=\"0\"", true);

    QVector<double> qVec;
    QVector<double> rVec;
    for (auto it = QvsR.begin(); it != QvsR.end(); ++it) {
        if (it->second <= 0)
            continue;
        qVec.push_back(it->first);
        rVec.push_back(it->second);
    }

    auto graph = plotWidget->addGraph();
    graph->addData(qVec, rVec);
    plotWidget->rescaleAxes();

    return "<p>" + bold("Information: ") + info() + "</p><p>" + s + "</p>";
}
