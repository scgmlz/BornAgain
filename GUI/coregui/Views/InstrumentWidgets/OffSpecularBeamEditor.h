//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/InstrumentWidgets/OffSpecularBeamEditor.h
//! @brief     Defines class OffSpecularBeamEditor
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_GUI_COREGUI_VIEWS_INSTRUMENTWIDGETS_OFFSPECULARBEAMEDITOR_H
#define BORNAGAIN_GUI_COREGUI_VIEWS_INSTRUMENTWIDGETS_OFFSPECULARBEAMEDITOR_H

#include "GUI/coregui/Views/CommonWidgets/SessionItemWidget.h"

class ComponentEditor;
class QGridLayout;
class OffSpecularInstrumentItem;
class BeamItem;
class ColumnResizer;

//! GISAS beam editor. Operates on GISASInstrumentItem.

class OffSpecularBeamEditor : public SessionItemWidget {
    Q_OBJECT

public:
    explicit OffSpecularBeamEditor(ColumnResizer* columnResizer, QWidget* parent = nullptr);

protected:
    void subscribeToItem();
    void unsubscribeFromItem();

private:
    OffSpecularInstrumentItem* instrumentItem();
    BeamItem* beamItem();
    void onDialogRequest(SessionItem* item, const QString& name);

    ColumnResizer* m_columnResizer;
    ComponentEditor* m_intensityEditor;
    ComponentEditor* m_wavelengthEditor;
    ComponentEditor* m_inclinationEditor;
    ComponentEditor* m_azimuthalEditor;
    QGridLayout* m_gridLayout;
};

#endif // BORNAGAIN_GUI_COREGUI_VIEWS_INSTRUMENTWIDGETS_OFFSPECULARBEAMEDITOR_H
