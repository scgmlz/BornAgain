// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/SampleDesigner/ParticleView.h
//! @brief     Defines class ParticleView
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_VIEWS_SAMPLEDESIGNER_PARTICLEVIEW_H
#define BORNAGAIN_GUI_COREGUI_VIEWS_SAMPLEDESIGNER_PARTICLEVIEW_H

#include "GUI/coregui/Views/SampleDesigner/ConnectableView.h"
#include <QPixmap>

//! Class representing view of Particle item
class BA_CORE_API_ ParticleView : public ConnectableView
{
    Q_OBJECT

public:
    ParticleView(QGraphicsItem* parent = 0);

    int type() const { return ViewTypes::PARTICLE; }

    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);

    void onPropertyChange(const QString& propertyName);

    void addView(IView* childView, int row = 0); // to add Transformation

protected:
    void update_appearance();

private:
    void updatePixmap();
    void updateToolTip();

    QPixmap m_pixmap;
};

#endif // BORNAGAIN_GUI_COREGUI_VIEWS_SAMPLEDESIGNER_PARTICLEVIEW_H
