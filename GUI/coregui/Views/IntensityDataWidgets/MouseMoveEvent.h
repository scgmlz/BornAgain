// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/IntensityDataWidgets/MouseMoveEvent.h
//! @brief     Defines class MouseMoveEvent
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef MOUSEMOVEEVENT_H
#define MOUSEMOVEEVENT_H

#include <memory>
#include <QObject>
#include "WinDllMacros.h"

class DescriptedPlot;
class IPlotDescriptor;
class QMouseEvent;
class QCustomPlot;

//! Helps DescriptedPlot to handle mouse events. Particularly, it constructs a valid
//! status string. Can be extended to play a role of event filter.

class BA_CORE_API_ MouseMoveEvent : public QObject
{
    Q_OBJECT

public:
    explicit MouseMoveEvent(DescriptedPlot* descriptedPlot);

    void setMouseTrackingEnabled(bool enable);

signals:
    void enteringPlot();
    void leavingPlot();
    void positionChanged(double x, double y);

public slots:
    void onCustomMouseMove(QMouseEvent* event);

private:
    DescriptedPlot* descriptedPlot();
    const DescriptedPlot* descriptedPlot() const;
    QCustomPlot* customPlot();
    std::unique_ptr<IPlotDescriptor> currentPlotDescriptor(QMouseEvent* event) const;

    DescriptedPlot* m_plot;
    std::unique_ptr<IPlotDescriptor> m_prevPos;
};

#endif // MOUSEMOVEEVENT_H
