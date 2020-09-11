// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/mainwindow/SaveThread.cpp
//! @brief     Defines SaveThread classes
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/coregui/mainwindow/SaveThread.h"
#include "Core/Basics/Assert.h"
#include "GUI/coregui/mainwindow/projectdocument.h"

SaveThread::SaveThread(QObject* parent) : QThread(parent), m_document(nullptr) {}

SaveThread::~SaveThread()
{
    wait();
}

void SaveThread::run()
{
    ASSERT(m_document);
    m_document->save_project_data(m_projectFile);
    emit saveReady();
}

void SaveThread::setSaveContext(ProjectDocument* document, const QString& project_file_name)
{
    m_document = document;
    m_projectFile = project_file_name;
}
