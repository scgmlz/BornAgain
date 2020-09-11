// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/SampleDesigner/ParticleView.cpp
//! @brief     Implements class ParticleView
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/coregui/Views/SampleDesigner/ParticleView.h"
#include "GUI/coregui/Models/FormFactorItems.h"
#include "GUI/coregui/Models/GroupItem.h"
#include "GUI/coregui/Models/ParticleItem.h"
#include "GUI/coregui/Views/SampleDesigner/DesignerHelper.h"
#include "GUI/coregui/utils/GUIHelpers.h"
#include "GUI/coregui/utils/StyleUtils.h"
#include <QObject>
#include <QPainter>
#include <QStyleOptionGraphicsItem>

ParticleView::ParticleView(QGraphicsItem* parent) : ConnectableView(parent)
{
    setName("Particle");
    setColor(DesignerHelper::getDefaultParticleColor());
    setRectangle(DesignerHelper::getParticleBoundingRect());
    addPort("out", NodeEditorPort::OUTPUT, NodeEditorPort::FORM_FACTOR)
        ->setToolTip("Connect to the ParticleLayout");
    addPort("transformation", NodeEditorPort::INPUT, NodeEditorPort::TRANSFORMATION)
        ->setToolTip("Connect particle rotation to this port, if necessary");
    m_label_vspace = StyleUtils::SizeOfLetterM().height() * 3.0;
}

void ParticleView::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    Q_UNUSED(widget);
    painter->setRenderHint(QPainter::SmoothPixmapTransform);
    painter->setRenderHint(QPainter::Antialiasing);

    painter->setPen(Qt::gray);
    if (option->state & (QStyle::State_Selected | QStyle::State_HasFocus)) {
        painter->setPen(Qt::DashLine);
    }

    painter->setBrush(DesignerHelper::getDecorationGradient(m_color, getRectangle()));
    painter->drawRoundedRect(getRectangle(), m_roundpar, m_roundpar);

    if (m_label.isEmpty())
        return;

    painter->setPen(Qt::black);
    double width = getRectangle().width() * 0.9;
    double yoffset = 5; // space above the label
    // double height = m_label_vspace - yoffset;
    double height = 20;
    QFont serifFont("Monospace", DesignerHelper::getLabelFontSize(), QFont::Normal);
    painter->setFont(serifFont);
    QRectF textRect(getRectangle().x() + (getRectangle().width() - width) / 2.,
                    getRectangle().y() + yoffset, width, height);
    painter->drawText(textRect, Qt::AlignCenter, m_label);

    QRectF target(getRectangle().width() / 2 - 16, 25, 32, 32);
    painter->drawPixmap(target, m_pixmap, QRectF(0.0, 0.0, m_pixmap.width(), m_pixmap.height()));
    //    painter->drawImage(target, m_pixmap);
}

void ParticleView::onPropertyChange(const QString& propertyName)
{
    if (propertyName == ParticleItem::P_FORM_FACTOR)
        update_appearance();

    IView::onPropertyChange(propertyName);
}

void ParticleView::addView(IView* childView, int /*row*/)
{
    if (childView->type() == ViewTypes::TRANSFORMATION) {
        connectInputPort(dynamic_cast<ConnectableView*>(childView), 0);
    } else {
        throw GUIHelpers::Error("ParticleView::addView() -> Error. Unknown view");
    }
}

void ParticleView::update_appearance()
{
    updatePixmap();
    updateToolTip();
    ConnectableView::update_appearance();
}

void ParticleView::updatePixmap()
{
    if (!getItem())
        return;

    QString ff_type = getItem()->item<GroupItem>(ParticleItem::P_FORM_FACTOR).currentType();
    QString filename = QString(":/widgetbox/images/ff_%1_64x64.png").arg(ff_type);
    m_pixmap = QPixmap(filename);
}

void ParticleView::updateToolTip()
{
    if (!getItem())
        return;

    auto ffItem = getItem()->item<GroupItem>(ParticleItem::P_FORM_FACTOR).currentItem();
    setToolTip(ffItem->toolTip());
}
