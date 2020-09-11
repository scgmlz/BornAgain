// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/IntensityDataWidgets/IntensityDataPropertyWidget.cpp
//! @brief     Implements class IntensityDataPropertyWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/coregui/Views/IntensityDataWidgets/IntensityDataPropertyWidget.h"
#include "GUI/coregui/Models/IntensityDataItem.h"
#include "GUI/coregui/Models/JobModel.h"
#include "GUI/coregui/Views/PropertyEditor/ComponentEditor.h"
#include "GUI/coregui/utils/StyleUtils.h"
#include <QAction>
#include <QVBoxLayout>

IntensityDataPropertyWidget::IntensityDataPropertyWidget(QWidget* parent)
    : SessionItemWidget(parent), m_togglePanelAction(new QAction(this)),
      m_componentEditor(new ComponentEditor)
{
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
    setWindowTitle(QLatin1String("Intensity Data Properties"));
    setObjectName(QLatin1String("Intensity Data Properties"));

    auto mainLayout = new QVBoxLayout;
    mainLayout->setMargin(0);
    mainLayout->setSpacing(0);
    mainLayout->addWidget(m_componentEditor);
    setLayout(mainLayout);

    m_togglePanelAction->setText("Properties");
    m_togglePanelAction->setIcon(QIcon(":/images/dock-right.svg"));
    m_togglePanelAction->setToolTip("Toggle property panel");
    connect(m_togglePanelAction, &QAction::triggered, this,
            &IntensityDataPropertyWidget::onTogglePanelAction);
}

QSize IntensityDataPropertyWidget::sizeHint() const
{
    return QSize(StyleUtils::PropertyPanelWidth() * 1.2, StyleUtils::PropertyPanelWidth() * 2);
}

QSize IntensityDataPropertyWidget::minimumSizeHint() const
{
    return QSize(StyleUtils::PropertyPanelWidth() * 1.2, StyleUtils::PropertyPanelWidth());
}

QList<QAction*> IntensityDataPropertyWidget::actionList()
{
    return QList<QAction*>() << m_togglePanelAction;
}

void IntensityDataPropertyWidget::onTogglePanelAction()
{
    setVisible(!isVisible());
}

void IntensityDataPropertyWidget::subscribeToItem()
{
    m_componentEditor->setItem(currentItem());
}

void IntensityDataPropertyWidget::unsubscribeFromItem()
{
    m_componentEditor->setItem(nullptr);
}

void IntensityDataPropertyWidget::contextMenuEvent(QContextMenuEvent*)
{
    // Reimplemented to suppress menu from main window
}
