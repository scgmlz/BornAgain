// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/InstrumentWidgets/DepthProbeInstrumentEditor.h
//! @brief     Defines class DepthProbeInstrumentEditor
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_VIEWS_INSTRUMENTWIDGETS_DEPTHPROBEINSTRUMENTEDITOR_H
#define BORNAGAIN_GUI_COREGUI_VIEWS_INSTRUMENTWIDGETS_DEPTHPROBEINSTRUMENTEDITOR_H

#include "GUI/coregui/Views/CommonWidgets/SessionItemWidget.h"

class ComponentEditor;
class QGridLayout;
class DepthProbeInstrumentItem;

class BA_CORE_API_ DepthProbeInstrumentEditor : public SessionItemWidget
{
    Q_OBJECT

public:
    DepthProbeInstrumentEditor(QWidget* parent = nullptr);

protected:
    void subscribeToItem();
    void unsubscribeFromItem();

private:
    DepthProbeInstrumentItem* instrumentItem();
    void onDialogRequest(SessionItem* item, const QString& name);

    ComponentEditor* m_wavelengthEditor;
    ComponentEditor* m_inclinationEditor;
    ComponentEditor* m_depthAxisEditor;
    QGridLayout* m_gridLayout;
};

#endif // BORNAGAIN_GUI_COREGUI_VIEWS_INSTRUMENTWIDGETS_DEPTHPROBEINSTRUMENTEDITOR_H
