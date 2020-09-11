// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/InstrumentWidgets/SphericalDetectorEditor.h
//! @brief     Defines class SphericalDetectorEditor
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_VIEWS_INSTRUMENTWIDGETS_SPHERICALDETECTOREDITOR_H
#define BORNAGAIN_GUI_COREGUI_VIEWS_INSTRUMENTWIDGETS_SPHERICALDETECTOREDITOR_H

#include "GUI/coregui/Views/CommonWidgets/SessionItemWidget.h"
class SphericalDetectorItem;
class ComponentEditor;
class QGridLayout;

class BA_CORE_API_ SphericalDetectorEditor : public SessionItemWidget
{
    Q_OBJECT

public:
    SphericalDetectorEditor(QWidget* parent = nullptr);

protected:
    void subscribeToItem();
    void unsubscribeFromItem();
    SphericalDetectorItem* detectorItem();

private:
    ComponentEditor* m_phiAxisEditor;
    ComponentEditor* m_alphaAxisEditor;
    ComponentEditor* m_resolutionFunctionEditor;
    QGridLayout* m_gridLayout;
};

#endif // BORNAGAIN_GUI_COREGUI_VIEWS_INSTRUMENTWIDGETS_SPHERICALDETECTOREDITOR_H
