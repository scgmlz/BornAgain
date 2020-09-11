// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/InstrumentWidgets/EnvironmentEditor.h
//! @brief     Defines class EnvironmentEditor
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_VIEWS_INSTRUMENTWIDGETS_ENVIRONMENTEDITOR_H
#define BORNAGAIN_GUI_COREGUI_VIEWS_INSTRUMENTWIDGETS_ENVIRONMENTEDITOR_H

#include "GUI/coregui/Views/CommonWidgets/SessionItemWidget.h"

class ComponentEditor;
class QGridLayout;
class InstrumentItem;
class ColumnResizer;

//! Environment editor (i.e. background) for instrument editors.
//! Operates on InstrumentItem.

class BA_CORE_API_ EnvironmentEditor : public SessionItemWidget
{
    Q_OBJECT

public:
    EnvironmentEditor(ColumnResizer* columnResizer, QWidget* parent = nullptr);

protected:
    void subscribeToItem();
    void unsubscribeFromItem();

private:
    InstrumentItem* instrumentItem();
    ColumnResizer* m_columnResizer;
    ComponentEditor* m_backgroundEditor;
    QGridLayout* m_gridLayout;
};

#endif // BORNAGAIN_GUI_COREGUI_VIEWS_INSTRUMENTWIDGETS_ENVIRONMENTEDITOR_H
