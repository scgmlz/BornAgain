// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/MaskWidgets/IShape2DView.h
//! @brief     Defines class IShape2DView.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_VIEWS_MASKWIDGETS_ISHAPE2DVIEW_H
#define BORNAGAIN_GUI_COREGUI_VIEWS_MASKWIDGETS_ISHAPE2DVIEW_H

#include "GUI/coregui/Views/MaskWidgets/MaskEditorHelper.h"
#include "Wrap/WinDllMacros.h"
#include <QGraphicsObject>

class SessionItem;
class ISceneAdaptor;
class QPainter;

//! Main interface class for views representing MaskItems, Projections on graphics scene.

class BA_CORE_API_ IShape2DView : public QGraphicsObject
{
    Q_OBJECT

public:
    virtual int type() const { return MaskEditorHelper::IMASKVIEW; }

    IShape2DView();
    virtual ~IShape2DView();

    QRectF boundingRect() const;

    virtual void setParameterizedItem(SessionItem* item);
    virtual SessionItem* parameterizedItem();

    void setSceneAdaptor(const ISceneAdaptor* adaptor);

    virtual void addView(IShape2DView* childView, int row = 0);

protected slots:
    //! update visual appearance of view (triggered by ISceneAdaptor)
    virtual void update_view() = 0;
    virtual void onChangedX() {}
    virtual void onChangedY() {}
    virtual void onPropertyChange(const QString&) {}

protected:
    double par(const QString& property_name) const;
    qreal toSceneX(const QString& property_name) const;
    qreal toSceneX(qreal value) const;
    qreal toSceneY(const QString& property_name) const;
    qreal toSceneY(qreal value) const;

    //! convert scene coordinates to ColorMap plot coordinates
    qreal fromSceneX(qreal value) const;
    qreal fromSceneY(qreal value) const;
    void setBlockOnProperty(bool value);
    bool blockOnProperty() const;

    SessionItem* m_item;
    const ISceneAdaptor* m_adaptor;
    QRectF m_bounding_rect;
    bool m_block_on_property_change;

private:
    void onItemPropertyChange(const QString& propertyName);
};

#endif // BORNAGAIN_GUI_COREGUI_VIEWS_MASKWIDGETS_ISHAPE2DVIEW_H
