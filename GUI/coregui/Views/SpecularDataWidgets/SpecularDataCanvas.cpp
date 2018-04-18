// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/SpecularDataWidgets/SpecularDataCanvas.cpp
//! @brief     Implements class SpecularDataCanvas
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "AppSvc.h"
#include "projectmanager.h"
#include "SavePlotAssistant.h"
#include "SpecularDataCanvas.h"
#include "SpecularDataItem.h"
#include "SpecularPlotCanvas.h"
#include "plot_constants.h"
#include "qcustomplot.h"

SpecularDataCanvas::SpecularDataCanvas(QWidget* parent)
    : SessionItemWidget(parent)
    , m_plot_canvas(new SpecularPlotCanvas)
    , m_reset_view_action(nullptr)
    , m_save_plot_action(nullptr)

{
    QVBoxLayout* vlayout = new QVBoxLayout(this);
    vlayout->setMargin(0);
    vlayout->setSpacing(0);
    vlayout->setContentsMargins(0, 0, 0, 0);
    vlayout->addWidget(m_plot_canvas);
    setLayout(vlayout);
    setStyleSheet("background-color:white;");

    initActions();

    m_plot_canvas->setStatusLabelEnabled(true);

    connect(m_plot_canvas->customPlot(), &QCustomPlot::mousePress, this,
            &SpecularDataCanvas::onMousePress, Qt::UniqueConnection);
}

void SpecularDataCanvas::setItem(SessionItem* intensityItem)
{
    SessionItemWidget::setItem(intensityItem);
    m_plot_canvas->setItem(intensityItem);
}

QSize SpecularDataCanvas::sizeHint() const { return QSize(500, 400); }

QSize SpecularDataCanvas::minimumSizeHint() const { return QSize(128, 128); }

QList<QAction*> SpecularDataCanvas::actionList()
{
    return QList<QAction*>() << m_reset_view_action << m_save_plot_action;
}

void SpecularDataCanvas::onResetViewAction() { specularDataItem()->resetView(); }

void SpecularDataCanvas::onSavePlotAction()
{
    QString dirname = AppSvc::projectManager()->userExportDir();
    SavePlotAssistant saveAssistant;
    saveAssistant.savePlot(dirname, m_plot_canvas->customPlot(),
                           specularDataItem()->getOutputData());
}

void SpecularDataCanvas::onMousePress(QMouseEvent* event)
{
    if (event->button() == Qt::RightButton)
        emit customContextMenuRequested(event->globalPos());
}

SpecularDataItem* SpecularDataCanvas::specularDataItem()
{
    SpecularDataItem* result = dynamic_cast<SpecularDataItem*>(currentItem());
    Q_ASSERT(result);
    return result;
}

// TODO: try to reuse IntensityDataCanvas::initActions somehow
void SpecularDataCanvas::initActions()
{
    m_reset_view_action = new QAction(this);
    m_reset_view_action->setText("Reset");
    m_reset_view_action->setIcon(QIcon(":/images/toolbar16light_refresh.svg"));
    m_reset_view_action->setToolTip("Reset view\n"
                                    "x,y axes range will be set to default");
    connect(m_reset_view_action, &QAction::triggered, this, &SpecularDataCanvas::onResetViewAction);

    m_save_plot_action = new QAction(this);
    m_save_plot_action->setText("Save");
    m_save_plot_action->setIcon(QIcon(":/images/toolbar16light_save.svg"));
    m_save_plot_action->setToolTip("Save plot");
    connect(m_save_plot_action, &QAction::triggered, this, &SpecularDataCanvas::onSavePlotAction);
}
