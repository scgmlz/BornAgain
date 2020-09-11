// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/SampleDesigner/DesignerHelper.cpp
//! @brief     Implements class DesignerHelper
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/coregui/Views/SampleDesigner/DesignerHelper.h"
#include "GUI/coregui/utils/StyleUtils.h"
#include <QPainter>
#include <QtGlobal>
#include <cmath>
#include <iostream>

namespace
{
double m_current_zoom_level = 1.0;
}

QGradient DesignerHelper::getLayerGradient(const QColor& color, const QRectF& rect)
{
    QColor c = color;
    c.setAlpha(160);
    QLinearGradient result(rect.topLeft(), rect.bottomRight());
#if QT_VERSION >= QT_VERSION_CHECK(5, 13, 0)
    result.setColorAt(0, c.darker(150));
    result.setColorAt(0.5, c.lighter(200));
    result.setColorAt(1, c.darker(150));
#else
    result.setColorAt(0, c.dark(150));
    result.setColorAt(0.5, c.light(200));
    result.setColorAt(1, c.dark(150));
#endif
    return std::move(result);
}

QGradient DesignerHelper::getDecorationGradient(const QColor& color, const QRectF& rect)
{
    QColor c = color;
    // c.setAlpha(200);
    QLinearGradient result(rect.x() + rect.width() / 2, rect.y(), rect.x() + rect.width() / 2,
                           rect.y() + rect.height());
    result.setColorAt(0, c);
    result.setColorAt(0.5, c.lighter(150));
    result.setColorAt(1, c);
    return std::move(result);
}

QPixmap DesignerHelper::getSceneBackground()
{
    const int size = 10;
    QPixmap result(size, size);
    result.fill(QColor(250, 250, 250));
    QPainter tilePainter(&result);
    QColor color(220, 220, 220);
    tilePainter.fillRect(0.0, 0.0, 2, 2, color);
    tilePainter.end();

    return result;
}

QPixmap DesignerHelper::getPixmapLayer()
{
    QRect rect(0, 0, layerWidth(), layerHeight());
    QPixmap pixmap(rect.width() + 1, rect.height() + 1);
    pixmap.fill(Qt::transparent);
    QPainter painter(&pixmap);
    painter.setPen(Qt::black);
    painter.setBrush(getLayerGradient(Qt::green, rect));
    painter.drawRect(rect);
    return pixmap;
}

QPixmap DesignerHelper::getPixmapMultiLayer()
{
    auto rect = getDefaultMultiLayerRect();
    QPixmap pixmap(rect.width() + 1, rect.height() + 1);
    pixmap.fill(Qt::transparent);
    QPainter painter(&pixmap);
    painter.setPen(Qt::black);
    painter.setBrush(getLayerGradient(QColor(75, 157, 249), rect));
    painter.drawRect(rect);
    painter.setPen(Qt::DashLine);
    painter.drawLine(0, layerHeight() * 0.3, rect.width(), layerHeight() * 0.3);
    painter.drawLine(0, layerHeight() * 0.6, rect.width(), layerHeight() * 0.6);
    return pixmap;
}

QPixmap DesignerHelper::getPixmapParticleLayout()
{
    auto rect = getParticleLayoutBoundingRect();
    QPixmap pixmap(rect.width() + 1, rect.height() + 1);
    pixmap.fill(Qt::transparent);
    QPainter painter(&pixmap);
    painter.setPen(Qt::black);
    painter.setBrush(getDecorationGradient(QColor(135, 206, 50), rect));
    painter.drawRoundedRect(rect, 3, 3);
    return pixmap;
}

QPixmap DesignerHelper::getPixmapInterferenceFunction()
{
    auto rect = getInterferenceFunctionBoundingRect();
    QPixmap pixmap(rect.width() + 1, rect.height() + 1);
    pixmap.fill(Qt::transparent);
    QPainter painter(&pixmap);
    painter.setPen(Qt::black);
    painter.setBrush(getDecorationGradient(Qt::lightGray, rect));
    painter.drawRoundedRect(rect, 3, 3);
    return pixmap;
}

QPixmap DesignerHelper::getPixmapParticle()
{
    auto rect = getParticleBoundingRect();
    QPixmap pixmap(rect.width() + 1, rect.height() + 1);
    pixmap.fill(Qt::transparent);
    QPainter painter(&pixmap);
    painter.setPen(Qt::black);
    painter.setBrush(getDecorationGradient(getDefaultParticleColor(), rect));
    painter.drawRoundedRect(rect, 5, 5);
    return pixmap;
}

QColor DesignerHelper::getRandomColor()
{
    return QColor(qrand() % 256, qrand() % 256, qrand() % 256);
}

bool DesignerHelper::sort_layers(QGraphicsItem* left, QGraphicsItem* right)
{
    return left->y() < right->y();
}

// non-linear conversion of layer's thickness in nanometers to screen size to have reasonable
// graphics representation
int DesignerHelper::nanometerToScreen(double nanometer)
{
    const int ymin(layerHeight());
    const int ymax(500);
    int result(ymin);
    if (nanometer > 0)
        result = qBound(ymin, ymin + (int)std::pow(nanometer, 0.9), ymax);
    return result;
}

QRectF DesignerHelper::getDefaultBoundingRect(const QString& name)
{
    if (name == "MultiLayer") {
        return getDefaultMultiLayerRect();
    } else if (name == "Layer") {
        return QRectF(0, 0, layerWidth(), layerHeight());
    } else if (name == "ParticleLayout") {
        return getParticleLayoutBoundingRect();
    } else if (name == "Rotation") {
        return getTransformationBoundingRect();
    } else if (name.startsWith("FormFactor") || name == "Particle" || name == "ParticleCoreShell"
               || name == "ParticleDistribution") {
        return getParticleBoundingRect();
    } else if (name.startsWith("Interference")) {
        return getInterferenceFunctionBoundingRect();
    } else {
        return QRectF(0, 0, 50, 50);
    }
}

QColor DesignerHelper::getDefaultColor(const QString& name)
{
    if (name == "MultiLayer") {
        // return QColor(Qt::blue);
        return QColor(51, 116, 255);
    } else if (name == "Layer") {
        // return QColor(Qt::green);
        return QColor(26, 156, 9);
    } else if (name == "ParticleLayout") {
        return QColor(135, 206, 50);
    } else if (name.startsWith("FormFactor") || name == "Particle" || name == "ParticleCoreShell") {
        return QColor(210, 223, 237);
    } else if (name.startsWith("InterferenceFunction")) {
        return QColor(255, 236, 139);
    } else if (name == "Transparant red") {
        return QColor(0xFF, 0, 0, 0x80);
    } else if (name == "Transparant blue") {
        return QColor(0, 0, 0xFF, 0x80);
    } else {
        return QColor(Qt::lightGray);
    }
}

QPixmap DesignerHelper::getMimePixmap(const QString& name)
{
    QRectF default_rect = getDefaultBoundingRect(name);
    QRectF mime_rect(0, 0, default_rect.width() * m_current_zoom_level,
                     default_rect.height() * m_current_zoom_level);

    QPixmap pixmap(mime_rect.width() + 1, mime_rect.height() + 1);
    pixmap.fill(Qt::transparent);
    QPainter painter(&pixmap);
    painter.setPen(Qt::black);
    painter.setBrush(getDecorationGradient(getDefaultColor(name), mime_rect));
    painter.drawRoundedRect(mime_rect, 1, 1);
    return pixmap;
}

int DesignerHelper::getHeaderFontSize()
{
    return StyleUtils::SystemPointSize() * 1.5;
}

int DesignerHelper::layerWidth()
{
    return StyleUtils::SizeOfLetterM().width() * 18;
}

int DesignerHelper::layerHeight()
{
    return StyleUtils::SizeOfLetterM().height() * 2;
}

QColor DesignerHelper::getDefaultLayerColor()
{
    return QColor(Qt::lightGray);
}

QRectF DesignerHelper::getDefaultMultiLayerRect()
{
    return QRectF(0, 0, layerWidth() * 1.15, layerHeight());
}

QRectF DesignerHelper::getParticleLayoutBoundingRect()
{
    return QRectF(0, 0, layerHeight() * 3.5, layerHeight() * 4.5);
}

QRectF DesignerHelper::getInterferenceFunctionBoundingRect()
{
    return QRectF(0, 0, layerHeight() * 4.5, layerHeight() * 4);
}

QColor DesignerHelper::getDefaultParticleColor()
{
    return QColor(210, 223, 237);
}

QRectF DesignerHelper::getParticleBoundingRect()
{
    return QRectF(0, 0, layerHeight() * 3.5, layerHeight() * 4);
}

QColor DesignerHelper::getDefaultTransformationColor()
{
    return QColor(145, 50, 220);
}

QRectF DesignerHelper::getTransformationBoundingRect()
{
    return QRectF(0, 0, layerHeight() * 4, layerHeight() * 2);
}

QColor DesignerHelper::getDefaultMaterialColor()
{
    return QColor(qrand() % 256, qrand() % 256, qrand() % 256);
}

int DesignerHelper::getSectionFontSize()
{
    return StyleUtils::SystemPointSize() * 1.2;
}

int DesignerHelper::getLabelFontSize()
{
    return StyleUtils::SystemPointSize() * 0.9;
}

int DesignerHelper::getPortFontSize()
{
    return StyleUtils::SystemPointSize() * 0.7;
}

int DesignerHelper::getPythonEditorFontSize()
{
    return StyleUtils::SystemPointSize();
}
