// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/InstrumentWidgets/InstrumentEditorWidget.cpp
//! @brief     Implements class InstrumentEditorWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/coregui/Views/InstrumentWidgets/InstrumentEditorWidget.h"
#include "GUI/coregui/Models/DetectorItems.h"
#include "GUI/coregui/Models/InstrumentItems.h"
#include "GUI/coregui/Views/CommonWidgets/AdjustingScrollArea.h"
#include "GUI/coregui/Views/InstrumentWidgets/InstrumentPresenter.h"
#include <QBoxLayout>
#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>

InstrumentEditorWidget::InstrumentEditorWidget(QWidget* parent)
    : QWidget(parent), m_nameLineEdit(new QLineEdit),
      m_instrumentPresenter(new InstrumentPresenter), m_currentItem(nullptr), m_block_signals(false)
{
    setMinimumSize(400, 400);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    auto mainLayout = new QVBoxLayout;
    mainLayout->setContentsMargins(0, 20, 0, 20);
    mainLayout->addLayout(createTopLayout());

    auto scrollArea = new AdjustingScrollArea;
    scrollArea->setWidget(m_instrumentPresenter);
    mainLayout->addWidget(scrollArea, 1);
    mainLayout->addStretch();

    setLayout(mainLayout);

    connect(m_nameLineEdit, &QLineEdit::textChanged, this,
            &InstrumentEditorWidget::onChangedEditor);
}

QSize InstrumentEditorWidget::sizeHint() const
{
    return QSize(600, 600);
}

void InstrumentEditorWidget::setItem(SessionItem* instrument)
{
    m_currentItem = instrument;
    updateWidgets();

    m_instrumentPresenter->setItem(instrument);
}

void InstrumentEditorWidget::onChangedEditor(const QString&)
{
    if (m_block_signals)
        return;

    if (m_currentItem)
        m_currentItem->setItemName(m_nameLineEdit->text());
}

//! top block with instrument name

QLayout* InstrumentEditorWidget::createTopLayout()
{
    auto result = new QHBoxLayout;

    m_nameLineEdit->setMinimumWidth(200);

    result->addSpacing(17);
    result->addWidget(new QLabel("Instrument name"));
    result->addWidget(m_nameLineEdit);
    result->addStretch(1);

    return result;
}

void InstrumentEditorWidget::updateWidgets()
{
    m_block_signals = true;

    if (m_currentItem) {
        m_nameLineEdit->setEnabled(true);
        m_nameLineEdit->setText(m_currentItem->itemName());
    } else {
        m_nameLineEdit->setText(QString());
        m_nameLineEdit->setEnabled(false);
    }

    m_block_signals = false;
}
