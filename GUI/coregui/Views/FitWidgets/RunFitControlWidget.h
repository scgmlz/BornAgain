// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/FitWidgets/RunFitControlWidget.h
//! @brief     Defines class RunFitControlWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_VIEWS_FITWIDGETS_RUNFITCONTROLWIDGET_H
#define BORNAGAIN_GUI_COREGUI_VIEWS_FITWIDGETS_RUNFITCONTROLWIDGET_H

#include "GUI/coregui/Views/CommonWidgets/SessionItemWidget.h"
#include <QWidget>

class JobItem;
class QPushButton;
class QSlider;
class WarningSign;
class QLabel;
class FitSuiteItem;
class JobMessagePanel;

//! The RunFitControlWidget contains elements to start/stop fitting and to provide minimal
//! diagnostic. Part of FitSuiteWidget.

class BA_CORE_API_ RunFitControlWidget : public SessionItemWidget
{
    Q_OBJECT
public:
    RunFitControlWidget(QWidget* parent = 0);
    ~RunFitControlWidget();

signals:
    void startFittingPushed();
    void stopFittingPushed();

public slots:
    void onFittingError(const QString& what);

private slots:
    void onSliderValueChanged(int value);
    void onFitSuitePropertyChange(const QString& name);

protected:
    virtual void subscribeToItem();
    virtual void unsubscribeFromItem();

private:
    int sliderUpdateInterval();
    int sliderValueToUpdateInterval(int value);
    void updateControlElements();
    JobItem* jobItem();
    FitSuiteItem* fitSuiteItem();
    bool isValidJobItem();
    void unsubscribeFromChildren();

    QPushButton* m_startButton;
    QPushButton* m_stopButton;
    QSlider* m_intervalSlider;
    QLabel* m_updateIntervalLabel;
    QLabel* m_iterationsCountLabel;
    WarningSign* m_warningSign;
};

#endif // BORNAGAIN_GUI_COREGUI_VIEWS_FITWIDGETS_RUNFITCONTROLWIDGET_H
