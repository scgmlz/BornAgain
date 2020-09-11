// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/mainwindow/newprojectdialog.cpp
//! @brief     Implements class NewProjectDialog
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/coregui/mainwindow/newprojectdialog.h"
#include "GUI/coregui/mainwindow/projectdocument.h"
#include <QFileDialog>
#include <QGroupBox>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>

NewProjectDialog::NewProjectDialog(QWidget* parent, const QString& workingDirectory,
                                   const QString& projectName)
    : QDialog(parent), m_projectNameEdit(0), m_workDirEdit(0), m_browseButton(0), m_warningLabel(0),
      m_cancelButton(0), m_createButton(0), m_valid_projectName(true), m_valid_projectPath(true)

{
    setMinimumSize(480, 280);
    setWindowTitle("New project");

    QLabel* nameLabel = new QLabel("Project name:");
    m_projectNameEdit = new QLineEdit;
    m_projectNameEdit->setText("Untitled");
    connect(m_projectNameEdit, SIGNAL(textEdited(QString)), this,
            SLOT(checkIfProjectNameIsValid(QString)));
    nameLabel->setBuddy(m_projectNameEdit);

    QLabel* parentDirLabel = new QLabel("Create in:");
    m_workDirEdit = new QLineEdit;
    m_workDirEdit->setText(QDir::homePath());
    connect(m_workDirEdit, SIGNAL(textEdited(QString)), this,
            SLOT(checkIfProjectPathIsValid(QString)));
    parentDirLabel->setBuddy(m_workDirEdit);

    m_browseButton = new QPushButton("Browse");
    connect(m_browseButton, SIGNAL(clicked()), this, SLOT(onBrowseDirectory()));

    m_warningLabel = new QLabel();

    m_createButton = new QPushButton("Create");
    connect(m_createButton, SIGNAL(clicked()), this, SLOT(createProjectDir()));
    m_createButton->setDefault(true);
    m_cancelButton = new QPushButton("Cancel");
    connect(m_cancelButton, SIGNAL(clicked()), this, SLOT(reject()));

    QGroupBox* projectGroup = new QGroupBox("Project name and location");

    QGridLayout* layout = new QGridLayout;
    layout->addWidget(nameLabel, 0, 0);
    layout->addWidget(m_projectNameEdit, 0, 1);
    layout->addWidget(parentDirLabel, 1, 0);
    layout->addWidget(m_workDirEdit, 1, 1);
    layout->addWidget(m_browseButton, 1, 2);

    projectGroup->setLayout(layout);

    QHBoxLayout* buttonsLayout = new QHBoxLayout;
    buttonsLayout->addStretch(1);
    buttonsLayout->addWidget(m_createButton);
    buttonsLayout->addWidget(m_cancelButton);

    QVBoxLayout* mainLayout = new QVBoxLayout;
    mainLayout->addWidget(projectGroup);
    mainLayout->addWidget(m_warningLabel);
    mainLayout->addStretch();
    mainLayout->addLayout(buttonsLayout);

    setLayout(mainLayout);

    setWorkingDirectory(workingDirectory);
    setProjectName(projectName);
}

QString NewProjectDialog::getWorkingDirectory() const
{
    return m_workDirEdit->text();
}

void NewProjectDialog::setWorkingDirectory(const QString& text)
{
    return m_workDirEdit->setText(text);
}

void NewProjectDialog::setProjectName(const QString& text)
{
    return m_projectNameEdit->setText(text);
}

QString NewProjectDialog::getProjectFileName() const
{
    QString projectDir = getWorkingDirectory() + QString("/") + getProjectName();
    QString projectFile = getProjectName() + ProjectDocument::projectFileExtension();
    QString result = projectDir + QString("/") + projectFile;
    return result;
}

//! calls directory selection dialog
void NewProjectDialog::onBrowseDirectory()
{
    QString dirname = QFileDialog::getExistingDirectory(
        this, "Select directory", getWorkingDirectory(),
        QFileDialog::DontResolveSymlinks | QFileDialog::ShowDirsOnly);

    if (!dirname.isEmpty()) {
        checkIfProjectPathIsValid(dirname);
        checkIfProjectNameIsValid(getProjectName());
    }
}

//! Returns true if ProjectPath is valid. Corresponding directory should exists.
void NewProjectDialog::checkIfProjectPathIsValid(const QString& dirname)
{
    if (QFile::exists(dirname)) {
        setValidProjectPath(true);
        m_workDirEdit->setText(dirname);
    } else {
        setValidProjectPath(false);
    }
    updateWarningStatus();
}

//! Returns true if project name is valid. There should not be the directory with such
//! name in ProjectPath
void NewProjectDialog::checkIfProjectNameIsValid(const QString& projectName)
{
    QDir projectDir = getWorkingDirectory() + "/" + projectName;
    if (projectDir.exists()) {
        setValidProjectName(false);
    } else {
        setValidProjectName(true);
    }
    updateWarningStatus();
}

//! sets flags wether project name is valid and then updates color of LineEdit
//! and warning message
void NewProjectDialog::setValidProjectName(bool status)
{
    m_valid_projectName = status;
    QPalette palette;
    if (m_valid_projectName) {
        palette.setColor(QPalette::Text, Qt::black);
    } else {
        palette.setColor(QPalette::Text, Qt::darkRed);
    }
    m_projectNameEdit->setPalette(palette);
}

//! sets flags wether project path is valid and then updates color of LineEdit
//! and warning message
void NewProjectDialog::setValidProjectPath(bool status)
{
    m_valid_projectPath = status;
    QPalette palette;
    if (m_valid_projectPath) {
        palette.setColor(QPalette::Text, Qt::black);
    } else {
        palette.setColor(QPalette::Text, Qt::darkRed);
    }
    m_workDirEdit->setPalette(palette);
}

//! updates warning label depending on validity of project name and path
void NewProjectDialog::updateWarningStatus()
{
    if (m_valid_projectPath && m_valid_projectName) {
        m_createButton->setEnabled(true);
        m_warningLabel->setText("");
    } else if (!m_valid_projectPath) {
        m_createButton->setEnabled(false);
        m_warningLabel->setText("<font color='darkRed'> The path '" + getWorkingDirectory()
                                + "' does not exist. </font>");
    } else if (!m_valid_projectName) {
        m_createButton->setEnabled(false);
        if (getProjectName().isEmpty()) {
            m_warningLabel->setText("<font color='darkRed'> Please specify project name. </font>");
        } else {
            m_warningLabel->setText("<font color='darkRed'> The directory '" + getProjectName()
                                    + "' already exists. </font>");
        }
    }
}

//! creates directory with selected ProjectName in selected ProjectPath
void NewProjectDialog::createProjectDir()
{
    QDir parentDir = getWorkingDirectory();
    if (!parentDir.mkdir(getProjectName())) {
        m_warningLabel->setText("<font color='darkRed'> Can't make subdirectory' '"
                                + getProjectName() + "' in '" + getWorkingDirectory()
                                + "' </font>");
    } else {
        accept();
    }
}
