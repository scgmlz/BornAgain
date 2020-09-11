// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/utils/GUIHelpers.cpp
//! @brief     Implements GUIHelpers functions
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/coregui/utils/GUIHelpers.h"
#include "BAVersion.h"
#include "GUI/coregui/Models/JobItem.h"
#include "GUI/coregui/Models/RealDataItem.h"
#include <QApplication>
#include <QDateTime>
#include <QDir>
#include <QMessageBox>
#include <QPushButton>
#include <QTextStream>
#include <QUuid>

namespace
{
QMap<QString, QString> initializeCharacterMap()
{
    QMap<QString, QString> result;
    result["\\"] = "_backslash_";
    result["/"] = "_slash_";
    result["\""] = "_quote_";
    result["<"] = "_lessthan_";
    result[">"] = "_greaterthan_";
    result["|"] = "_pipe_";
    result["?"] = "_questionmark_";
    return result;
}

const QMap<QString, QString> invalidCharacterMap = initializeCharacterMap();
} // Anonymous namespace

namespace GUIHelpers
{

Error::~Error() noexcept = default;

const char* Error::what() const noexcept
{
    return message.toLatin1().data();
}

void information(QWidget* parent, const QString& title, const QString& text,
                 const QString& detailedText)
{
    QScopedPointer<QMessageBox> messageBox(new QMessageBox(parent));
    if (parent)
        messageBox->setWindowModality(Qt::WindowModal);
    messageBox->setWindowTitle(QString("%1 - %2").arg(QApplication::applicationName()).arg(title));
    messageBox->setText(text);
    if (!detailedText.isEmpty())
        messageBox->setInformativeText(detailedText);
    messageBox->setIcon(QMessageBox::Information);
    messageBox->addButton(QMessageBox::Ok);
    messageBox->exec();
}

void warning(QWidget* parent, const QString& title, const QString& text,
             const QString& detailedText)
{
    QScopedPointer<QMessageBox> messageBox(new QMessageBox(parent));
    if (parent)
        messageBox->setWindowModality(Qt::WindowModal);
    messageBox->setWindowTitle(QString("%1 - %2").arg(QApplication::applicationName()).arg(title));
    messageBox->setText(text);
    if (!detailedText.isEmpty())
        messageBox->setInformativeText(detailedText);
    messageBox->setIcon(QMessageBox::Warning);
    messageBox->addButton(QMessageBox::Ok);
    messageBox->exec();
}

bool question(QWidget* parent, const QString& title, const QString& text,
              const QString& detailedText, const QString& yesText, const QString& noText)
{
    QScopedPointer<QMessageBox> messageBox(new QMessageBox(parent));
    if (parent)
        messageBox->setWindowModality(Qt::WindowModal);
    messageBox->setWindowTitle(QString("%1 - %2").arg(QApplication::applicationName()).arg(title));
    messageBox->setText(text);
    if (!detailedText.isEmpty())
        messageBox->setInformativeText(detailedText);
    messageBox->setIcon(QMessageBox::Question);
    QAbstractButton* yesButton = messageBox->addButton(yesText, QMessageBox::AcceptRole);
    messageBox->addButton(noText, QMessageBox::RejectRole);
    messageBox->setDefaultButton(qobject_cast<QPushButton*>(yesButton));
    messageBox->exec();
    return messageBox->clickedButton() == yesButton;
}

bool okToDelete(QWidget* parent, const QString& title, const QString& text,
                const QString& detailedText)
{
    QScopedPointer<QMessageBox> messageBox(new QMessageBox(parent));
    if (parent)
        messageBox->setWindowModality(Qt::WindowModal);
    messageBox->setIcon(QMessageBox::Question);
    messageBox->setWindowTitle(QString("%1 - %2").arg(QApplication::applicationName()).arg(title));
    messageBox->setText(text);
    if (!detailedText.isEmpty())
        messageBox->setInformativeText(detailedText);
    QAbstractButton* deleteButton = messageBox->addButton("&Delete", QMessageBox::AcceptRole);
    messageBox->addButton("Do &Not Delete", QMessageBox::RejectRole);
    messageBox->setDefaultButton(qobject_cast<QPushButton*>(deleteButton));
    messageBox->exec();
    return messageBox->clickedButton() == deleteButton;
}

QString getBornAgainVersionString()
{
    return QString::fromStdString(BornAgain::GetVersionNumber());
}

//! Returns valid file name to be saved on disk. This name is constructed from proposed_name
//! by replacing all special characters with text representation
//! \ backslash
//! / slash
//! " quote
//! < lessthan
//! > greaterthan
//! | pipe
//! ? questionmark
QString getValidFileName(const QString& proposed_name)
{
    QString result = proposed_name;
    for (auto it = invalidCharacterMap.begin(); it != invalidCharacterMap.end(); ++it) {
        result.replace(it.key(), it.value());
    }
    return result;
}

//! parses version string into 3 numbers, returns true in the case of success
bool parseVersion(const QString& version, int& major_num, int& minor_num, int& patch_num)
{
    major_num = minor_num = patch_num = 0;
    bool success(true);
    QStringList nums = version.split(".");
    if (nums.size() != 3)
        return false;

    bool ok(false);
    major_num = nums.at(0).toInt(&ok);
    success &= ok;
    minor_num = nums.at(1).toInt(&ok);
    success &= ok;
    patch_num = nums.at(2).toInt(&ok);
    success &= ok;

    return success;
}

int versionCode(const QString& version)
{
    int result(-1);

    int ba_major(0), ba_minor(0), ba_patch(0);
    if (!parseVersion(version, ba_major, ba_minor, ba_patch))
        return result;

    result = ba_major * 10000 + ba_minor * 100 + ba_patch;

    return result;
}

//! returns true if current BornAgain version match minimal required version
bool isVersionMatchMinimal(const QString& version, const QString& minimal_version)
{
    return versionCode(version) >= versionCode(minimal_version);
}

//! Returns file directory from the full file path
QString fileDir(const QString& fileName)
{
    QFileInfo info(fileName);
    if (info.exists()) {
        return info.dir().path();
    }
    return "";
}

//! Returns base name of file.

QString baseName(const QString& fileName)
{
    QFileInfo info(fileName);
    return info.baseName();
}

//! Creates sub directory in given parent directory (should exist).
//! If sub-directory already exists, no action will be taken.

void createSubdir(const QString& parentName, const QString& subdirName)
{
    QDir projectDir(parentName);
    if (!projectDir.exists(subdirName)) {
        if (!projectDir.mkdir(subdirName))
            throw GUIHelpers::Error("GUIHelpers::createSubdir() -> Error. Can't create '"
                                    + subdirName + "' in parent directory '" + parentName + "'.");
    }
}

QString currentDateTime()
{
    return QDateTime::currentDateTime().toString("yyyy.MM.dd hh:mm:ss");
    ;
}

// QStringList fromStdList(const std::list<std::string> &string_list)
//{
//    QStringList result;
//    for(std::string str : string_list) {
//        result.append(QString::fromStdString(str));
//    }
//    return result;
//}

QVector<double> fromStdVector(const std::vector<double>& data)
{
    QVector<double> result;
    result.reserve(int(data.size()));
    std::copy(data.begin(), data.end(), std::back_inserter(result));
    return result;
}

QStringList fromStdStrings(const std::vector<std::string>& container)
{
    QStringList result;
    for (std::string str : container) {
        result.append(QString::fromStdString(str));
    }
    return result;
}

QString createUuid()
{
    return QUuid::createUuid().toString();
}

QString readTextFile(const QString& fileName)
{
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        throw GUIHelpers::Error("PyImportAssistant::readFile() -> Error. Can't read file '"
                                + fileName + "'");
    QTextStream in(&file);
    return in.readAll();
}

} // namespace GUIHelpers
