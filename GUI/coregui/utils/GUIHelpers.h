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

#include <QStringList>
#include <QWidget>
#include <memory>
#include <sstream>

class JobItem;
class RealDataItem;

namespace GUIHelpers
{
class Error : public std::exception
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

void information(QWidget* parent, const QString& title, const QString& text,
                 const QString& detailedText = "");
void warning(QWidget* parent, const QString& title, const QString& text,
             const QString& detailedText = "");
bool question(QWidget* parent, const QString& title, const QString& text,
              const QString& detailedText = "", const QString& yesText = "&Yes",
              const QString& noText = "&No");
bool okToDelete(QWidget* parent, const QString& title, const QString& text,
                const QString& detailedText = "");

QString getBornAgainVersionString();

QString getValidFileName(const QString& proposed_name);

QString fileDir(const QString& fileName);
QString baseName(const QString& fileName);

void createSubdir(const QString& parentName, const QString& subdirName);

bool parseVersion(const QString& version, int& major_num, int& minor_num, int& patch_num);

int versionCode(const QString& version);

bool isVersionMatchMinimal(const QString& version, const QString& minimal_version);

QString currentDateTime();

QStringList fromStdStrings(const std::vector<std::string>& container);

QVector<double> fromStdVector(const std::vector<double>& data);

QString createUuid();

QString readTextFile(const QString& fileName);

} // namespace GUIHelpers

inline std::ostream& operator<<(std::ostream& stream, const QString& str)
{
    stream << str.toStdString();
    return stream;
}

#endif // BORNAGAIN_GUI_COREGUI_UTILS_GUIHELPERS_H
