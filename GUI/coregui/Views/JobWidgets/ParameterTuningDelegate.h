// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/JobWidgets/ParameterTuningDelegate.h
//! @brief     Defines class ParameterTuningDelegate
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_VIEWS_JOBWIDGETS_PARAMETERTUNINGDELEGATE_H
#define BORNAGAIN_GUI_COREGUI_VIEWS_JOBWIDGETS_PARAMETERTUNINGDELEGATE_H

#include "Fit/Tools/RealLimits.h"
#include <QItemDelegate>
#include <memory>

class QDoubleSpinBox;
class QHBoxLayout;
class ParameterItem;
class ScientificSpinBox;
class SessionItem;

class BA_CORE_API_ ParameterTuningDelegate : public QItemDelegate
{
    Q_OBJECT

public:
    class TuningData
    {
    public:
        TuningData();
        void setRangeFactor(double range_factor);
        void setItemLimits(const RealLimits& item_limits);
        int value_to_slider(double value);
        double slider_to_value(int slider);
        double step() const;
        int m_smin;
        int m_smax;
        double m_rmin;
        double m_rmax;
        double m_range_factor;
        RealLimits m_item_limits;
    };

    ParameterTuningDelegate(QObject* parent = 0);
    ~ParameterTuningDelegate();

    QSize sizeHint(const QStyleOptionViewItem& option, const QModelIndex& /* index */) const
    {
        return QSize(option.rect.width(), 25);
    }

    void paint(QPainter* painter, const QStyleOptionViewItem& option,
               const QModelIndex& index) const;
    QWidget* createEditor(QWidget* parent, const QStyleOptionViewItem& option,
                          const QModelIndex& index) const;
    void setEditorData(QWidget* editor, const QModelIndex& index) const;
    void setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const;
    void setSliderRangeFactor(double value);

    void setValueColumn(int valueColumn) { m_valueColumn = valueColumn; }

    void setReadOnly(bool isReadOnly);

signals:
    void currentLinkChanged(SessionItem* item);

private slots:
    void sliderValueChanged(int position);
    void editorValueChanged(double value);

private:
    void updateSlider(double value) const;
    void emitSignals(double value);

    int m_valueColumn;
    mutable QSlider* m_slider;
    mutable ScientificSpinBox* m_valueBox;
    mutable QWidget* m_contentWidget;
    mutable QHBoxLayout* m_contentLayout;
    mutable ParameterItem* m_currentItem;
    mutable TuningData m_tuning_info;
    bool m_isReadOnly;
};

#endif // BORNAGAIN_GUI_COREGUI_VIEWS_JOBWIDGETS_PARAMETERTUNINGDELEGATE_H
