// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/SampleDesigner/ScriptPanel.h
//! @brief     Defines class SampleDesigner
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_VIEWS_SAMPLEDESIGNER_SCRIPTPANEL_H
#define BORNAGAIN_GUI_COREGUI_VIEWS_SAMPLEDESIGNER_SCRIPTPANEL_H

#include "GUI/coregui/Views/CommonWidgets/InfoPanel.h"

class SampleModel;
class InstrumentModel;
class PySampleWidget;

//! Resides at the bottom of SampleView and displays a Python script.

class BA_CORE_API_ ScriptPanel : public InfoPanel
{
    Q_OBJECT

public:
    explicit ScriptPanel(QWidget* parent = nullptr);

    void setSampleModel(SampleModel* sampleModel);
    void setInstrumentModel(InstrumentModel* instrumentModel);

private:
    PySampleWidget* m_pySampleWidget;
};

#endif // BORNAGAIN_GUI_COREGUI_VIEWS_SAMPLEDESIGNER_SCRIPTPANEL_H
