//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/InstrumentWidgets/OffSpecularInstrumentEditor.h
//! @brief     Defines class OffSpecularInstrumentEditor
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_GUI_COREGUI_VIEWS_INSTRUMENTWIDGETS_OFFSPECULARINSTRUMENTEDITOR_H
#define BORNAGAIN_GUI_COREGUI_VIEWS_INSTRUMENTWIDGETS_OFFSPECULARINSTRUMENTEDITOR_H

#include "GUI/coregui/Views/CommonWidgets/SessionItemWidget.h"

class OffSpecularInstrumentItem;
class OffSpecularBeamEditor;
class GISASDetectorEditor;
class EnvironmentEditor;
class PolarizationAnalysisEditor;
class ColumnResizer;

class OffSpecularInstrumentEditor : public SessionItemWidget {
    Q_OBJECT

public:
    OffSpecularInstrumentEditor(QWidget* parent = nullptr);

protected:
    void subscribeToItem();

private:
    OffSpecularInstrumentItem* instrumentItem();
    ColumnResizer* m_columnResizer;
    OffSpecularBeamEditor* m_beamEditor;
    GISASDetectorEditor* m_detectorEditor;
    EnvironmentEditor* m_environmentEditor;
    PolarizationAnalysisEditor* m_polarizationAnalysisEditor;
};

#endif // BORNAGAIN_GUI_COREGUI_VIEWS_INSTRUMENTWIDGETS_OFFSPECULARINSTRUMENTEDITOR_H
