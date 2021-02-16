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

namespace Ui {
class AutomaticMultiColumnDataLoader1DProperties;
}

class AutomaticMultiColumnDataLoader1DProperties : public QWidget {
    Q_OBJECT
public:
    AutomaticMultiColumnDataLoader1DProperties();

    Ui::AutomaticMultiColumnDataLoader1DProperties* m_ui;

    QComboBox* m_typeCombos[4];
    QComboBox* m_unitCombos[4];
    QDoubleSpinBox* m_factors[4];
    QList<QWidget*> m_widgetsOfColumns[4];

    QString unit(int col) const;
    double factor(int col) const;
    void setType(int col, int type);

signals:
    void propertiesChanged();

private:
    void onTypeComboChanged(int column);
};

#endif // BORNAGAIN_GUI_COREGUI_DATALOADERS_AUTOMATICMULTICOLUMNDATALOADER1DPROPERTIES_H
