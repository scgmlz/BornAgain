// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/JobWidgets/ProjectionsPropertyPanel.h
//! @brief     Defines class ProjectionsPropertyPanel
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_VIEWS_JOBWIDGETS_PROJECTIONSPROPERTYPANEL_H
#define BORNAGAIN_GUI_COREGUI_VIEWS_JOBWIDGETS_PROJECTIONSPROPERTYPANEL_H

#include "GUI/coregui/Views/CommonWidgets/SessionItemWidget.h"

class ComponentEditor;

class BA_CORE_API_ ProjectionsPropertyPanel : public SessionItemWidget
{
    Q_OBJECT

public:
    ProjectionsPropertyPanel(QWidget* parent = nullptr);

    QSize sizeHint() const;
    QSize minimumSizeHint() const;

protected:
    void subscribeToItem();
    void unsubscribeFromItem();

private:
    ComponentEditor* m_componentEditor;
};

#endif // BORNAGAIN_GUI_COREGUI_VIEWS_JOBWIDGETS_PROJECTIONSPROPERTYPANEL_H
