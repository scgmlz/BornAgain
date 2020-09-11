// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/SampleDesigner/ParticleCoreShellView.cpp
//! @brief     Implements class ParticleCoreShellView
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/coregui/Views/SampleDesigner/ParticleCoreShellView.h"
#include "GUI/coregui/Models/ParticleCoreShellItem.h"
#include "GUI/coregui/Models/SessionItem.h"
#include "GUI/coregui/Views/SampleDesigner/DesignerHelper.h"
#include "GUI/coregui/utils/StyleUtils.h"

ParticleCoreShellView::ParticleCoreShellView(QGraphicsItem* parent) : ConnectableView(parent)
{
    setName("ParticleCoreShell");
    setColor(DesignerHelper::getDefaultParticleColor());
    setRectangle(DesignerHelper::getDefaultBoundingRect("ParticleCoreShell"));
    addPort("out", NodeEditorPort::OUTPUT, NodeEditorPort::FORM_FACTOR)
        ->setToolTip("Connect to the ParticleLayout");
    addPort("core", NodeEditorPort::INPUT, NodeEditorPort::FORM_FACTOR)
        ->setToolTip("Connect particle which will play the role of core.");
    addPort("shell", NodeEditorPort::INPUT, NodeEditorPort::FORM_FACTOR)
        ->setToolTip("Connect particle which will play the role of shell.");
    addPort("transformation", NodeEditorPort::INPUT, NodeEditorPort::TRANSFORMATION)
        ->setToolTip("Connect particle rotation to this port, if necessary");

    m_label_vspace = StyleUtils::SizeOfLetterM().height() * 3.0;
}

void ParticleCoreShellView::addView(IView* childView, int /* row */)
{
    int index = 0;
    if (this->getItem()->tagFromItem(childView->getItem()) == ParticleCoreShellItem::T_CORE) {
        index = 0;
    } else if (this->getItem()->tagFromItem(childView->getItem())
               == ParticleCoreShellItem::T_SHELL) {
        index = 1;
    } else {
        index = 2;
    }
    connectInputPort(dynamic_cast<ConnectableView*>(childView), index);
}
