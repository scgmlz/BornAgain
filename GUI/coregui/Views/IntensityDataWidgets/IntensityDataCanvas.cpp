// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/IntensityDataWidgets/IntensityDataCanvas.cpp
//! @brief     Implements class IntensityDataCanvas
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/coregui/Views/IntensityDataWidgets/IntensityDataCanvas.h"
#include "GUI/coregui/Models/ComboProperty.h"
#include "GUI/coregui/Models/IntensityDataItem.h"
#include "GUI/coregui/Views/IntensityDataWidgets/ColorMap.h"
#include "GUI/coregui/Views/IntensityDataWidgets/ColorMapCanvas.h"
#include "GUI/coregui/Views/IntensityDataWidgets/IntensityDataFFTPresenter.h"
#include "GUI/coregui/Views/IntensityDataWidgets/SavePlotAssistant.h"
#include "GUI/coregui/mainwindow/AppSvc.h"
#include "GUI/coregui/mainwindow/projectmanager.h"
#include <QAction>
#include <QMouseEvent>
#include <QSettings>
#include <QVBoxLayout>

namespace
{

QString group_name()
{
    return "IntensityDataCanvas/";
}
QString gradient_setting_name()
{
    return group_name() + IntensityDataItem::P_GRADIENT;
}
QString interpolation_setting_name()
{
    return group_name() + IntensityDataItem::P_IS_INTERPOLATED;
}
} // namespace

IntensityDataCanvas::IntensityDataCanvas(QWidget* parent)
    : SessionItemWidget(parent), m_colorMap(new ColorMapCanvas), m_resetViewAction(nullptr),
      m_savePlotAction(nullptr)
{
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    auto layout = new QVBoxLayout;
    layout->setMargin(0);
    layout->setSpacing(0);
    layout->addWidget(m_colorMap);
    setLayout(layout);

    m_colorMap->setStatusLabelEnabled(true);

    initActions();

    connect(m_colorMap->customPlot(), &QCustomPlot::mousePress, this,
            &IntensityDataCanvas::onMousePress, Qt::UniqueConnection);
}

void IntensityDataCanvas::setItem(SessionItem* intensityItem)
{
    SessionItemWidget::setItem(intensityItem);
    m_colorMap->setItem(intensityDataItem());

    applyPersistentSettings();
}

QSize IntensityDataCanvas::sizeHint() const
{
    return QSize(500, 400);
}

QSize IntensityDataCanvas::minimumSizeHint() const
{
    return QSize(128, 128);
}

QList<QAction*> IntensityDataCanvas::actionList()
{
    return QList<QAction*>() << m_resetViewAction << m_savePlotAction;
}

void IntensityDataCanvas::onResetViewAction()
{
    intensityDataItem()->resetView();
}

void IntensityDataCanvas::onSavePlotAction()
{
    QString dirname = AppSvc::projectManager()->userExportDir();
    SavePlotAssistant saveAssistant;
    saveAssistant.savePlot(dirname, m_colorMap->customPlot(), intensityDataItem()->getOutputData());
}

void IntensityDataCanvas::onMousePress(QMouseEvent* event)
{
    if (event->button() == Qt::RightButton)
        emit customContextMenuRequested(event->globalPos());
}

void IntensityDataCanvas::subscribeToItem()
{
    intensityDataItem()->mapper()->setOnPropertyChange(
        [this](const QString& name) { onPropertyChanged(name); }, this);
}

IntensityDataItem* IntensityDataCanvas::intensityDataItem()
{
    IntensityDataItem* result = dynamic_cast<IntensityDataItem*>(currentItem());
    ASSERT(result);
    return result;
}

void IntensityDataCanvas::initActions()
{
    m_resetViewAction = new QAction(this);
    m_resetViewAction->setText("Center view");
    m_resetViewAction->setIcon(QIcon(":/images/camera-metering-center.svg"));
    m_resetViewAction->setToolTip("Reset view\n"
                                  "x,y,z axes range will be set to default");
    connect(m_resetViewAction, &QAction::triggered, this, &IntensityDataCanvas::onResetViewAction);

    m_savePlotAction = new QAction(this);
    m_savePlotAction->setText("Save");
    m_savePlotAction->setIcon(QIcon(":/images/content-save-outline.svg"));
    m_savePlotAction->setToolTip("Save plot");
    connect(m_savePlotAction, &QAction::triggered, this, &IntensityDataCanvas::onSavePlotAction);
}

//! Reads gradient/ interpolation settings from IntensityDataItem and writes to persistant
//! project settings.

void IntensityDataCanvas::onPropertyChanged(const QString& name)
{
    if (name == IntensityDataItem::P_GRADIENT) {
        QSettings settings;
        settings.setValue(gradient_setting_name(), intensityDataItem()->getGradient());
    } else if (name == IntensityDataItem::P_IS_INTERPOLATED) {
        QSettings settings;
        settings.setValue(interpolation_setting_name(), intensityDataItem()->isInterpolated());
    }
}

//! Apply persistent settings (gradient, interpolation) to IntensityDataItem.

void IntensityDataCanvas::applyPersistentSettings()
{
    QSettings settings;

    if (settings.contains(gradient_setting_name())) {
        ComboProperty combo =
            intensityDataItem()->getItemValue(IntensityDataItem::P_GRADIENT).value<ComboProperty>();
        QString persistentGradient = settings.value(gradient_setting_name()).toString();
        if (combo.getValue() != persistentGradient) {
            combo.setValue(settings.value(gradient_setting_name()).toString());
            intensityDataItem()->setItemValue(IntensityDataItem::P_GRADIENT, combo.variant());
        }
    }

    if (settings.contains(interpolation_setting_name())) {
        bool value = settings.value(interpolation_setting_name()).toBool();
        intensityDataItem()->setItemValue(IntensityDataItem::P_IS_INTERPOLATED, value);
    }
}
