// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/utils/GUIHelpers.h
//! @brief     Defines class GUIHelpers functions
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_UTILS_GUIHELPERS_H
#define BORNAGAIN_GUI_COREGUI_UTILS_GUIHELPERS_H

#include "Wrap/WinDllMacros.h"
#include <QStringList>
#include <QWidget>
#include <memory>
#include <sstream>

class JobItem;
class RealDataItem;

namespace GUIHelpers
{
class BA_CORE_API_ Error : public std::exception
{
public:
    explicit Error(const QString& message) noexcept : message(message) {}
    virtual ~Error() noexcept;

    Error(const Error&) = default;
    Error& operator=(const Error&) = default;
    Error(Error&&) = default;
    Error& operator=(Error&&) = default;

    const char* what() const noexcept override;

private:
    QString message;
};

BA_CORE_API_ void information(QWidget* parent, const QString& title, const QString& text,
                              const QString& detailedText = "");
BA_CORE_API_ void warning(QWidget* parent, const QString& title, const QString& text,
                          const QString& detailedText = "");
BA_CORE_API_ bool question(QWidget* parent, const QString& title, const QString& text,
                           const QString& detailedText = "", const QString& yesText = "&Yes",
                           const QString& noText = "&No");
BA_CORE_API_ bool okToDelete(QWidget* parent, const QString& title, const QString& text,
                             const QString& detailedText = "");

BA_CORE_API_ QString getBornAgainVersionString();

BA_CORE_API_ QString getValidFileName(const QString& proposed_name);

BA_CORE_API_ QString fileDir(const QString& fileName);
BA_CORE_API_ QString baseName(const QString& fileName);

BA_CORE_API_ void createSubdir(const QString& parentName, const QString& subdirName);

BA_CORE_API_ bool parseVersion(const QString& version, int& major_num, int& minor_num,
                               int& patch_num);

BA_CORE_API_ int versionCode(const QString& version);

BA_CORE_API_ bool isVersionMatchMinimal(const QString& version, const QString& minimal_version);

BA_CORE_API_ QString currentDateTime();

BA_CORE_API_ QStringList fromStdStrings(const std::vector<std::string>& container);

BA_CORE_API_ QVector<double> fromStdVector(const std::vector<double>& data);

BA_CORE_API_ QString createUuid();

BA_CORE_API_ QString readTextFile(const QString& fileName);

} // namespace GUIHelpers

inline std::ostream& operator<<(std::ostream& stream, const QString& str)
{
    stream << str.toStdString();
    return stream;
}

#endif // BORNAGAIN_GUI_COREGUI_UTILS_GUIHELPERS_H
