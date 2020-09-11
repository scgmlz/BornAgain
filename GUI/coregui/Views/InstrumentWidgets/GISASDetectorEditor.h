// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/InstrumentWidgets/GISASDetectorEditor.h
//! @brief     Defines class GISASDetectorEditor
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_VIEWS_INSTRUMENTWIDGETS_GISASDETECTOREDITOR_H
#define BORNAGAIN_GUI_COREGUI_VIEWS_INSTRUMENTWIDGETS_GISASDETECTOREDITOR_H

#include "GUI/coregui/Views/CommonWidgets/SessionItemWidget.h"

class ComponentEditor;
class DetectorPresenter;
class Instrument2DItem;

//! GISAS detector editor. Provides selector between available detector types
//! (spherical/rectangular) and stack to show proper editor.
//! Operates on GISASInstrumentItem.

class BA_CORE_API_ GISASDetectorEditor : public SessionItemWidget
{
    Q_OBJECT

public:
    GISASDetectorEditor(QWidget* parent = nullptr);

protected:
    void subscribeToItem();
    void unsubscribeFromItem();

private:
    Instrument2DItem* instrumentItem();
    void updateDetectorPresenter();

    ComponentEditor* m_detectorTypeEditor;
    DetectorPresenter* m_detectorPresenter;
};

#endif // BORNAGAIN_GUI_COREGUI_VIEWS_INSTRUMENTWIDGETS_GISASDETECTOREDITOR_H
