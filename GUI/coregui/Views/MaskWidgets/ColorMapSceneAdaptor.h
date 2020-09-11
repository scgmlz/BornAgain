// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/MaskWidgets/ColorMapSceneAdaptor.h
//! @brief     Defines class ColorMapSceneAdaptor
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_VIEWS_MASKWIDGETS_COLORMAPSCENEADAPTOR_H
#define BORNAGAIN_GUI_COREGUI_VIEWS_MASKWIDGETS_COLORMAPSCENEADAPTOR_H

#include "GUI/coregui/Views/MaskWidgets/ISceneAdaptor.h"
class ColorMap;

//! Performs conversion of MaskItems coordinates between ColorMap and GraphicsScene.

class ColorMapSceneAdaptor : public ISceneAdaptor
{
    Q_OBJECT

public:
    ColorMapSceneAdaptor();

    qreal toSceneX(qreal mask_x) const;
    qreal toSceneY(qreal mask_y) const;
    qreal fromSceneX(qreal scene_x) const;
    qreal fromSceneY(qreal scene_y) const;

    void setColorMapPlot(ColorMap* plot);

    bool eventFilter(QObject* object, QEvent* event);

    //! returns ColorMapPlot axes rectangle (at current zoom level) in scene coordinates
    const QRectF& viewportRectangle() const;

private:
    ColorMap* m_plot;
};

#endif // BORNAGAIN_GUI_COREGUI_VIEWS_MASKWIDGETS_COLORMAPSCENEADAPTOR_H
