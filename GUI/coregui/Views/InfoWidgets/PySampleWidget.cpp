// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/InfoWidgets/PySampleWidget.cpp
//! @brief     Implements class PySampleWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/coregui/Views/InfoWidgets/PySampleWidget.h"
#include "Core/Export/ExportToPython.h"
#include "Core/Multilayer/MultiLayer.h"
#include "GUI/coregui/Models/DomainObjectBuilder.h"
#include "GUI/coregui/Models/MultiLayerItem.h"
#include "GUI/coregui/Models/SampleModel.h"
#include "GUI/coregui/Models/SessionItemUtils.h"
#include "GUI/coregui/Views/CommonWidgets/UpdateTimer.h"
#include "GUI/coregui/Views/InfoWidgets/PythonSyntaxHighlighter.h"
#include "GUI/coregui/Views/InfoWidgets/WarningSign.h"
#include "GUI/coregui/Views/SampleDesigner/DesignerHelper.h"
#include <QScrollBar>
#include <QTextEdit>
#include <QVBoxLayout>

namespace
{
const int accumulate_updates_during_msec = 20.;
}

PySampleWidget::PySampleWidget(QWidget* parent)
    : QWidget(parent), m_textEdit(new QTextEdit), m_sampleModel(nullptr),
      m_instrumentModel(nullptr), m_highlighter(nullptr),
      m_updateTimer(new UpdateTimer(accumulate_updates_during_msec, this)),
      m_warningSign(new WarningSign(m_textEdit))
{
    m_textEdit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    auto mainLayout = new QVBoxLayout;
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->addWidget(m_textEdit);

    setLayout(mainLayout);

    m_textEdit->setReadOnly(true);
    QFont textFont("Monospace");
    m_textEdit->setFont(textFont);
    m_textEdit->setFontPointSize(DesignerHelper::getPythonEditorFontSize());
}

void PySampleWidget::setSampleModel(SampleModel* sampleModel)
{
    if (sampleModel != m_sampleModel) {
        if (m_sampleModel)
            setEditorConnected(false);
        m_sampleModel = sampleModel;
    }
}

void PySampleWidget::setInstrumentModel(InstrumentModel* instrumentModel)
{
    m_instrumentModel = instrumentModel;
}

void PySampleWidget::onModifiedRow(const QModelIndex&, int, int)
{
    m_updateTimer->scheduleUpdate();
}

void PySampleWidget::onDataChanged(const QModelIndex& index, const QModelIndex&)
{
    auto item = m_sampleModel->itemForIndex(index);
    if (!item)
        return;

    if (!SessionItemUtils::IsPositionRelated(*item))
        m_updateTimer->scheduleUpdate();
}

//! Update the editor with the script content
void PySampleWidget::updateEditor()
{
    if (!m_highlighter) {
        m_highlighter = new PythonSyntaxHighlighter(m_textEdit->document());
        m_textEdit->setLineWrapMode(QTextEdit::NoWrap);
    }

    const int old_scrollbar_value = m_textEdit->verticalScrollBar()->value();

    QString code_snippet = generateCodeSnippet();

    if (!code_snippet.isEmpty())
        m_textEdit->setText(code_snippet);
    else
        m_textEdit->clear();

    m_textEdit->verticalScrollBar()->setValue(old_scrollbar_value);
}

void PySampleWidget::setEditorConnected(bool isConnected)
{
    if (isConnected) {
        connect(m_sampleModel, &SampleModel::rowsInserted, this, &PySampleWidget::onModifiedRow,
                Qt::UniqueConnection);
        connect(m_sampleModel, &SampleModel::rowsRemoved, this, &PySampleWidget::onModifiedRow,
                Qt::UniqueConnection);
        connect(m_sampleModel, &SampleModel::dataChanged, this, &PySampleWidget::onDataChanged,
                Qt::UniqueConnection);
        connect(m_sampleModel, &SampleModel::modelReset, this, &PySampleWidget::updateEditor,
                Qt::UniqueConnection);

        connect(m_updateTimer, &UpdateTimer::timeToUpdate, this, &PySampleWidget::updateEditor,
                Qt::UniqueConnection);

        m_updateTimer->scheduleUpdate();

    } else {
        disconnect(m_sampleModel, &SampleModel::rowsInserted, this, &PySampleWidget::onModifiedRow);
        disconnect(m_sampleModel, &SampleModel::rowsRemoved, this, &PySampleWidget::onModifiedRow);
        disconnect(m_sampleModel, &SampleModel::dataChanged, this, &PySampleWidget::onDataChanged);
        disconnect(m_sampleModel, &SampleModel::modelReset, this, &PySampleWidget::updateEditor);

        disconnect(m_updateTimer, &UpdateTimer::timeToUpdate, this, &PySampleWidget::updateEditor);
    }
}

void PySampleWidget::showEvent(QShowEvent*)
{
    setEditorConnected(isVisible());
}

void PySampleWidget::hideEvent(QHideEvent*)
{
    setEditorConnected(isVisible());
}

//! generates string representing code snippet for all multi layers in the model

QString PySampleWidget::generateCodeSnippet()
{
    m_warningSign->clear();
    QString result;

    for (const MultiLayerItem* sampleItem : m_sampleModel->topItems<MultiLayerItem>()) {
        try {
            auto multilayer = DomainObjectBuilder::buildMultiLayer(*sampleItem);
            if (!result.isEmpty())
                result.append("\n");
            result.append(QString::fromStdString(ExportToPython::generateSampleCode(*multilayer)));
        } catch (const std::exception& ex) {
            QString message =
                QString("Generation of Python Script failed. Code is not complete.\n\n"
                        "It can happen if sample requires further assembling or some of sample "
                        "parameters are not valid. See details below.\n\n%1")
                    .arg(QString::fromStdString(ex.what()));

            m_warningSign->setWarningMessage(message);
        }
    }

    return result;
}
