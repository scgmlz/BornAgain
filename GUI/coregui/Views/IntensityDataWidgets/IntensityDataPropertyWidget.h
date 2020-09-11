// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/IntensityDataWidgets/IntensityDataPropertyWidget.h
//! @brief     Defines class IntensityDataPropertyWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_VIEWS_INTENSITYDATAWIDGETS_INTENSITYDATAPROPERTYWIDGET_H
#define BORNAGAIN_GUI_COREGUI_VIEWS_INTENSITYDATAWIDGETS_INTENSITYDATAPROPERTYWIDGET_H

#include "GUI/coregui/Views/CommonWidgets/SessionItemWidget.h"

class IntensityDataItem;
class ComponentEditor;
class SessionItem;

//! The IntensityDataPropertyWidget shows ComponentEditor for given IntensityDataItem.

class BA_CORE_API_ IntensityDataPropertyWidget : public SessionItemWidget
{
    Q_OBJECT
public:
    explicit IntensityDataPropertyWidget(QWidget* parent = 0);

    QSize sizeHint() const;
    QSize minimumSizeHint() const;

    QList<QAction*> actionList();

public slots:
    void onTogglePanelAction();

protected:
    virtual void subscribeToItem();
    virtual void unsubscribeFromItem();
    void contextMenuEvent(QContextMenuEvent*);

private:
    QAction* m_togglePanelAction;
    ComponentEditor* m_componentEditor;
};

#endif // BORNAGAIN_GUI_COREGUI_VIEWS_INTENSITYDATAWIDGETS_INTENSITYDATAPROPERTYWIDGET_H
