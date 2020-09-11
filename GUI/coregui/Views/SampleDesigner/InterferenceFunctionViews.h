// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/SampleDesigner/InterferenceFunctionViews.h
//! @brief     Defines classes InterferenceFunctionViews
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_VIEWS_SAMPLEDESIGNER_INTERFERENCEFUNCTIONVIEWS_H
#define BORNAGAIN_GUI_COREGUI_VIEWS_SAMPLEDESIGNER_INTERFERENCEFUNCTIONVIEWS_H

#include "GUI/coregui/Views/SampleDesigner/ConnectableView.h"

class BA_CORE_API_ InterferenceFunction1DLatticeView : public ConnectableView
{
    Q_OBJECT
public:
    InterferenceFunction1DLatticeView(QGraphicsItem* parent = nullptr);
    int type() const { return ViewTypes::INTERFERENCE_FUNCTION_1D_LATTICE; }
};

class BA_CORE_API_ InterferenceFunction2DLatticeView : public ConnectableView
{
    Q_OBJECT
public:
    InterferenceFunction2DLatticeView(QGraphicsItem* parent = nullptr);
    int type() const { return ViewTypes::INTERFERENCE_FUNCTION_2D_LATTICE; }
};

class BA_CORE_API_ InterferenceFunction2DParaCrystalView : public ConnectableView
{
    Q_OBJECT
public:
    InterferenceFunction2DParaCrystalView(QGraphicsItem* parent = nullptr);
    int type() const { return ViewTypes::INTERFERENCE_FUNCTION_2D_PARA; }
};

class BA_CORE_API_ InterferenceFunctionFinite2DLatticeView : public ConnectableView
{
    Q_OBJECT
public:
    InterferenceFunctionFinite2DLatticeView(QGraphicsItem* parent = nullptr);
    int type() const { return ViewTypes::INTERFERENCE_FUNCTION_FINITE_2D_LATTICE; }
};

class BA_CORE_API_ InterferenceFunctionHardDiskView : public ConnectableView
{
    Q_OBJECT
public:
    InterferenceFunctionHardDiskView(QGraphicsItem* parent = nullptr);
    int type() const { return ViewTypes::INTERFERENCE_FUNCTION_HARD_DISK; }
};

class BA_CORE_API_ InterferenceFunctionRadialParaCrystalView : public ConnectableView
{
    Q_OBJECT
public:
    InterferenceFunctionRadialParaCrystalView(QGraphicsItem* parent = nullptr);
    int type() const { return ViewTypes::INTERFERENCE_FUNCTION_RADIAL_PARA; }
};

#endif // BORNAGAIN_GUI_COREGUI_VIEWS_SAMPLEDESIGNER_INTERFERENCEFUNCTIONVIEWS_H
