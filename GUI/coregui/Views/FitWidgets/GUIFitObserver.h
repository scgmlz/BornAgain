// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/FitWidgets/GUIFitObserver.h
//! @brief     Implements class GUIFitObserver
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_VIEWS_FITWIDGETS_GUIFITOBSERVER_H
#define BORNAGAIN_GUI_COREGUI_VIEWS_FITWIDGETS_GUIFITOBSERVER_H

#include "GUI/coregui/Views/FitWidgets/FitProgressInfo.h"
#include <QObject>
#include <condition_variable>
#include <mutex>

template <class T> class OutputData;
class IntensityDataItem;
class FitObjective;

//! Serves as observer for FitObjective and saves fit iteration data for later display
//! in GUI widgets.

class BA_CORE_API_ GUIFitObserver : public QObject
{
    Q_OBJECT

public:
    GUIFitObserver(QObject* parent = nullptr);
    ~GUIFitObserver();

    void update(const FitObjective* subject);

    void finishedPlotting();

    FitProgressInfo progressInfo();

public slots:
    void setInterval(int val);

signals:
    void updateReady();

private:
    bool is_suitable_iteration(const FitObjective* fitSuite) const;
    bool is_obligatory_iteration(const FitObjective* fitSuite) const;

    bool m_block_update_plots;
    std::mutex m_update_plot_mutex;
    std::condition_variable m_on_finish_notifier;
    int m_update_interval;
    FitProgressInfo m_iteration_info;
};

#endif // BORNAGAIN_GUI_COREGUI_VIEWS_FITWIDGETS_GUIFITOBSERVER_H
