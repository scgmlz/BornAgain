// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/InstrumentWidgets/GISASInstrumentEditor.h
//! @brief     Defines class GISASInstrumentEditor
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_VIEWS_INSTRUMENTWIDGETS_GISASINSTRUMENTEDITOR_H
#define BORNAGAIN_GUI_COREGUI_VIEWS_INSTRUMENTWIDGETS_GISASINSTRUMENTEDITOR_H

#include "GUI/coregui/Views/CommonWidgets/SessionItemWidget.h"

class GISASInstrumentItem;
class GISASBeamEditor;
class GISASDetectorEditor;
class EnvironmentEditor;
class PolarizationAnalysisEditor;
class ColumnResizer;

class BA_CORE_API_ GISASInstrumentEditor : public SessionItemWidget
{
    Q_OBJECT

public:
    GISASInstrumentEditor(QWidget* parent = nullptr);

protected:
    void subscribeToItem();

private:
    GISASInstrumentItem* instrumentItem();
    ColumnResizer* m_columnResizer;
    GISASBeamEditor* m_beamEditor;
    GISASDetectorEditor* m_detectorEditor;
    EnvironmentEditor* m_environmentEditor;
    PolarizationAnalysisEditor* m_polarizationAnalysisEditor;
};

#endif // BORNAGAIN_GUI_COREGUI_VIEWS_INSTRUMENTWIDGETS_GISASINSTRUMENTEDITOR_H
