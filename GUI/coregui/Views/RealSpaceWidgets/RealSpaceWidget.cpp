// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/RealSpaceWidgets/RealSpaceWidget.cpp
//! @brief     Implements class RealSpaceWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/coregui/Views/RealSpaceWidgets/RealSpaceWidget.h"
#include "GUI/coregui/Views/RealSpaceWidgets/RealSpaceActions.h"
#include "GUI/coregui/Views/RealSpaceWidgets/RealSpaceCanvas.h"
#include "GUI/coregui/Views/RealSpaceWidgets/RealSpaceToolBar.h"
#include <QLabel>
#include <QVBoxLayout>

RealSpaceWidget::RealSpaceWidget(SampleModel* sampleModel, QItemSelectionModel* selectionModel,
                                 QWidget* parent)
    : QWidget(parent), m_actions(new RealSpaceActions(this)), m_toolBar(new RealSpaceToolBar),
      m_canvas(new RealSpaceCanvas), m_sampleModel(sampleModel), m_selectionModel(selectionModel)
{
    auto hlayout = new QHBoxLayout;
    hlayout->setMargin(0);
    hlayout->setSpacing(0);
    hlayout->setContentsMargins(0, 0, 0, 0);
    hlayout->addWidget(m_canvas);

    auto* mainLayout = new QVBoxLayout;
    mainLayout->setMargin(0);
    mainLayout->setSpacing(0);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->addWidget(m_toolBar);
    mainLayout->addLayout(hlayout);

    setLayout(mainLayout);

    connect(m_toolBar, &RealSpaceToolBar::defaultViewAction, m_canvas,
            &RealSpaceCanvas::onDefaultViewAction);

    connect(m_toolBar, &RealSpaceToolBar::sideViewAction, m_canvas,
            &RealSpaceCanvas::onSideViewAction);

    connect(m_toolBar, &RealSpaceToolBar::topViewAction, m_canvas,
            &RealSpaceCanvas::onTopViewAction);

    connect(m_toolBar, &RealSpaceToolBar::lockViewAction, m_canvas,
            &RealSpaceCanvas::onLockViewAction);

    connect(m_toolBar, &RealSpaceToolBar::changeLayerSizeAction, m_canvas,
            &RealSpaceCanvas::onChangeLayerSizeAction);

    connect(m_toolBar, &RealSpaceToolBar::savePictureAction, m_canvas,
            &RealSpaceCanvas::onSavePictureAction);
}

void RealSpaceWidget::showEvent(QShowEvent*)
{
    m_canvas->setModel(m_sampleModel, m_selectionModel);
}

void RealSpaceWidget::hideEvent(QHideEvent*)
{
    m_canvas->setModel(nullptr, nullptr);
}
