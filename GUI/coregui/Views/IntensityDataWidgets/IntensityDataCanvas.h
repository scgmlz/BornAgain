// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/IntensityDataWidgets/IntensityDataCanvas.h
//! @brief     Defines class IntensityDataCanvas
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_VIEWS_INTENSITYDATAWIDGETS_INTENSITYDATACANVAS_H
#define BORNAGAIN_GUI_COREGUI_VIEWS_INTENSITYDATAWIDGETS_INTENSITYDATACANVAS_H

#include "Core/Intensity/OutputData.h"
#include "GUI/coregui/Views/CommonWidgets/SessionItemWidget.h"
#include <memory>

class SessionItem;
class IntensityDataItem;
class ColorMapCanvas;
class QAction;

//! The IntensityDataCanvas class represents IntensityDataItem as color map,
//! provides standard actions (reset view, save as) for external toolbars and context menus.

class BA_CORE_API_ IntensityDataCanvas : public SessionItemWidget
{
    Q_OBJECT
public:
    explicit IntensityDataCanvas(QWidget* parent = 0);

    void setItem(SessionItem* intensityItem);

    QSize sizeHint() const;
    QSize minimumSizeHint() const;

    QList<QAction*> actionList();

public slots:
    void onResetViewAction();
    void onSavePlotAction();
    void onMousePress(QMouseEvent* event);

protected:
    void subscribeToItem();

private:
    IntensityDataItem* intensityDataItem();
    void initActions();
    void onPropertyChanged(const QString& name);
    void applyPersistentSettings();

    ColorMapCanvas* m_colorMap;
    QAction* m_resetViewAction;
    QAction* m_savePlotAction;
};

#endif // BORNAGAIN_GUI_COREGUI_VIEWS_INTENSITYDATAWIDGETS_INTENSITYDATACANVAS_H
