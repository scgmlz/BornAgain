// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/JobWidgets/JobPropertiesWidget.cpp
//! @brief     Implements class JobPropertiesWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/coregui/Views/JobWidgets/JobPropertiesWidget.h"
#include "GUI/coregui/Models/JobItem.h"
#include "GUI/coregui/Views/PropertyEditor/ComponentEditor.h"
#include "GUI/coregui/mainwindow/mainwindow_constants.h"
#include "GUI/coregui/utils/StyleUtils.h"
#include <QTabBar>
#include <QTabWidget>
#include <QTextEdit>
#include <QVBoxLayout>

JobPropertiesWidget::JobPropertiesWidget(QWidget* parent)
    : SessionItemWidget(parent), m_tabWidget(new QTabWidget),
      m_componentEditor(new ComponentEditor), m_commentsEditor(new QTextEdit), m_block_update(false)
{
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::MinimumExpanding);
    setWindowTitle(Constants::JobPropertiesWidgetName);

    auto mainLayout = new QVBoxLayout;
    mainLayout->setMargin(0);
    mainLayout->setSpacing(0);
    mainLayout->setContentsMargins(0, 0, 0, 0);

    m_tabWidget->setTabPosition(QTabWidget::South);
    m_tabWidget->insertTab(JOB_PROPERTIES, m_componentEditor, "Job Properties");
    m_tabWidget->insertTab(JOB_COMMENTS, m_commentsEditor, "Details");

    mainLayout->addWidget(m_tabWidget);
    setLayout(mainLayout);

    connect(m_commentsEditor, &QTextEdit::textChanged, this, &JobPropertiesWidget::onTextChanged);
}

QSize JobPropertiesWidget::sizeHint() const
{
    return QSize(StyleUtils::PropertyPanelWidth(), StyleUtils::PropertyPanelWidth());
}

QSize JobPropertiesWidget::minimumSizeHint() const
{
    return QSize(StyleUtils::PropertyPanelWidth(), StyleUtils::PropertyPanelWidth());
}

void JobPropertiesWidget::subscribeToItem()
{
    currentItem()->mapper()->setOnPropertyChange(
        [this](const QString& name) {
            if (name == JobItem::P_COMMENTS)
                updateItem();
        },
        this);

    m_componentEditor->setItem(currentItem());

    updateItem();
}

void JobPropertiesWidget::unsubscribeFromItem()
{
    m_componentEditor->setItem(nullptr);
}

void JobPropertiesWidget::contextMenuEvent(QContextMenuEvent*)
{
    // Reimplemented to suppress menu from main window
}

void JobPropertiesWidget::onTextChanged()
{
    m_block_update = true;
    jobItem()->setComments(m_commentsEditor->toPlainText());
    m_block_update = false;
}

void JobPropertiesWidget::updateItem()
{
    if (m_block_update)
        return;

    if (JobItem* item = jobItem()) {
        if (item->getStatus() == "Failed")
            m_tabWidget->tabBar()->setTabTextColor(JOB_COMMENTS, Qt::red);
        else
            m_tabWidget->tabBar()->setTabTextColor(JOB_COMMENTS, Qt::black);

        m_commentsEditor->setText(item->getComments());
    }
}

JobItem* JobPropertiesWidget::jobItem()
{
    return dynamic_cast<JobItem*>(currentItem());
}
