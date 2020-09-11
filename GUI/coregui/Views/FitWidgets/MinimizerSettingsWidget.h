// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/FitWidgets/MinimizerSettingsWidget.h
//! @brief     Defines class MinimizerSettingsWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_VIEWS_FITWIDGETS_MINIMIZERSETTINGSWIDGET_H
#define BORNAGAIN_GUI_COREGUI_VIEWS_FITWIDGETS_MINIMIZERSETTINGSWIDGET_H

#include "Wrap/WinDllMacros.h"
#include <QWidget>

class ComponentEditor;
class JobItem;
class MinimizerContainerItem;

//! The MinimizerSettingsWidget contains editor for all minnimizer settings and related fit
//! options. Part of FitSuiteWidget.

class BA_CORE_API_ MinimizerSettingsWidget : public QWidget
{
    Q_OBJECT

public:
    MinimizerSettingsWidget(QWidget* parent = nullptr);

    QSize minimumSizeHint() const;

public slots:
    void setItem(JobItem* jobItem);
    void setItem(MinimizerContainerItem* minimizerItem);

private:
    MinimizerContainerItem* m_currentItem;
    ComponentEditor* m_componentEditor;
};

#endif // BORNAGAIN_GUI_COREGUI_VIEWS_FITWIDGETS_MINIMIZERSETTINGSWIDGET_H
