// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/InfoWidgets/ProjectLoadWarningDialog.cpp
//! @brief     Implements class ProjectLoadWarningDialog
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/coregui/Views/InfoWidgets/ProjectLoadWarningDialog.h"
#include "GUI/coregui/Views/SampleDesigner/DesignerHelper.h"
#include "GUI/coregui/utils/GUIHelpers.h"
#include "GUI/coregui/utils/GUIMessage.h"
#include "GUI/coregui/utils/MessageService.h"
#include <QBoxLayout>
#include <QGridLayout>
#include <QHeaderView>
#include <QLabel>
#include <QPushButton>
#include <QTableWidget>
#include <QTableWidgetItem>

namespace
{
const int top_panel_height = 80;
}

ProjectLoadWarningDialog::ProjectLoadWarningDialog(QWidget* parent,
                                                   const MessageService* messageService,
                                                   const QString& documentVersion)
    : QDialog(parent), m_messageService(messageService), m_projectDocumentVersion(documentVersion)
{
    setMinimumSize(256, 256);
    resize(520, 620);
    setWindowTitle("Problems encountered while loading project");
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    auto mainLayout = new QVBoxLayout;
    mainLayout->addWidget(createTopPanel());
    mainLayout->addWidget(createModelInfoPanel());
    mainLayout->addWidget(createExplanationPanel());
    mainLayout->addWidget(createDetailsPanel());
    mainLayout->addLayout(buttonLayout());

    setLayout(mainLayout);
    setAttribute(Qt::WA_DeleteOnClose, true);
}

//! Top panel with warning icon and the header
QWidget* ProjectLoadWarningDialog::createTopPanel()
{
    auto result = new QWidget(this);
    auto layout = new QHBoxLayout;

    auto warningLabel = new QLabel;
    warningLabel->setPixmap(QPixmap(":/images/warning_64x64.png"));

    auto warningWidget = new QWidget;
    warningWidget->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    warningWidget->resize(top_panel_height, top_panel_height);
    auto warningWidgetLayout = new QHBoxLayout;
    warningWidgetLayout->addWidget(warningLabel);
    warningWidget->setLayout(warningWidgetLayout);

    QFont titleFont;
    titleFont.setPointSize(DesignerHelper::getSectionFontSize());
    titleFont.setBold(true);

    auto messageLabel = new QLabel();
    messageLabel->setFont(titleFont);
    messageLabel->setText("Some parts of the project were not loaded correctly.");
    messageLabel->setWordWrap(true);

    layout->addWidget(warningWidget);
    layout->addWidget(messageLabel);
    layout->setContentsMargins(0, 0, 0, 0);
    result->setLayout(layout);

    return result;
}

//! Info panel with summary over warnings in different models
QWidget* ProjectLoadWarningDialog::createModelInfoPanel()
{
    auto result = new QWidget(this);
    auto layout = new QHBoxLayout;

    auto line = new QFrame();
    line->setFrameShape(QFrame::VLine);
    line->setFrameShadow(QFrame::Sunken);

    auto gridLayout = new QGridLayout;

    QStringList names = m_messageService->senderList();
    for (int irow = 0; irow < names.size(); ++irow) {
        gridLayout->addWidget(new QLabel(names.at(irow)), irow, 0);
        gridLayout->addWidget(new QLabel("WARNINGS"), irow, 1);
    }

    layout->addWidget(line);
    layout->addLayout(gridLayout);
    layout->addWidget(new QWidget);

    layout->setContentsMargins(0, 0, 0, 0);

    result->setLayout(layout);
    return result;
}

//! Info panel with explanations what had happened and what to do
QWidget* ProjectLoadWarningDialog::createExplanationPanel()
{
    auto result = new QWidget(this);
    auto layout = new QVBoxLayout;

    QFont titleFont;
    titleFont.setPointSize(DesignerHelper::getSectionFontSize());
    titleFont.setBold(true);

    auto whyLabel = new QLabel;
    whyLabel->setFont(titleFont);
    whyLabel->setText("Why did this happen to me?");

    auto explanationLabel = new QLabel;
    explanationLabel->setText(explanationText());
    explanationLabel->setWordWrap(true);

    auto whatLabel = new QLabel;
    whatLabel->setFont(titleFont);
    whatLabel->setText("What to do?");

    auto adviceLabel = new QLabel;
    QString adviceText("Check parameters of your items and re-enter uninitialized values. "
                       "Use detailed log below to get a hint what went wrong. "
                       "After that, save you project and work as normal.");
    adviceLabel->setText(adviceText);
    adviceLabel->setWordWrap(true);

    layout->addWidget(whyLabel);
    layout->addWidget(explanationLabel);
    layout->addWidget(whatLabel);
    layout->addWidget(adviceLabel);

    layout->setContentsMargins(0, 0, 0, 0);

    result->setLayout(layout);
    return result;
}

//! Info panel with table widget containing error messages
QWidget* ProjectLoadWarningDialog::createDetailsPanel()
{
    auto result = new QWidget(this);
    auto layout = new QVBoxLayout;

    QFont titleFont;
    titleFont.setPointSize(DesignerHelper::getSectionFontSize());
    titleFont.setBold(true);

    auto detailsLabel = new QLabel;
    detailsLabel->setFont(titleFont);
    detailsLabel->setText("Details");

    layout->addWidget(detailsLabel);
    layout->addWidget(createTableWidget());

    layout->setContentsMargins(0, 0, 0, 0);

    result->setLayout(layout);
    return result;
}

//! Creates QTableWidget and fills it with error messages
QTableWidget* ProjectLoadWarningDialog::createTableWidget()
{
    auto result = new QTableWidget;
    result->setWordWrap(true);
    //    result->setTextElideMode(Qt::ElideMiddle);

    result->setStyleSheet(
        "QToolTip { color: #ffffff; background-color: #fcfcfc; border: 1px solid black; }");

    result->setRowCount(numberOfTableRows());
    result->setColumnCount(tableHeaderLabels().size());
    result->setHorizontalHeaderLabels(tableHeaderLabels());
    result->verticalHeader()->setVisible(false);
    result->horizontalHeader()->setStretchLastSection(true);

    int rowCount(0);
    for (auto message : m_messageService->messages()) {
        result->setItem(rowCount, 0, createTableItem(message->senderName()));
        result->setItem(rowCount, 1, createTableItem(message->messageType()));
        result->setItem(rowCount, 2, createTableItem(message->messageDescription()));
        ++rowCount;
    }

    result->resizeRowsToContents();

    return result;
}

QLayout* ProjectLoadWarningDialog::buttonLayout()
{
    auto result = new QHBoxLayout;

    auto button = new QPushButton("Close", this);
    button->setAutoDefault(false);
    connect(button, SIGNAL(clicked()), this, SLOT(close()));

    result->addStretch(3);
    result->setContentsMargins(0, 0, 0, 0);
    result->addWidget(button);

    return result;
}

//! Returns number of rows in table with error messages, each row represents an error message
int ProjectLoadWarningDialog::numberOfTableRows() const
{
    return m_messageService->messages().size();
}

//! Returns labels for table header
QStringList ProjectLoadWarningDialog::tableHeaderLabels() const
{
    return QStringList() << "Sender"
                         << "Message"
                         << "Description";
}

QTableWidgetItem* ProjectLoadWarningDialog::createTableItem(const QString& name)
{
    auto result = new QTableWidgetItem(name);
    result->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

    // trick to turn tooltip text to rich text and so have multi-line appearance
    QString toolTip = QString("<font color=black>%1</font>").arg(name);
    result->setToolTip(toolTip);

    return result;
}

//! Returns explanations what went wrong.
QString ProjectLoadWarningDialog::explanationText() const
{
    QString result;
    if (m_projectDocumentVersion != GUIHelpers::getBornAgainVersionString()) {
        result =
            QString("Given project was created using BornAgain version %1 "
                    " which is different from version %2 you are currently using. "
                    "At the moment we provide only limited support for import from older versions.")
                .arg(m_projectDocumentVersion)
                .arg(GUIHelpers::getBornAgainVersionString());
    } else {
        result =
            QString("Given project was created using BornAgain version %1 "
                    "which is the same as the current version of the framework. "
                    "Strangely enough, some parts was not loaded correctly due to format mismatch. "
                    "Please contact developpers.")
                .arg(m_projectDocumentVersion);
    }
    return result;
}
