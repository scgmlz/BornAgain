// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/MaskWidgets/MaskGraphicsView.h
//! @brief     Defines class MaskGraphicsView
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_VIEWS_MASKWIDGETS_MASKGRAPHICSVIEW_H
#define BORNAGAIN_GUI_COREGUI_VIEWS_MASKWIDGETS_MASKGRAPHICSVIEW_H

#include "GUI/coregui/Views/MaskWidgets/MaskEditorFlags.h"
#include <QGraphicsView>

class QWheelEvent;
class MaskGraphicsProxy;

//! Graphics view for MaskEditorCanvas

class MaskGraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    MaskGraphicsView(QGraphicsScene* scene, QWidget* parent = 0);
    QSize sizeHint() const { return QSize(512, 512); }
    QSize minimumSizeHint() const { return QSize(128, 128); }

public slots:
    void onResetViewRequest();

    void updateSize(const QSize& newSize);

signals:
    void changeActivityRequest(MaskEditorFlags::Activity);
    void deleteSelectedRequest();

protected:
    void wheelEvent(QWheelEvent* event);
    void resizeEvent(QResizeEvent* event);
    void keyPressEvent(QKeyEvent* event);
    void keyReleaseEvent(QKeyEvent* event);

private:
    bool isControlButtonIsPressed(QWheelEvent* event);
    void cancelCurrentDrawing();

    void setZoomValue(double zoom_value);
    void decreazeZoomValue();
    void increazeZoomValue();

    double m_current_zoom_value;
};

#endif // BORNAGAIN_GUI_COREGUI_VIEWS_MASKWIDGETS_MASKGRAPHICSVIEW_H
