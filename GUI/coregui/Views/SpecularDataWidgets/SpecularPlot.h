// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/SpecularDataWidgets/SpecularPlot.h
//! @brief     Defines class SpecularPlot
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_VIEWS_SPECULARDATAWIDGETS_SPECULARPLOT_H
#define BORNAGAIN_GUI_COREGUI_VIEWS_SPECULARDATAWIDGETS_SPECULARPLOT_H

#include "GUI/coregui/Views/IntensityDataWidgets/ScientificPlot.h"
#include "qcustomplot.h"
#include <memory>

class BasicAxisItem;
class SpecularDataItem;
class SpecularPlotEvent;
class UpdateTimer;

//! The SpecularPlot class presents 1D intensity data from SpecularDataItem.

//! Provides minimal functionality for data plotting and axes interaction. Should be a component
//! for more complicated plotting widgets. Corresponds to ColorMap for 2D intensity data.

class BA_CORE_API_ SpecularPlot : public ScientificPlot
{
    Q_OBJECT

public:
    explicit SpecularPlot(QWidget* parent = nullptr);

    QSize sizeHint() const override { return QSize(500, 400); }
    QSize minimumSizeHint() const override { return QSize(128, 128); }

    //! Returns PlotEventInfo corresponding to given axes coordinates.
    PlotEventInfo eventInfo(double xpos, double ypos) const override;

    QCustomPlot* customPlot() override { return m_custom_plot; }
    const QCustomPlot* customPlot() const override { return m_custom_plot; }

    //! sets logarithmic scale
    void setLog(bool log);

    //! reset all axes min,max to initial value
    void resetView();

private slots:
    //! updates plot depending on  IntensityDataItem properties
    void onPropertyChanged(const QString& property_name);

    //! Propagate xmin, xmax back to IntensityDataItem
    void onXaxisRangeChanged(QCPRange newRange);

    //! Propagate ymin, ymax back to IntensityDataItem
    void onYaxisRangeChanged(QCPRange newRange);

    //! Replots SpecularPlot.
    void onTimeToReplot();

protected:
    void subscribeToItem() override;
    void unsubscribeFromItem() override;

private:
    //! creates and initializes the color map
    void initPlot();

    void setConnected(bool isConnected);

    //! Connects/disconnects signals related to SpecularPlot's X,Y axes rectangle change.
    void setAxesRangeConnected(bool isConnected);

    void setUpdateTimerConnected(bool isConnected);

    //! Sets initial state of SpecularPlot to match given intensity item.
    void setPlotFromItem(SpecularDataItem* intensityItem);

    //! Sets (xmin,xmax) and (ymin,ymax) of SpecularPlot from specular item.
    //! Also sets logarithmic scale on y-axis if necessary.
    void setAxesRangeFromItem(SpecularDataItem* item);

    //! Sets X,Y axes labels from item
    void setAxesLabelsFromItem(SpecularDataItem* item);

    //! Sets label to axis
    void setLabel(const BasicAxisItem* item, QCPAxis* axis, QString label);

    //! Sets the intensity values to SpecularPlot.
    void setDataFromItem(SpecularDataItem* item);

    SpecularDataItem* specularItem();
    const SpecularDataItem* specularItem() const;

    void modifyAxesProperties(const QString& axisName, const QString& propertyName);

    //! Schedule replot for later execution by onTimeReplot() slot.
    void replot();

    QCustomPlot* m_custom_plot;
    UpdateTimer* m_update_timer;

    bool m_block_update;
};

#endif // BORNAGAIN_GUI_COREGUI_VIEWS_SPECULARDATAWIDGETS_SPECULARPLOT_H
