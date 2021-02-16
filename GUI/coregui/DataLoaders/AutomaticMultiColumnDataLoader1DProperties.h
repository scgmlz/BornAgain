//  ************************************************************************************************
//
//  BornAgain: simulate and fit reflection and scattering
//
//! @file      M:\BornAgain\GUI\coregui\DataLoaders/AutomaticMultiColumnDataLoader1DProperties.h
//! @brief     Defines class AutomaticMultiColumnDataLoader1DProperties
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2021
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_GUI_COREGUI_DATALOADERS_AUTOMATICMULTICOLUMNDATALOADER1DPROPERTIES_H
#define BORNAGAIN_GUI_COREGUI_DATALOADERS_AUTOMATICMULTICOLUMNDATALOADER1DPROPERTIES_H

#include <QWidget>

class QComboBox;
class QDoubleSpinBox;
class QSpinBox;
class QCheckBox;

namespace Ui {
class AutomaticMultiColumnDataLoader1DProperties;
}

class AutomaticMultiColumnDataLoader1DProperties : public QWidget {
    Q_OBJECT
public:
    AutomaticMultiColumnDataLoader1DProperties();

    Ui::AutomaticMultiColumnDataLoader1DProperties* m_ui;

    QString unit(int dataType) const;
    double factor(int dataType) const;

    void setDataType(int dataType, bool enabled, int column, const QString& unit, double factor);

    QCheckBox* enablingCheckBox(int dataType) const;
    QComboBox* unitCombo(int dataType) const;
    QSpinBox* columnSpinBox(int dataType) const;
    QDoubleSpinBox* factorSpinBox(int dataType) const;

signals:
    void propertiesChanged();

private:
    void updateEnabling(int dataType, bool enabled);
    void onEnablingChanged(int dataType);
};

#endif // BORNAGAIN_GUI_COREGUI_DATALOADERS_AUTOMATICMULTICOLUMNDATALOADER1DPROPERTIES_H
