#include "ISampleViewAligner.h"
#include "ISampleView.h"
#include "LayerView.h"
#include "MultiLayerView.h"
#include "FormFactorView.h"
#include "InterferenceFunctionView.h"
#include "ParticleDecorationView.h"
#include <iostream>


//! makes alignment of MultiLayer wil all nodes connected
//!
//! we run over all items to know which item is located at which level
//! here level 0 - is MultiLayer, level 1 - Layers, level 2 - decorations,
//! level 3 - formfactors and interference etc...
void ISampleViewAligner::makeAlign(MultiLayerView *multi_layer)
{
    // run over all items to know which item is located at which level
    multi_layer->accept(this);

    QPointF start(multi_layer->pos().x(), multi_layer->pos().y());
    for(int i_level = 2; i_level <= getMaximumLevelNumber(); ++i_level) {
        QList<ISampleView *> items = m_views.values(i_level);
        start = placeItems(items, start);
    }
}


int ISampleViewAligner::getMaximumLevelNumber()
{
    QList<int> keys = m_views.keys();
    qSort(keys.begin(), keys.end(), qGreater<int>());
    return keys[0];
}


//! place given items using given reference point
QPointF ISampleViewAligner::placeItems(const QList<ISampleView *> &items, QPointF reference)
{
    const double size_factor = 1.5;
    qreal dy = size_factor*getTotalVerticalSpace(items);
    qreal dx = size_factor*getMaximumHorizontalSpace(items);
    reference.setX(reference.x() - dx );
    for(int i=0; i<items.size(); ++i) {
        QPointF pos = reference;
        pos.setY(pos.y() - i*dy/items.size());
        items.at(i)->setPos(pos);
    }
    return reference;
}


qreal ISampleViewAligner::getTotalVerticalSpace(const QList<ISampleView *> &items)
{
    qreal result = 0;
    for(int i=0; i<items.size(); ++i) {
        result += items.at(i)->boundingRect().height();
    }
    return result;
}


qreal ISampleViewAligner::getMaximumHorizontalSpace(const QList<ISampleView *> &items)
{
    qreal result = 0;
    for(int i=0; i<items.size(); ++i) {
        qreal width = items.at(i)->boundingRect().width();
        if(width > result) result = width;
    }
    return result;
}


void ISampleViewAligner::visit(ISampleView *view)
{
    Q_ASSERT(view);
    std::cout << get_indent() << "ViewVisitor(ISampleView ) " << m_level << " " << view->type() << " " << std::endl;
}


void ISampleViewAligner::visit(ISampleRectView *view)
{
    Q_ASSERT(view);
    std::cout << get_indent() << "ViewVisitor(ISampleRectView ) " << m_level << " " << view->type() << " " << view->getName().toStdString() << std::endl;
}


void ISampleViewAligner::visit(LayerView *view)
{
    Q_ASSERT(view);
    std::cout << get_indent() << "ViewVisitor(LayerView ) " << m_level << " " << view->type() << " " << view->getName().toStdString() << std::endl;
    m_views.insertMulti(m_level, view);

    goForward();
    foreach(ISampleRectView *item, view->getConnectedInputItems()) {
        std::cout << "Layer children xxx " << item->type() << std::endl;
        item->accept(this);
    }
    goBack();
}


void ISampleViewAligner::visit(MultiLayerView *view)
{
    Q_ASSERT(view);
    std::cout << get_indent() << "ViewVisitor(MultiLayerView ) " << m_level << " " << view->type() << " " << view->getName().toStdString() << std::endl;
    m_views.insertMulti(m_level, view);

    goForward();
    foreach(QGraphicsItem *item, view->childItems()) {
        ISampleView *layer = dynamic_cast<ISampleView *>(item);
        if(layer) layer->accept(this);
    }
    goBack();
}


void ISampleViewAligner::visit(FormFactorView *view)
{
    Q_ASSERT(view);
    std::cout << get_indent() << "ViewVisitor(FormFactorView ) " << m_level << " " << view->type() << " " << view->getName().toStdString() << std::endl;
    m_views.insertMulti(m_level, view);
}


void ISampleViewAligner::visit(FormFactorFullSphereView *view)
{
    Q_ASSERT(view);
    std::cout << get_indent() << "ViewVisitor(FormFactorFullSphereView ) " << m_level << " " << view->type() << " " << view->getName().toStdString() << std::endl;
    m_views.insertMulti(m_level, view);
}


void ISampleViewAligner::visit(FormFactorPyramidView *view)
{
    Q_ASSERT(view);
    std::cout << get_indent() << "ViewVisitor(FormFactorPyramidView ) " << m_level << " " << view->type() << " " << view->getName().toStdString() << std::endl;
    m_views.insertMulti(m_level, view);
}


void ISampleViewAligner::visit(FormFactorPrism3View *view)
{
    Q_ASSERT(view);
    std::cout << get_indent() << "ViewVisitor(FormFactorPrism3View ) " << m_level << " " << view->type() << " " << view->getName().toStdString() << std::endl;
    m_views.insertMulti(m_level, view);
}


void ISampleViewAligner::visit(FormFactorCylinderView *view)
{
    Q_ASSERT(view);
    std::cout << get_indent() << "ViewVisitor(FormFactorCylinderView ) " << m_level << " " << view->type() << " " << view->getName().toStdString() << std::endl;
    m_views.insertMulti(m_level, view);
}


void ISampleViewAligner::visit(InterferenceFunctionView *view)
{
    Q_ASSERT(view);
    std::cout << get_indent() << "ViewVisitor(InterferenceFunctionView ) " << m_level << " " << view->type() << " " << view->getName().toStdString() << std::endl;
    m_views.insertMulti(m_level, view);
}


void ISampleViewAligner::visit(InterferenceFunction1DParaCrystalView *view)
{
    Q_ASSERT(view);
    std::cout << get_indent() << "ViewVisitor(InterferenceFunction1DParaCrystalView ) " << m_level << " " << view->type() << " " << view->getName().toStdString() << std::endl;
    m_views.insertMulti(m_level, view);
}


void ISampleViewAligner::visit(ParticleDecorationView *view)
{
    Q_ASSERT(view);
    std::cout << get_indent() << "ViewVisitor(ParticleDecorationView ) " << m_level << " " << view->type() << " " << view->getName().toStdString() << std::endl;

    m_views.insertMulti(m_level, view);

    goForward();
    foreach(ISampleRectView *item, view->getConnectedInputItems()) {
        item->accept(this);
    }
    goBack();
}

