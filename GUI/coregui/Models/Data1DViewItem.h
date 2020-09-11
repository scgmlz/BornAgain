// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/Data1DViewItem.h
//! @brief     Defines class Data1DViewItem
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_MODELS_DATA1DVIEWITEM_H
#define BORNAGAIN_GUI_COREGUI_MODELS_DATA1DVIEWITEM_H

#include "GUI/coregui/Models/SessionItem.h"

class AmplitudeAxisItem;
class BasicAxisItem;
class DataPropertyContainer;
class Data1DProperties;
class DataItem;
class JobItem;
template <class T> class OutputData;

//! View model for 1D DataItem. Can represent several items
//! at once. In current implementation the first of carried
//! items determines axes' limits.

class BA_CORE_API_ Data1DViewItem : public SessionItem
{
public:
    static const QString P_TITLE;
    static const QString P_XAXIS;
    static const QString P_YAXIS;
    static const QString P_AXES_UNITS;
    static const QString T_DATA_PROPERTIES;

    Data1DViewItem();

    //! Number of bins in data
    int getNbins() const;

    //! returns lower and upper zoom ranges of x-axis
    double getLowerX() const;
    double getUpperX() const;

    //! returns lower and upper zoom ranges of y-axis
    double getLowerY() const;
    double getUpperY() const;

    bool isLog() const;
    QString getXaxisTitle() const;
    QString getYaxisTitle() const;

    const BasicAxisItem* xAxisItem() const;
    BasicAxisItem* xAxisItem();
    const AmplitudeAxisItem* yAxisItem() const;

    void resetView();

    void setXaxisTitle(QString xtitle);
    void setYaxisTitle(QString ytitle);
    void setAxesRangeToData();

    //! Returns data view to default state (no dimensional units, default axes' names)
    void resetToDefault();

    //! Returns point data for drawing
    QPair<QVector<double>, QVector<double>> graphData(Data1DProperties* property_item);

    //! Sets job item (for unit conversion) if DataItemView
    //! is dynamically created outside of JobModel
    void setJobItem(JobItem* job_item) { m_job_item = job_item; }

    //! Returns either parenting JobItem or
    //! job item set with DataItem1DView::setJobItem.
    JobItem* jobItem();

    void setLowerX(double xmin);
    void setUpperX(double xmax);
    void setLowerY(double ymin);
    void setUpperY(double ymax);
    void setLog(bool log_flag);

    DataPropertyContainer* propertyContainerItem();

private:
    QPair<double, double> dataRange(const OutputData<double>* data) const;

    JobItem* m_job_item;
};

#endif // BORNAGAIN_GUI_COREGUI_MODELS_DATA1DVIEWITEM_H
