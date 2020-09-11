// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/MaskWidgets/IntensityDataView.h
//! @brief     Defines IntensityDataView class
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_VIEWS_MASKWIDGETS_INTENSITYDATAVIEW_H
#define BORNAGAIN_GUI_COREGUI_VIEWS_MASKWIDGETS_INTENSITYDATAVIEW_H

#include "GUI/coregui/Views/MaskWidgets/IShape2DView.h"
#include "GUI/coregui/Views/MaskWidgets/SizeHandleElement.h"
#include <QMap>

//! The IntensityDataView is nothing move than just transparent rectangle to cover axes area
//! of ColorMapPlot inside MaskGraphicsScene. The goal of this rectangle is to hide all MaskViews
//! if they are going outside of ColorMapPlot.
//!
//! The size of the rectangle always matches axes viewport at any zoom level.
//! All MasksViews are added to IntensityDataView as children.

class BA_CORE_API_ IntensityDataView : public IShape2DView
{
    Q_OBJECT
public:
    IntensityDataView();

public slots:
    void update_view();

protected:
    void paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*);
};

#endif // BORNAGAIN_GUI_COREGUI_VIEWS_MASKWIDGETS_INTENSITYDATAVIEW_H
