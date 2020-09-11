// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/SampleDesigner/SampleWidgetBox.h
//! @brief     Defines class SampleWidgetBox
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_VIEWS_SAMPLEDESIGNER_SAMPLEWIDGETBOX_H
#define BORNAGAIN_GUI_COREGUI_VIEWS_SAMPLEDESIGNER_SAMPLEWIDGETBOX_H

#include "Wrap/WinDllMacros.h"
#include <QWidget>

class QDesignerWidgetBoxInterface;
class SampleDesignerInterface;

//! widget box and tool window on the left side of SampleView
class BA_CORE_API_ SampleWidgetBox : public QWidget
{
public:
    explicit SampleWidgetBox(SampleDesignerInterface* core, QWidget* parent);

    QSize minimumSizeHint() const override { return QSize(300, 300); }

private:
    SampleDesignerInterface* m_core;
    QDesignerWidgetBoxInterface* m_widgetBox;
};

#endif // BORNAGAIN_GUI_COREGUI_VIEWS_SAMPLEDESIGNER_SAMPLEWIDGETBOX_H
