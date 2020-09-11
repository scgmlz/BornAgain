// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/SampleDesigner/ParticleDistributionView.cpp
//! @brief     Implements class ParticleDistributionView
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/coregui/Views/SampleDesigner/ParticleDistributionView.h"
#include "GUI/coregui/Models/SessionItem.h"
#include "GUI/coregui/Views/SampleDesigner/DesignerHelper.h"
#include "GUI/coregui/utils/StyleUtils.h"

ParticleDistributionView::ParticleDistributionView(QGraphicsItem* parent) : ConnectableView(parent)
{
    setName("ParticleDistribution");
    setColor(DesignerHelper::getDefaultParticleColor());
    setRectangle(DesignerHelper::getDefaultBoundingRect("ParticleDistribution"));
    addPort("out", NodeEditorPort::OUTPUT, NodeEditorPort::FORM_FACTOR)
        ->setToolTip("Connect to the ParticleLayout");
    addPort("particle", NodeEditorPort::INPUT, NodeEditorPort::FORM_FACTOR)
        ->setToolTip("Connect particle to this port. It will be a prototype \n"
                     "for parametric distribution.");

    m_label_vspace = StyleUtils::SizeOfLetterM().height() * 3.0;
}

void ParticleDistributionView::addView(IView* childView, int /* row */)
{
    connectInputPort(dynamic_cast<ConnectableView*>(childView), 0);
}
