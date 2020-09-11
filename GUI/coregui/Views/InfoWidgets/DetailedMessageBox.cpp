// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/InfoWidgets/DetailedMessageBox.cpp
//! @brief     Implements class DetailedMessageBox
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/coregui/Views/InfoWidgets/DetailedMessageBox.h"
#include "GUI/coregui/Views/SampleDesigner/DesignerHelper.h"
#include <QApplication>
#include <QLabel>
#include <QMessageBox>
#include <QPushButton>
#include <QStyle>
#include <QTextEdit>
#include <QVBoxLayout>

namespace
{
const QSize default_dialog_size(512, 300);
}

DetailedMessageBox::DetailedMessageBox(QWidget* parent, const QString& title, const QString& text,
                                       const QString& details)
    : QDialog(parent), m_topLabel(new QLabel), m_textEdit(new QTextEdit)
{
    setWindowTitle(title);
    m_topLabel->setText(text);
    m_textEdit->setText(details);
    m_textEdit->setReadOnly(true);
    m_textEdit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    setWindowFlags(Qt::Dialog);

    resize(default_dialog_size);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    QColor bgColor(240, 240, 240, 255);
    QPalette palette;
    palette.setColor(QPalette::Background, bgColor);
    setAutoFillBackground(true);
    setPalette(palette);

    auto topLayout = new QHBoxLayout;
    topLayout->addLayout(createLogoLayout());
    topLayout->addLayout(createInfoLayout());
    topLayout->addStretch(1);

    auto mainLayout = new QVBoxLayout;
    mainLayout->addLayout(topLayout);
    mainLayout->addWidget(m_textEdit);
    mainLayout->addLayout(createButtonLayout());

    setLayout(mainLayout);

    setSizeGripEnabled(true);
}

void DetailedMessageBox::setText(const QString& text)
{
    m_topLabel->setText(text);
}

void DetailedMessageBox::setDetailedText(const QString& text)
{
    m_textEdit->setText(text);
}

//! Returns layout with icon for left part of the widget.

QBoxLayout* DetailedMessageBox::createLogoLayout()
{
    auto result = new QVBoxLayout;

    QIcon icon = QApplication::style()->standardIcon(QStyle::SP_MessageBoxWarning);

    auto label = new QLabel;
    label->setPixmap(icon.pixmap(128));

    result->addWidget(label);
    result->setContentsMargins(5, 5, 5, 5);

    return result;
}

//! Create right layout with text and QComboBox selection.

QBoxLayout* DetailedMessageBox::createInfoLayout()
{
    m_topLabel->setWordWrap(true);

    auto result = new QVBoxLayout;
    result->addWidget(m_topLabel);
    result->setContentsMargins(5, 5, 5, 5);
    return result;
}

//! Creates button layout with buttons.

QBoxLayout* DetailedMessageBox::createButtonLayout()
{
    auto result = new QHBoxLayout;

    auto okButton = new QPushButton("Ok");
    connect(okButton, SIGNAL(clicked()), this, SLOT(reject()));

    result->addStretch(1);
    result->addWidget(okButton);

    return result;
}
