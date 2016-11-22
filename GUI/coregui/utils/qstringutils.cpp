// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/utils/qstringutils.cpp
//! @brief     Implements functions from Utils namespace
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "qstringutils.h"
#include "hostosinfo.h"
#include <QDir>

namespace GUI_StringUtils
{

QString withTildeHomePath(const QString &path)
{
    if (GUI_OS_Utils::HostOsInfo::isWindowsHost())
        return path;

    static const QString homePath = QDir::homePath();

    QFileInfo fi(QDir::cleanPath(path));
    QString outPath = fi.absoluteFilePath();
    if (outPath.startsWith(homePath))
        outPath = QLatin1Char('~') + outPath.mid(homePath.size());
    else
        outPath = path;
    return outPath;
}

} // namespace GUI_StringUtils
