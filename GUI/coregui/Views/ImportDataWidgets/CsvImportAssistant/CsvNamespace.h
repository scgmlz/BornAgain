#ifndef CSVNAMESPACE_H
#define CSVNAMESPACE_H

#include <QString>
#include <vector>

namespace csv
{
typedef std::vector<std::vector<std::string>> DataArray;
typedef std::vector<std::string> DataRow;
typedef std::vector<std::string> DataColumn;
bool isAscii(QString filename);
double atof(std::string str);
double atof(QString str);
}

#endif // CSVNAMESPACE_H
