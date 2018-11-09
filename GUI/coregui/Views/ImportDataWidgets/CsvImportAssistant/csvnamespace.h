#ifndef CSVNAMESPACE_H
#define CSVNAMESPACE_H

#include <vector>
#include <QString>

namespace csv{
typedef std::vector<std::vector<std::string>> DataArray ;
typedef std::vector<std::string> DataRow;
typedef std::vector<std::string> DataColumn;
bool isAscii(QString filename);
}



#endif // CSVNAMESPACE_H
