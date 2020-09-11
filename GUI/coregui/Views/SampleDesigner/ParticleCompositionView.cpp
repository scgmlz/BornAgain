// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/SampleDesigner/ParticleCompositionView.cpp
//! @brief     Implements class ParticleCompositionView
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/coregui/Views/SampleDesigner/ParticleCompositionView.h"
#include "GUI/coregui/Models/ParticleItem.h"
#include "GUI/coregui/Models/SessionItem.h"
#include "GUI/coregui/Views/SampleDesigner/DesignerHelper.h"
#include "GUI/coregui/utils/StyleUtils.h"

ParticleCompositionView::ParticleCompositionView(QGraphicsItem* parent) : ConnectableView(parent)
{
    setName("ParticleComposition");
    setColor(DesignerHelper::getDefaultParticleColor());
    setRectangle(DesignerHelper::getDefaultBoundingRect("ParticleCoreShell"));
    addPort("out", NodeEditorPort::OUTPUT, NodeEditorPort::FORM_FACTOR)
        ->setToolTip("Connect to the ParticleLayout");
    addPort("particles", NodeEditorPort::INPUT, NodeEditorPort::FORM_FACTOR)
        ->setToolTip("Connect particles");
    addPort("transformation", NodeEditorPort::INPUT, NodeEditorPort::TRANSFORMATION)
        ->setToolTip("Connect rotation to this port, if necessary");
    m_label_vspace = StyleUtils::SizeOfLetterM().height() * 3.0;
}

void ParticleCompositionView::addView(IView* childView, int /* row */)
{
    int index = 0;
    if (this->getItem()->tagFromItem(childView->getItem()) == ParticleItem::T_TRANSFORMATION)
        index = 1;
    connectInputPort(dynamic_cast<ConnectableView*>(childView), index);
}
