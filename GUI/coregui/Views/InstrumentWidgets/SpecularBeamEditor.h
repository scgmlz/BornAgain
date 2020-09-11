// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/InstrumentWidgets/SpecularBeamEditor.h
//! @brief     Defines class SpecularBeamEditor
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_VIEWS_INSTRUMENTWIDGETS_SPECULARBEAMEDITOR_H
#define BORNAGAIN_GUI_COREGUI_VIEWS_INSTRUMENTWIDGETS_SPECULARBEAMEDITOR_H

#include "GUI/coregui/Views/CommonWidgets/SessionItemWidget.h"

class BeamItem;
class ColumnResizer;
class ComponentEditor;
class QGridLayout;
class SpecularInstrumentItem;

//! Specular beam editor. Operates on SpecularInstrumentItem.

class BA_CORE_API_ SpecularBeamEditor : public SessionItemWidget
{
    Q_OBJECT

public:
    explicit SpecularBeamEditor(ColumnResizer* columnResizer, QWidget* parent = nullptr);

protected:
    void subscribeToItem();
    void unsubscribeFromItem();

private:
    SpecularInstrumentItem* instrumentItem();
    void onDialogRequest(SessionItem* item, const QString& name);

    ColumnResizer* m_columnResizer;
    ComponentEditor* m_intensityEditor;
    ComponentEditor* m_wavelengthEditor;
    ComponentEditor* m_inclinationEditor;
    ComponentEditor* m_footprint_editor;
    QGridLayout* m_gridLayout;
};

#endif // BORNAGAIN_GUI_COREGUI_VIEWS_INSTRUMENTWIDGETS_SPECULARBEAMEDITOR_H
