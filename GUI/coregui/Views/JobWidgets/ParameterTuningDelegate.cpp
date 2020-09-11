// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/JobWidgets/ParameterTuningDelegate.cpp
//! @brief     Implements class ParameterTuningDelegate
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/coregui/Views/JobWidgets/ParameterTuningDelegate.h"
#include "GUI/coregui/Models/ModelPath.h"
#include "GUI/coregui/Models/ParameterTreeItems.h"
#include "GUI/coregui/Models/ParameterTuningModel.h"
#include "GUI/coregui/Models/SessionItemUtils.h"
#include "GUI/coregui/Models/SessionModel.h"
#include "GUI/coregui/Views/JobWidgets/ScientificSpinBox.h"
#include <QAbstractItemModel>
#include <QApplication>
#include <QHBoxLayout>
#include <QItemSelectionModel>
#include <QMouseEvent>
#include <QPaintDevice>
#include <QPainter>
#include <QRect>
#include <QStyleOptionSlider>
#include <QWidget>
#include <cmath>
#include <iostream>
#include <limits>

namespace
{
const double maximum_doublespin_value = std::numeric_limits<double>::max();
const double minimum_doublespin_value = std::numeric_limits<double>::lowest();
} // namespace

ParameterTuningDelegate::TuningData::TuningData()
    : m_smin(0), m_smax(100), m_rmin(0.0), m_rmax(0.0), m_range_factor(100.0)
{
}

void ParameterTuningDelegate::TuningData::setRangeFactor(double range_factor)
{
    m_range_factor = range_factor;
}

void ParameterTuningDelegate::TuningData::setItemLimits(const RealLimits& item_limits)
{
    m_item_limits = item_limits;
}

int ParameterTuningDelegate::TuningData::value_to_slider(double value)
{
    double dr(0);
    if (value == 0.0) {
        dr = 1.0 * m_range_factor / 100.;
    } else {
        dr = std::abs(value) * m_range_factor / 100.;
    }
    m_rmin = value - dr;
    m_rmax = value + dr;

    if (m_item_limits.hasLowerLimit() && m_rmin < m_item_limits.lowerLimit())
        m_rmin = m_item_limits.lowerLimit();

    if (m_item_limits.hasUpperLimit() && m_rmax > m_item_limits.upperLimit())
        m_rmax = m_item_limits.upperLimit();

    double result = m_smin + (value - m_rmin) * (m_smax - m_smin) / (m_rmax - m_rmin);
    return static_cast<int>(result);
}

double ParameterTuningDelegate::TuningData::slider_to_value(int slider)
{
    return m_rmin + (slider - m_smin) * (m_rmax - m_rmin) / (m_smax - m_smin);
}

double ParameterTuningDelegate::TuningData::step() const
{
    return (m_rmax - m_rmin) / (m_smax - m_smin);
}

ParameterTuningDelegate::ParameterTuningDelegate(QObject* parent)
    : QItemDelegate(parent), m_valueColumn(1), m_slider(nullptr), m_valueBox(nullptr),
      m_contentWidget(nullptr), m_contentLayout(nullptr), m_currentItem(nullptr),
      m_isReadOnly(false)
{
}

ParameterTuningDelegate::~ParameterTuningDelegate() {}

void ParameterTuningDelegate::paint(QPainter* painter, const QStyleOptionViewItem& option,
                                    const QModelIndex& index) const
{
    if (index.column() == m_valueColumn) {

        if (!index.parent().isValid())
            return;

        QVariant prop_value = index.model()->data(index, Qt::EditRole);
        if (prop_value.isValid()) {
            int type = SessionItemUtils::VariantType(prop_value);
            if (type == QVariant::Double) {
                double value = prop_value.toDouble();
                QString text = ScientificSpinBox::toString(value, 3);

                QStyleOptionViewItem myOption = option;
                myOption.displayAlignment = Qt::AlignLeft | Qt::AlignVCenter;

                drawDisplay(painter, myOption, myOption.rect, text);
                drawFocus(painter, myOption, myOption.rect);
                return;
            }
        }
    }
    QItemDelegate::paint(painter, option, index);
}

QWidget* ParameterTuningDelegate::createEditor(QWidget* parent, const QStyleOptionViewItem& option,
                                               const QModelIndex& index) const
{
    if (m_isReadOnly)
        return nullptr;

    if (index.column() == m_valueColumn) {
        if (index.parent().isValid() == false)
            return nullptr;

        QVariant data = index.model()->data(index, Qt::EditRole);
        if (!data.isValid())
            return nullptr;

        m_currentItem = static_cast<ParameterItem*>(
            ParameterTuningModel::toSourceIndex(index).internalPointer());
        if (!m_currentItem)
            return nullptr;

        double value = data.toDouble();
        RealLimits limits = m_currentItem->linkedItem()->limits();
        m_tuning_info.setItemLimits(limits);
        m_tuning_info.value_to_slider(value);

        // initializing value box
        m_valueBox = new ScientificSpinBox();
        m_valueBox->setKeyboardTracking(false);
        m_valueBox->setFixedWidth(105);
        m_valueBox->setDecimals(m_currentItem->linkedItem()->decimals());
        m_valueBox->setSingleStep(m_tuning_info.step());

        if (limits.hasLowerLimit()) {
            m_valueBox->setMinimum(limits.lowerLimit());
        } else {
            m_valueBox->setMinimum(minimum_doublespin_value);
        }

        if (limits.hasUpperLimit()) {
            m_valueBox->setMaximum(limits.upperLimit());
        } else {
            m_valueBox->setMaximum(maximum_doublespin_value);
        }

        m_valueBox->setValue(value);
        connect(m_valueBox, &ScientificSpinBox::valueChanged, this,
                &ParameterTuningDelegate::editorValueChanged);

        // initializing slider
        m_slider = new QSlider(Qt::Horizontal);
        m_slider->setFocusPolicy(Qt::StrongFocus);
        m_slider->setTickPosition(QSlider::NoTicks);
        m_slider->setTickInterval(1);
        m_slider->setSingleStep(1);
        m_slider->setRange(m_tuning_info.m_smin, m_tuning_info.m_smax);

        updateSlider(value);

        m_contentWidget = new QWidget(parent);
        m_contentLayout = new QHBoxLayout(parent);
        m_contentLayout->setMargin(0);
        m_contentLayout->setSpacing(0);
        m_contentLayout->addWidget(m_valueBox);
        m_contentLayout->addWidget(m_slider);

        // FIXME there is an issue with time of life of editor .vs. item
        //        m_currentItem->mapper()->setOnValueChange(
        //                      [this](){
        //            if(m_valueBox && m_currentItem)
        //              m_valueBox->setValue(m_currentItem->value().toDouble());
        //        }, this);

        //        m_currentItem->mapper()->setOnItemDestroy(
        //                    [this](SessionItem *) {
        //            m_currentItem = 0;
        //        }, this);

        m_contentWidget->setLayout(m_contentLayout);

        return m_contentWidget;
    } else {
        return QItemDelegate::createEditor(parent, option, index);
    }
}

void ParameterTuningDelegate::updateSlider(double value) const
{
    disconnect(m_slider, &QSlider::valueChanged, this,
               &ParameterTuningDelegate::sliderValueChanged);

    m_slider->setValue(m_tuning_info.value_to_slider(value));

    connect(m_slider, &QSlider::valueChanged, this, &ParameterTuningDelegate::sliderValueChanged);
}

void ParameterTuningDelegate::sliderValueChanged(int position)
{
    disconnect(m_valueBox, &ScientificSpinBox::valueChanged, this,
               &ParameterTuningDelegate::editorValueChanged);

    double value = m_tuning_info.slider_to_value(position);
    m_valueBox->setValue(value);

    connect(m_valueBox, &ScientificSpinBox::valueChanged, this,
            &ParameterTuningDelegate::editorValueChanged);
    emitSignals(value);
}

void ParameterTuningDelegate::editorValueChanged(double value)
{
    disconnect(m_slider, &QSlider::valueChanged, this,
               &ParameterTuningDelegate::sliderValueChanged);

    updateSlider(value);

    connect(m_slider, &QSlider::valueChanged, this, &ParameterTuningDelegate::sliderValueChanged);
    emitSignals(value);
}

void ParameterTuningDelegate::setEditorData(QWidget* editor, const QModelIndex& index) const
{
    if (index.column() == m_valueColumn) {
        // as using custom widget, doing nothing here
    } else {
        QItemDelegate::setEditorData(editor, index);
    }
}

void ParameterTuningDelegate::setModelData(QWidget* editor, QAbstractItemModel* model,
                                           const QModelIndex& index) const
{
    if (index.column() == m_valueColumn) {

        model->setData(index, m_valueBox->value());

    } else {
        QItemDelegate::setModelData(editor, model, index);
    }
}

void ParameterTuningDelegate::emitSignals(double value)
{
    if (m_currentItem) {
        m_currentItem->propagateValueToLink(value);
        emit currentLinkChanged(m_currentItem);
    }
}

void ParameterTuningDelegate::setSliderRangeFactor(double value)
{
    m_tuning_info.setRangeFactor(value);
}

void ParameterTuningDelegate::setReadOnly(bool isReadOnly)
{
    m_isReadOnly = isReadOnly;
}
