// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/FitWidgets/FitComparisonController.h
//! @brief     Defines class FitComparisonController
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_VIEWS_FITWIDGETS_FITCOMPARISONCONTROLLER_H
#define BORNAGAIN_GUI_COREGUI_VIEWS_FITWIDGETS_FITCOMPARISONCONTROLLER_H

#include "Wrap/WinDllMacros.h"
#include <QObject>

class DataItem;
class IntensityDataItem;
class JobItem;
class PropertyRepeater;
class SessionModel;
class SpecularDataItem;

//! Provides synchronization between certain properties of fit related IntensityDataItems.
//! Used solely in FitComparisonWidget.

class BA_CORE_API_ FitComparisonController2D : public QObject
{
public:
    class DiffItemController;

    explicit FitComparisonController2D(QObject* parent = nullptr);

    IntensityDataItem* diffItem();

    void setItem(JobItem* job_item);
    void updateDiffData();
    void resetDiffItem();

    void clear();

private:
    DiffItemController* m_diff_item_controller;
    PropertyRepeater* m_appearanceRepeater;
    PropertyRepeater* m_xAxisRepeater;
    PropertyRepeater* m_yAxisRepeater;
    PropertyRepeater* m_zAxisRepeater;
};

#endif // BORNAGAIN_GUI_COREGUI_VIEWS_FITWIDGETS_FITCOMPARISONCONTROLLER_H
