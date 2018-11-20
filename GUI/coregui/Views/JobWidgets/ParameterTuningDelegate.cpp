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

#include "ParameterTuningDelegate.h"
#include "ModelPath.h"
#include "ParameterTreeItems.h"
#include "ParameterTuningModel.h"
#include "ScientificSpinBox.h"
#include "SessionModel.h"
#include "SessionItemUtils.h"
#include <QAbstractItemModel>
#include <QApplication>
#include <QDoubleSpinBox>
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


namespace {
const double maximum_doublespin_value = std::numeric_limits<double>::max();
const double minimum_doublespin_value = std::numeric_limits<double>::lowest();
const double double_quant = std::numeric_limits<double>::min();
}

ParameterTuningDelegate::TuningData::TuningData()
    : m_smin(0)
    , m_smax(100)
    , m_rmin(0.0)
    , m_rmax(0.0)
    , m_range_factor(100.0)
{

}

void ParameterTuningDelegate::TuningData::setRangeFactor(double range_factor)
{
    m_range_factor = range_factor;
}

void ParameterTuningDelegate::TuningData::setItemLimits(const RealLimits &item_limits)
{
    m_item_limits = item_limits;
}

void ParameterTuningDelegate::TuningData::updateRealLimits(double value)
{
    const double abs_value = std::abs(value);
    const double dr =
        abs_value <= double_quant ? m_range_factor / 100. : abs_value * m_range_factor / 100.;
    m_rmin = value - dr;
    m_rmax = value + dr;

    if(m_item_limits.hasLowerLimit() && m_rmin < m_item_limits.lowerLimit())
        m_rmin = m_item_limits.lowerLimit();

    if(m_item_limits.hasUpperLimit() && m_rmax > m_item_limits.upperLimit())
        m_rmax = m_item_limits.upperLimit();
}

int ParameterTuningDelegate::TuningData::sliderPosition(double value)
{
    updateRealLimits(value);
    return m_smin + static_cast<int>((value - m_rmin) / step());
}

double ParameterTuningDelegate::TuningData::value(int slider_pos)
{
    return m_rmin + (slider_pos - m_smin) * step();
}

double ParameterTuningDelegate::TuningData::step() const
{
    return (m_rmax - m_rmin) / (m_smax - m_smin);
}

ParameterTuningDelegate::ParameterTuningDelegate(QObject *parent)
    : QItemDelegate(parent)
    , m_valueColumn(1)
    , m_slider(nullptr)
    , m_valueBox(nullptr)
    , m_contentWidget(nullptr)
    , m_contentLayout(nullptr)
    , m_currentItem(nullptr)
    , m_isReadOnly(false)
{

}

ParameterTuningDelegate::~ParameterTuningDelegate()
{
//    if(m_currentItem)
//        m_currentItem->mapper()->unsubscribe(this);

}

void ParameterTuningDelegate::paint(QPainter *painter,
                                const QStyleOptionViewItem &option,
                                const QModelIndex &index) const
{
    if (index.column() == m_valueColumn) {

        if(!index.parent().isValid()) return;

        QVariant prop_value = index.model()->data(index, Qt::EditRole);
        if(prop_value.isValid()) {
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


QWidget *ParameterTuningDelegate::createEditor(QWidget *parent,
                                           const QStyleOptionViewItem &option,
                                           const QModelIndex &index) const
{
    if(m_isReadOnly)
        return nullptr;

    if (index.column() != m_valueColumn)
        return QItemDelegate::createEditor(parent, option, index);

    if (!index.parent().isValid())
        return nullptr;

    QVariant data = index.model()->data(index, Qt::EditRole);
    if (!data.isValid())
        return nullptr;

    m_currentItem =
        static_cast<ParameterItem*>(ParameterTuningModel::toSourceIndex(index).internalPointer());
    if (!m_currentItem)
        return nullptr;

    double value = data.toDouble();
    RealLimits limits = m_currentItem->linkedItem()->limits();
    m_tuning_info.setItemLimits(limits);
    m_tuning_info.updateRealLimits(value);

    // initializing value box
    m_valueBox = new ScientificSpinBox();
    m_valueBox->setKeyboardTracking(false);
    m_valueBox->setFixedWidth(105);
    m_valueBox->setDecimalPoints(m_currentItem->linkedItem()->decimals());
    m_valueBox->setSingleStep(m_tuning_info.step());
    m_valueBox->setMinimum(limits.hasLowerLimit() ? limits.lowerLimit() : minimum_doublespin_value);
    m_valueBox->setMaximum(limits.hasUpperLimit() ? limits.upperLimit() : maximum_doublespin_value);

    m_valueBox->setValue(value);
    connect(m_valueBox,
            static_cast<void (QDoubleSpinBox::*)(double)>(&ScientificSpinBox::valueChanged),
            this, &ParameterTuningDelegate::editorValueChanged);

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

    m_contentWidget->setLayout(m_contentLayout);

    return m_contentWidget;
}


void ParameterTuningDelegate::updateSlider(double value) const
{
    disconnect(m_slider, SIGNAL(valueChanged(int)),this, SLOT(sliderValueChanged(int)));

    m_slider->setValue(m_tuning_info.sliderPosition(value));

    connect(m_slider, SIGNAL(valueChanged(int)),this, SLOT(sliderValueChanged(int)));
}


void ParameterTuningDelegate::sliderValueChanged(int position)
{
    disconnect(m_valueBox,
               static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
               this, &ParameterTuningDelegate::editorValueChanged);

    double value = m_tuning_info.value(position);
    m_valueBox->setValue(value);

    connect(m_valueBox,
            static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
            this, &ParameterTuningDelegate::editorValueChanged);
    emitSignals(value);
}


void ParameterTuningDelegate::editorValueChanged(double value)
{
    disconnect(m_slider, SIGNAL(valueChanged(int)),this, SLOT(sliderValueChanged(int)));

    updateSlider(value);

    connect(m_slider, SIGNAL(valueChanged(int)),this, SLOT(sliderValueChanged(int)));
    emitSignals(value);
}


void ParameterTuningDelegate::setEditorData(QWidget *editor,
                                        const QModelIndex &index) const
{
    if (index.column() == m_valueColumn) {
        //as using custom widget, doing nothing here
    } else {
        QItemDelegate::setEditorData(editor, index);
    }
}


void ParameterTuningDelegate::setModelData(QWidget *editor,
                                       QAbstractItemModel *model,
                                       const QModelIndex &index) const
{
    if (index.column() == m_valueColumn) {

        model->setData(index, m_valueBox->value());

    } else {
        QItemDelegate::setModelData(editor, model, index);
    }
}


void ParameterTuningDelegate::emitSignals(double value)
{
    if(m_currentItem) {
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
