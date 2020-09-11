// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/MaskWidgets/MaskAllView.h
//! @brief     Defines MaskAllView class
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_VIEWS_MASKWIDGETS_MASKALLVIEW_H
#define BORNAGAIN_GUI_COREGUI_VIEWS_MASKWIDGETS_MASKALLVIEW_H

#include "GUI/coregui/Views/MaskWidgets/IShape2DView.h"

//! This is a view of MaskAllItem which covers whole detector plane with mask value=true.

class BA_CORE_API_ MaskAllView : public IShape2DView
{
    Q_OBJECT

public:
    int type() const { return MaskEditorHelper::MASKALL; }

    MaskAllView();

protected slots:
    virtual void update_view();

protected:
    void paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*);
};

#endif // BORNAGAIN_GUI_COREGUI_VIEWS_MASKWIDGETS_MASKALLVIEW_H
