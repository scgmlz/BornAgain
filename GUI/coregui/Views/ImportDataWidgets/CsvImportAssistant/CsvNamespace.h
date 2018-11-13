#ifndef CSVNAMESPACE_H
#define CSVNAMESPACE_H

#include <QString>
#include <QStringList>
#include <vector>

namespace csv
{
enum ColumnType { _intensity_, _theta_, _q_ };
const QStringList HeaderLabels{"Intensity", "theta", "q"};
const QStringList UnitsLabels{"default", "bin", "rad", "deg", "mm", "1/nm"};
typedef std::vector<std::vector<std::string>> DataArray;
typedef std::vector<std::string> DataRow;
typedef std::vector<std::string> DataColumn;
bool isAscii(QString filename);
double atof(std::string str);
double atof(QString str);
}

#endif // CSVNAMESPACE_H
