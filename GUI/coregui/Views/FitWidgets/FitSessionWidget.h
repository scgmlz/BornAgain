// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/FitWidgets/FitSessionWidget.h
//! @brief     Defines class FitSessionWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_VIEWS_FITWIDGETS_FITSESSIONWIDGET_H
#define BORNAGAIN_GUI_COREGUI_VIEWS_FITWIDGETS_FITSESSIONWIDGET_H

#include "GUI/coregui/Views/FitWidgets/FitProgressInfo.h"
#include "Wrap/WinDllMacros.h"
#include <QWidget>

class QTabWidget;
class RunFitControlWidget;
class JobItem;
class FitParameterWidget;
class MinimizerSettingsWidget;
class FitResultsWidget;
class ParameterTuningWidget;
class FitSessionController;
class JobMessagePanel;

//! Contains all fit settings for given JobItem (fit parameters,
//! minimizer settings). Controlled by FitActivityPanel.

class BA_CORE_API_ FitSessionWidget : public QWidget
{
    Q_OBJECT

public:
    FitSessionWidget(QWidget* parent = nullptr);

    void setItem(JobItem* jobItem);
    void setModelTuningWidget(ParameterTuningWidget* tuningWidget);
    void setSessionController(FitSessionController* sessionController);

    QSize sizeHint() const;
    QSize minimumSizeHint() const;

private slots:
    void onFittingError(const QString& text);

private:
    QTabWidget* m_tabWidget;
    RunFitControlWidget* m_controlWidget;
    FitParameterWidget* m_fitParametersWidget;
    MinimizerSettingsWidget* m_minimizerSettingsWidget;
    FitResultsWidget* m_fitResultsWidget;
    FitSessionController* m_sessionController;
};

#endif // BORNAGAIN_GUI_COREGUI_VIEWS_FITWIDGETS_FITSESSIONWIDGET_H
