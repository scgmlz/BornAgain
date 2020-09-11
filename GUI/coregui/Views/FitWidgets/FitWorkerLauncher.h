// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/FitWidgets/FitWorkerLauncher.h
//! @brief     Implements class FitWorkerLauncher
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_VIEWS_FITWIDGETS_FITWORKERLAUNCHER_H
#define BORNAGAIN_GUI_COREGUI_VIEWS_FITWIDGETS_FITWORKERLAUNCHER_H

#include "Wrap/WinDllMacros.h"
#include <QObject>
#include <atomic>
#include <memory>

class FitObjectiveBuilder;

class BA_CORE_API_ FitWorkerLauncher : public QObject
{
    Q_OBJECT

public:
    FitWorkerLauncher(QObject* parent);

    void runFitting(std::shared_ptr<FitObjectiveBuilder> suite);

    int getDuration();

public slots:
    void interruptFitting();

signals:
    void fittingStarted();
    void fittingFinished();
    void fittingError(const QString& message);
    void intern_interruptFittingWorker();

private slots:
    void intern_workerFinished(int duration);

    void intern_workerStarted();

    void intern_error(const QString& mesg);

private:
    std::atomic<bool> m_is_fit_running;
    int m_duration;
};

#endif // BORNAGAIN_GUI_COREGUI_VIEWS_FITWIDGETS_FITWORKERLAUNCHER_H
