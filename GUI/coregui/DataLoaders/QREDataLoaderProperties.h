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
class QLabel;

namespace Ui {
class QREDataLoaderProperties;
}

class QREDataLoaderProperties : public QWidget {
    Q_OBJECT
public:
    QREDataLoaderProperties();

    Ui::QREDataLoaderProperties* m_ui;

    void allowFactors(bool b);

    double factor(int dataType) const;

    QSpinBox* columnSpinBox(int dataType) const;
    QDoubleSpinBox* factorSpinBox(int dataType) const;

signals:
    void propertiesChanged();

private:
    void updateEnabling(int dataType, bool enabled);
    void updateErrorEnabling(bool enabled);
    void onErrorEnablingChanged();
    QLabel* factorLabel(int dataType) const;

    // factors shall not be supported. However, since the requirements have been there,
    // they are only deactivated. Call allowFactors(true) to enable them.
    bool m_allowFactors;

    static const int factorLabelColumn = 3;
    static const int factorColumn = factorLabelColumn + 1;
};

#endif // BORNAGAIN_GUI_COREGUI_DATALOADERS_AUTOMATICMULTICOLUMNDATALOADER1DPROPERTIES_H
