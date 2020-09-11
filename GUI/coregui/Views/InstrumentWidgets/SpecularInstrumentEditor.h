// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/InstrumentWidgets/SpecularInstrumentEditor.h
//! @brief     Defines class SpecularInstrumentEditor
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_VIEWS_INSTRUMENTWIDGETS_SPECULARINSTRUMENTEDITOR_H
#define BORNAGAIN_GUI_COREGUI_VIEWS_INSTRUMENTWIDGETS_SPECULARINSTRUMENTEDITOR_H

#include "GUI/coregui/Views/CommonWidgets/SessionItemWidget.h"

class SpecularInstrumentItem;
class SpecularBeamEditor;
class EnvironmentEditor;
class PolarizationAnalysisEditor;
class ColumnResizer;
class QVBoxLayout;

class BA_CORE_API_ SpecularInstrumentEditor : public SessionItemWidget
{
    Q_OBJECT

public:
    SpecularInstrumentEditor(QWidget* parent = nullptr);

protected:
    void subscribeToItem();

private:
    SpecularInstrumentItem* instrumentItem();
    ColumnResizer* m_columnResizer;
    SpecularBeamEditor* m_beamEditor;
    EnvironmentEditor* m_environmentEditor;
    PolarizationAnalysisEditor* m_polarizationAnalysisEditor;
};

#endif // BORNAGAIN_GUI_COREGUI_VIEWS_INSTRUMENTWIDGETS_SPECULARINSTRUMENTEDITOR_H
