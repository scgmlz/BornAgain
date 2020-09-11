// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/MaskWidgets/MaskGraphicsProxy.h
//! @brief     Defines class MaskGraphicsProxy
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_VIEWS_MASKWIDGETS_MASKGRAPHICSPROXY_H
#define BORNAGAIN_GUI_COREGUI_VIEWS_MASKWIDGETS_MASKGRAPHICSPROXY_H

#include "GUI/coregui/Views/MaskWidgets/MaskEditorHelper.h"
#include <QGraphicsProxyWidget>

class SessionItem;
class ISceneAdaptor;
class ColorMapSceneAdaptor;
class ColorMap;
class IntensityDataItem;

//! Graphics proxy to place QWidget inside QGraphicsScene, used by MaskEditorCanvas.

class MaskGraphicsProxy : public QGraphicsProxyWidget
{
    Q_OBJECT

public:
    MaskGraphicsProxy();
    virtual ~MaskGraphicsProxy();

    int type() const { return MaskEditorHelper::MASKGRAPHICSPROXY; }

    void setIntensityItem(IntensityDataItem* item);
    void setSceneAdaptor(ISceneAdaptor* sceneAdaptor);
    void setInZoomMode(bool value);

    ColorMap* colorMap();

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent* event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event);
    void wheelEvent(QGraphicsSceneWheelEvent* event);

private:
    ColorMap* m_colorMap;
    ColorMapSceneAdaptor* m_sceneAdaptor;
    bool m_send_signals_to_colormap;
};

#endif // BORNAGAIN_GUI_COREGUI_VIEWS_MASKWIDGETS_MASKGRAPHICSPROXY_H
