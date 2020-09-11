// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/mainwindow/OutputDataIOService.h
//! @brief     Defines class OutputDataIOService
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_MAINWINDOW_OUTPUTDATAIOSERVICE_H
#define BORNAGAIN_GUI_COREGUI_MAINWINDOW_OUTPUTDATAIOSERVICE_H

#include "GUI/coregui/mainwindow/OutputDataIOHistory.h"
#include "Wrap/WinDllMacros.h"
#include <QObject>

class ApplicationModels;
class MessageService;
class SaveLoadInterface;

//! Provide read/write of heavy data files in a separate thread.
//!
//! Listens all models and keep tracks of changes in items. Provides logic to
//! not to re-save already saved data.

class BA_CORE_API_ OutputDataIOService : public QObject
{
    Q_OBJECT
public:
    explicit OutputDataIOService(QObject* parent = nullptr);
    explicit OutputDataIOService(ApplicationModels* models, QObject* parent = nullptr);

    void setApplicationModels(ApplicationModels* models);

    void save(const QString& projectDir);

    void load(const QString& projectDir, MessageService* messageService = nullptr);

    QVector<SaveLoadInterface*> nonXMLItems() const;

private:
    void cleanOldFiles(const QString& projectDir, const QStringList& oldSaves,
                       const QStringList& newSaves);

    OutputDataIOHistory m_history;
    ApplicationModels* m_applicationModels;
};

#endif // BORNAGAIN_GUI_COREGUI_MAINWINDOW_OUTPUTDATAIOSERVICE_H
