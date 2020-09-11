// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/JobWidgets/SliderSettingsWidget.h
//! @brief     Defines class SliderSettingsWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_VIEWS_JOBWIDGETS_SLIDERSETTINGSWIDGET_H
#define BORNAGAIN_GUI_COREGUI_VIEWS_JOBWIDGETS_SLIDERSETTINGSWIDGET_H

#include "Wrap/WinDllMacros.h"
#include <QWidget>

class QRadioButton;
class QCheckBox;

class BA_CORE_API_ SliderSettingsWidget : public QWidget
{
    Q_OBJECT

public:
    SliderSettingsWidget(QWidget* parent = 0);

signals:
    void sliderRangeFactorChanged(double value);
    void lockzChanged(bool value);

private slots:
    void rangeChanged();
    void onLockZChanged(int state);

private:
    double m_currentSliderRange;
    QRadioButton* m_radio1;
    QRadioButton* m_radio2;
    QRadioButton* m_radio3;
    QCheckBox* m_lockzCheckBox;
};

#endif // BORNAGAIN_GUI_COREGUI_VIEWS_JOBWIDGETS_SLIDERSETTINGSWIDGET_H
