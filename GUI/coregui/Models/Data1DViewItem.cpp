// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/Data1DViewItem.cpp
//! @brief     Implements class Data1DViewItem
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/coregui/Models/Data1DViewItem.h"
#include "GUI/coregui/Models/AxesItems.h"
#include "GUI/coregui/Models/ComboProperty.h"
#include "GUI/coregui/Models/DataItem.h"
#include "GUI/coregui/Models/DataProperties.h"
#include "GUI/coregui/Models/DataPropertyContainer.h"
#include "GUI/coregui/Models/DataViewUtils.h"
#include "GUI/coregui/Models/JobItem.h"
#include "GUI/coregui/utils/GUIHelpers.h"

namespace
{
const QString x_axis_default_name = "X [nbins]";
const QString y_axis_default_name = "Signal [a.u.]";

const double default_min = 0.0;
const double default_max = 1.0;
} // namespace

const QString Data1DViewItem::P_TITLE = "Title";
const QString Data1DViewItem::P_XAXIS = "x-axis";
const QString Data1DViewItem::P_YAXIS = "y-axis";
const QString Data1DViewItem::P_AXES_UNITS = "Axes Units";
const QString Data1DViewItem::T_DATA_PROPERTIES = "Data property container";

Data1DViewItem::Data1DViewItem() : SessionItem("Data1DViewItem"), m_job_item(nullptr)
{
    addProperty(P_TITLE, QString())->setVisible(false);

    SessionItem* item = addGroupProperty(P_XAXIS, "BasicAxis");
    item->getItem(BasicAxisItem::P_NBINS)->setVisible(false);

    item = addGroupProperty(P_YAXIS, "AmplitudeAxis");
    item->getItem(BasicAxisItem::P_NBINS)->setVisible(false);
    item->getItem(BasicAxisItem::P_TITLE)->setVisible(true);

    item = item->getItem(AmplitudeAxisItem::P_IS_VISIBLE);
    item->setValue(true);
    item->setVisible(false);

    registerTag(T_DATA_PROPERTIES, 1, 1, QStringList() << "DataPropertyContainer");

    ComboProperty combo = ComboProperty() << "nbins";
    addProperty(P_AXES_UNITS, combo.variant());

    mapper()->setOnPropertyChange([this](const QString& name) {
        if (name != P_AXES_UNITS)
            return;
        setAxesRangeToData();
        DataViewUtils::updateAxesTitle(this);
    });

    setLowerX(default_min);
    setUpperX(default_max);
    setLowerY(default_min);
    setUpperY(default_max);
    setXaxisTitle(x_axis_default_name);
    setYaxisTitle(y_axis_default_name);
}

int Data1DViewItem::getNbins() const
{
    return xAxisItem()->getItemValue(BasicAxisItem::P_NBINS).toInt();
}

double Data1DViewItem::getLowerX() const
{
    return getItem(P_XAXIS)->getItemValue(BasicAxisItem::P_MIN_DEG).toDouble();
}

double Data1DViewItem::getUpperX() const
{
    return getItem(P_XAXIS)->getItemValue(BasicAxisItem::P_MAX_DEG).toDouble();
}

double Data1DViewItem::getLowerY() const
{
    return getItem(P_YAXIS)->getItemValue(BasicAxisItem::P_MIN_DEG).toDouble();
}

double Data1DViewItem::getUpperY() const
{
    return getItem(P_YAXIS)->getItemValue(BasicAxisItem::P_MAX_DEG).toDouble();
}

bool Data1DViewItem::isLog() const
{
    return getItem(P_YAXIS)->getItemValue(AmplitudeAxisItem::P_IS_LOGSCALE).toBool();
}

QString Data1DViewItem::getXaxisTitle() const
{
    return getItem(P_XAXIS)->getItemValue(BasicAxisItem::P_TITLE).toString();
}

QString Data1DViewItem::getYaxisTitle() const
{
    return getItem(P_YAXIS)->getItemValue(BasicAxisItem::P_TITLE).toString();
}

void Data1DViewItem::setXaxisTitle(QString xtitle)
{
    getItem(P_XAXIS)->setItemValue(BasicAxisItem::P_TITLE, xtitle);
}

void Data1DViewItem::setYaxisTitle(QString ytitle)
{
    getItem(P_YAXIS)->setItemValue(AmplitudeAxisItem::P_TITLE, ytitle);
}

//! set zoom range of x,y axes to axes of input data
void Data1DViewItem::setAxesRangeToData()
{
    const auto data =
        DataViewUtils::getTranslatedData(this, propertyContainerItem()->basicDataItem());

    // For data loading from disk: items appear earlier than
    // actual data.
    if (!data)
        return;

    setLowerX(data->getAxis(0).getMin());
    setUpperX(data->getAxis(0).getMax());

    auto data_range = dataRange(data.get());
    setLowerY(data_range.first);
    setUpperY(data_range.second);
}

void Data1DViewItem::resetToDefault()
{
    // TODO: implement when applying DataITem1DView in ImportView
    throw GUIHelpers::Error("Error in DataItem1DView::resetToDefault: not implemented");
}

QPair<QVector<double>, QVector<double>> Data1DViewItem::graphData(Data1DProperties* property_item)
{
    const auto data = DataViewUtils::getTranslatedData(this, property_item->dataItem());
    if (!data)
        return {};

#if QT_VERSION >= QT_VERSION_CHECK(5, 14, 0)
    auto centers = data->getAxis(0).getBinCenters();
    auto values = data->getRawDataVector();
    return {QVector<double>(centers.begin(), centers.end()),
            QVector<double>(values.begin(), values.end())};
#else
    return {QVector<double>::fromStdVector(data->getAxis(0).getBinCenters()),
            QVector<double>::fromStdVector(data->getRawDataVector())};
#endif
}

JobItem* Data1DViewItem::jobItem()
{
    if (m_job_item != nullptr)
        return m_job_item; // returning preset job item

    auto item = parent();
    do {
        if (item->modelType() == "JobItem") {
            m_job_item = dynamic_cast<JobItem*>(item);
            return m_job_item;
        }
    } while ((item = item->parent()));
    throw GUIHelpers::Error(
        "Error in DataItem1DView::jobItem: passed item is not owned by any job item");
}

void Data1DViewItem::setLowerX(double xmin)
{
    getItem(P_XAXIS)->setItemValue(BasicAxisItem::P_MIN_DEG, xmin);
}

void Data1DViewItem::setUpperX(double xmax)
{
    getItem(P_XAXIS)->setItemValue(BasicAxisItem::P_MAX_DEG, xmax);
}

void Data1DViewItem::setLowerY(double ymin)
{
    getItem(P_YAXIS)->setItemValue(AmplitudeAxisItem::P_MIN_DEG, ymin);
}

void Data1DViewItem::setUpperY(double ymax)
{
    getItem(P_YAXIS)->setItemValue(AmplitudeAxisItem::P_MAX_DEG, ymax);
}

void Data1DViewItem::setLog(bool log_flag)
{
    getItem(P_YAXIS)->setItemValue(AmplitudeAxisItem::P_IS_LOGSCALE, log_flag);
}

DataPropertyContainer* Data1DViewItem::propertyContainerItem()
{
    return dynamic_cast<DataPropertyContainer*>(getItem(T_DATA_PROPERTIES));
}

const BasicAxisItem* Data1DViewItem::xAxisItem() const
{
    return dynamic_cast<const BasicAxisItem*>(getItem(P_XAXIS));
}

BasicAxisItem* Data1DViewItem::xAxisItem()
{
    return const_cast<BasicAxisItem*>(static_cast<const Data1DViewItem*>(this)->xAxisItem());
}

const AmplitudeAxisItem* Data1DViewItem::yAxisItem() const
{
    auto result = dynamic_cast<const AmplitudeAxisItem*>(getItem(P_YAXIS));
    ASSERT(result);
    return result;
}

//! Set axes viewport to original data.

void Data1DViewItem::resetView()
{
    setAxesRangeToData();
}

//! Init ymin, ymax to match the intensity values range.
QPair<double, double> Data1DViewItem::dataRange(const OutputData<double>* data) const
{
    if (!data)
        return QPair<double, double>(default_min, default_max);

    double min(*std::min_element(data->begin(), data->end()));
    double max(*std::max_element(data->begin(), data->end()));

    min /= 2.0;
    min = std::numeric_limits<double>::epsilon() < min ? min : default_min;
    max *= 2.0;
    max = max > min ? max : default_max;

    return QPair<double, double>(min, max);
}
