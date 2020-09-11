// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/IntensityDataWidgets/IntensityDataWidget.cpp
//! @brief     Implements class IntensityDataWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/coregui/Views/IntensityDataWidgets/IntensityDataWidget.h"
#include "GUI/coregui/Models/DataItemUtils.h"
#include "GUI/coregui/Models/IntensityDataItem.h"
#include "GUI/coregui/Models/JobItem.h"
#include "GUI/coregui/Views/IntensityDataWidgets/IntensityDataCanvas.h"
#include "GUI/coregui/Views/IntensityDataWidgets/IntensityDataFFTPresenter.h"
#include "GUI/coregui/Views/IntensityDataWidgets/IntensityDataPropertyWidget.h"
#include <QBoxLayout>
#include <QMenu>

IntensityDataWidget::IntensityDataWidget(QWidget* parent)
    : SessionItemWidget(parent), m_intensityCanvas(new IntensityDataCanvas),
      m_propertyWidget(new IntensityDataPropertyWidget),
      m_fftPresenter(new IntensityDataFFTPresenter(this))
{
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    auto hlayout = new QHBoxLayout;
    hlayout->setMargin(0);
    hlayout->setSpacing(0);
    hlayout->addWidget(m_intensityCanvas);
    hlayout->addWidget(m_propertyWidget);

    auto mainLayout = new QVBoxLayout;
    mainLayout->setMargin(0);
    mainLayout->setSpacing(0);
    mainLayout->addLayout(hlayout);

    setLayout(mainLayout);

    connect(m_intensityCanvas, &IntensityDataCanvas::customContextMenuRequested, this,
            &IntensityDataWidget::onContextMenuRequest);

    connect(m_fftPresenter, &IntensityDataFFTPresenter::fftActionRequest, this,
            &IntensityDataWidget::onFFTAction);

    m_propertyWidget->setVisible(false);
}

void IntensityDataWidget::setItem(SessionItem* jobItem)
{
    SessionItemWidget::setItem(jobItem);
    m_intensityCanvas->setItem(intensityDataItem());
    m_propertyWidget->setItem(intensityDataItem());
    m_fftPresenter->reset();
}

QList<QAction*> IntensityDataWidget::actionList()
{
    return m_intensityCanvas->actionList() + m_fftPresenter->actionList()
           + m_propertyWidget->actionList();
}

void IntensityDataWidget::onContextMenuRequest(const QPoint& point)
{
    QMenu menu;
    for (auto action : actionList())
        menu.addAction(action);
    menu.exec(point);
}

void IntensityDataWidget::onFFTAction()
{
    if (!intensityDataItem() || !intensityDataItem()->getOutputData())
        return;

    if (m_fftPresenter->inFFTMode()) {
        auto fftItem = m_fftPresenter->fftItem(intensityDataItem());
        m_intensityCanvas->setItem(fftItem);
        m_propertyWidget->setItem(fftItem);
    } else {
        // returning ColorMap to non-fft presentation
        m_intensityCanvas->setItem(intensityDataItem());
        m_propertyWidget->setItem(intensityDataItem());
    }
}

IntensityDataItem* IntensityDataWidget::intensityDataItem()
{
    return DataItemUtils::intensityDataItem(currentItem());
}
