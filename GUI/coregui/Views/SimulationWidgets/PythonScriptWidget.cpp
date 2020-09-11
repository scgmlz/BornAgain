// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/SimulationWidgets/PythonScriptWidget.cpp
//! @brief     Implements class PythonScriptWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/coregui/Views/SimulationWidgets/PythonScriptWidget.h"
#include "Core/Export/ExportToPython.h"
#include "Core/Simulation/GISASSimulation.h"
#include "GUI/coregui/Models/DomainSimulationBuilder.h"
#include "GUI/coregui/Models/InstrumentItems.h"
#include "GUI/coregui/Views/InfoWidgets/PythonSyntaxHighlighter.h"
#include "GUI/coregui/Views/InfoWidgets/WarningSign.h"
#include "GUI/coregui/Views/SampleDesigner/DesignerHelper.h"
#include "GUI/coregui/utils/StyleUtils.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QPushButton>
#include <QStandardPaths>
#include <QStyle>
#include <QTextEdit>
#include <QTextStream>
#include <QToolBar>
#include <QVBoxLayout>
#include <memory>

PythonScriptWidget::PythonScriptWidget(QWidget* parent)
    : QDialog(parent), m_toolBar(nullptr), m_textEdit(new QTextEdit),
      m_warningSign(new WarningSign(m_textEdit))
{
    setWindowTitle("Python Script View");
    setMinimumSize(128, 128);
    resize(512, 400);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    m_toolBar = new QToolBar;
    m_toolBar->setFixedHeight(28);
    m_toolBar->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    const int size = style()->pixelMetric(QStyle::PM_SmallIconSize);
    m_toolBar->setIconSize(QSize(size, size));
    m_toolBar->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);

    QPushButton* exportToFileButton = new QPushButton;
    exportToFileButton->setText("Save to file");
    exportToFileButton->setToolTip("Opens dialog to save given script into the file");
    connect(exportToFileButton, SIGNAL(clicked()), this, SLOT(onExportToFileButton()));
    exportToFileButton->setAutoDefault(false);
    m_toolBar->addWidget(exportToFileButton);

    m_textEdit->setReadOnly(true);
    QFont textFont("Monospace");
    m_textEdit->setFont(textFont);
    m_textEdit->setFontPointSize(DesignerHelper::getPythonEditorFontSize());
    m_textEdit->setLineWrapMode(QTextEdit::NoWrap);
    PythonSyntaxHighlighter* highlighter = new PythonSyntaxHighlighter(m_textEdit->document());
    Q_UNUSED(highlighter);

    QVBoxLayout* mainLayout = new QVBoxLayout;
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setMargin(0);
    mainLayout->setSpacing(0);
    mainLayout->addWidget(m_toolBar);
    mainLayout->addWidget(m_textEdit);

    setLayout(mainLayout);

    setAttribute(Qt::WA_DeleteOnClose, true);
    StyleUtils::setResizable(this);
}

void PythonScriptWidget::generatePythonScript(const MultiLayerItem* sampleItem,
                                              const InstrumentItem* instrumentItem,
                                              const SimulationOptionsItem* optionItem,
                                              const QString& outputDir)
{
    m_outputDir = outputDir;
    m_warningSign->clear();

    try {
        const auto simulation =
            DomainSimulationBuilder::createSimulation(sampleItem, instrumentItem, optionItem);

        QString code = QString::fromStdString(ExportToPython::generateSimulationCode(*simulation));
        m_textEdit->clear();
        m_textEdit->setText(code);

    } catch (const std::exception& ex) {
        QString message =
            QString(
                "Generation of Python Script failed. Code is not complete.\n\n"
                "It can happen if sample requires further assembling or some of sample parameters "
                "are not valid. See details below.\n\n%1")
                .arg(QString::fromStdString(ex.what()));

        m_warningSign->setWarningMessage(message);
    }
}

void PythonScriptWidget::onExportToFileButton()
{
    QString dirname(m_outputDir);
    if (dirname.isEmpty())
        dirname = QStandardPaths::writableLocation(QStandardPaths::HomeLocation);

    QString filters("Python scripts (*.py)");
    QString defaultFilter("Python scripts (*.py)");
    QString defaultName = dirname + "/untitled";

    QString fileName =
        QFileDialog::getSaveFileName(nullptr, "Save file", defaultName, filters, &defaultFilter);

    if (fileName.isEmpty())
        return;

    if (!fileName.endsWith(".py"))
        fileName += ".py";

    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly)) {
        QMessageBox warning_dialog(this);
        warning_dialog.setIcon(QMessageBox::Warning);
        warning_dialog.setText("File could not be opened for writing!");
        warning_dialog.exec();
        return;
    }
    QTextStream out(&file);
    out << m_textEdit->toPlainText();
    file.close();
    raise();
}
