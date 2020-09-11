// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/IntensityDataWidgets/ColorMap.h
//! @brief     Defines class ColorMap
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_VIEWS_INTENSITYDATAWIDGETS_COLORMAP_H
#define BORNAGAIN_GUI_COREGUI_VIEWS_INTENSITYDATAWIDGETS_COLORMAP_H

#include "GUI/coregui/Views/IntensityDataWidgets/ScientificPlot.h"
#include "qcustomplot.h"
#include <QMap>
#include <QPoint>
#include <memory>

class IntensityDataItem;
class QCustomPlot;
class QCPColorMap;
class QCPColorScale;
class UpdateTimer;
class ScientificPlotEvent;

//! The ColorMap class presents 2D intensity data from IntensityDataItem as color map.

//! Provides a minimal functionality for data plotting and axes interaction. Should be a component
//! for more complicated plotting widgets. This is a replacement for ColorMapPlot.

class BA_CORE_API_ ColorMap : public ScientificPlot
{
    Q_OBJECT

public:
    explicit ColorMap(QWidget* parent = nullptr);

    QSize sizeHint() const override { return QSize(500, 400); }
    QSize minimumSizeHint() const override { return QSize(128, 128); }

    QCustomPlot* customPlot() override { return m_customPlot; }
    const QCustomPlot* customPlot() const override { return m_customPlot; }
    QCPColorScale* colorScale() { return m_colorScale; }

    //! returns rectangle representing current axes zoom state in widget coordinates
    QRectF viewportRectangleInWidgetCoordinates();

    //! Returns PlotEventInfo corresponding to given axes coordinates.
    PlotEventInfo eventInfo(double xpos, double ypos) const override;

signals:
    void marginsChanged(double left, double right);

public slots:
    void setLogz(bool logz);
    void resetView();

private slots:
    void onIntensityModified();
    void onPropertyChanged(const QString& property_name);
    void onAxisPropertyChanged(const QString& axisName, const QString& propertyName);
    void onDataRangeChanged(QCPRange newRange);
    void onXaxisRangeChanged(QCPRange newRange);
    void onYaxisRangeChanged(QCPRange newRange);
    void replot();
    void onTimeToReplot();
    void marginsChangedNotify();

protected:
    void subscribeToItem() override;
    void unsubscribeFromItem() override;

private:
    void initColorMap();

    void setConnected(bool isConnected);
    void setAxesRangeConnected(bool isConnected);
    void setDataRangeConnected(bool isConnected);
    void setUpdateTimerConnected(bool isConnected);

    void setFixedColorMapMargins();

    void setColorMapFromItem(IntensityDataItem* intensityItem);
    void setAxesRangeFromItem(IntensityDataItem* item);
    void setAxesZoomFromItem(IntensityDataItem* item);
    void setAxesLabelsFromItem(IntensityDataItem* item);
    void setDataFromItem(IntensityDataItem* item);
    void setColorScaleAppearanceFromItem(IntensityDataItem* item);
    void setDataRangeFromItem(IntensityDataItem* item);

    void setColorScaleVisible(bool visibility_flag);

    IntensityDataItem* intensityItem();
    const IntensityDataItem* intensityItem() const;

    QCustomPlot* m_customPlot;
    QCPColorMap* m_colorMap;
    QCPColorScale* m_colorScale;
    UpdateTimer* m_updateTimer;
    QCPLayoutGrid* m_colorBarLayout;

    bool m_block_update;
};

#endif // BORNAGAIN_GUI_COREGUI_VIEWS_INTENSITYDATAWIDGETS_COLORMAP_H
