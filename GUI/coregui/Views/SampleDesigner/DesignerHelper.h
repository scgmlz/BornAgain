// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/SampleDesigner/DesignerHelper.h
//! @brief     Defines class DesignerHelper
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_VIEWS_SAMPLEDESIGNER_DESIGNERHELPER_H
#define BORNAGAIN_GUI_COREGUI_VIEWS_SAMPLEDESIGNER_DESIGNERHELPER_H

#include "Wrap/WinDllMacros.h"
#include <QColor>
#include <QGradient>
#include <QGraphicsItem>
#include <QRect>

//! collection of static methods with SampleDesigner geometry settings
class BA_CORE_API_ DesignerHelper
{
public:
    static int layerWidth();
    static int layerHeight();
    static QColor getDefaultLayerColor();

    static QRectF getDefaultMultiLayerRect();

    static QRectF getParticleLayoutBoundingRect();

    static QRectF getInterferenceFunctionBoundingRect();

    static QColor getDefaultParticleColor();
    static QRectF getParticleBoundingRect();

    static QColor getDefaultTransformationColor();
    static QRectF getTransformationBoundingRect();

    static QColor getDefaultMaterialColor();

    static QGradient getLayerGradient(const QColor& color, const QRectF& rect);
    static QGradient getDecorationGradient(const QColor& color, const QRectF& rect);

    static QPixmap getSceneBackground();
    static QPixmap getPixmapLayer();
    static QPixmap getPixmapMultiLayer();
    static QPixmap getPixmapParticleLayout();
    static QPixmap getPixmapInterferenceFunction();
    static QPixmap getPixmapParticle();

    static QColor getRandomColor();

    //! sort graphics item according they y-coordinate
    static bool sort_layers(QGraphicsItem* left, QGraphicsItem* right);

    //! non-linear conversion of layer's thickness in nanometers to screen size
    //! to have reasonable graphics representation of layer in the form of QRect
    static int nanometerToScreen(double nanometer);

    //! returns default bounding rectangle for given IvView name
    static QRectF getDefaultBoundingRect(const QString& name);

    //! returns default color for IView with given name
    static QColor getDefaultColor(const QString& name);

    //! returns Mime pixmap for givew IView name
    static QPixmap getMimePixmap(const QString& name);

    //! returns system dependent font size
    static int getHeaderFontSize();
    static int getSectionFontSize();
    static int getLabelFontSize();
    static int getPortFontSize();
    static int getPythonEditorFontSize();
};

#endif // BORNAGAIN_GUI_COREGUI_VIEWS_SAMPLEDESIGNER_DESIGNERHELPER_H
