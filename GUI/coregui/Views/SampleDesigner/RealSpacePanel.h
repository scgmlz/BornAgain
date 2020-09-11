// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/SampleDesigner/RealSpacePanel.h
//! @brief     Defines class RealSpacePanel
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_VIEWS_SAMPLEDESIGNER_REALSPACEPANEL_H
#define BORNAGAIN_GUI_COREGUI_VIEWS_SAMPLEDESIGNER_REALSPACEPANEL_H

#include "Wrap/WinDllMacros.h"
#include <QWidget>

class SampleModel;
class QItemSelectionModel;
class RealSpaceWidget;

//! Panel with item selector, property editor on the right side of RealSpaceWidget.

class BA_CORE_API_ RealSpacePanel : public QWidget
{
    Q_OBJECT

public:
    RealSpacePanel(SampleModel* sampleModel, QItemSelectionModel* selectionModel, QWidget* parent);

    QSize sizeHint() const override;

private:
    RealSpaceWidget* m_realSpaceWidget;
};

#endif // BORNAGAIN_GUI_COREGUI_VIEWS_SAMPLEDESIGNER_REALSPACEPANEL_H
