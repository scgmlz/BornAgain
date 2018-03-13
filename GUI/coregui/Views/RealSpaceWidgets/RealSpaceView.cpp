// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/RealSpaceWidgets/RealSpaceView.cpp
//! @brief     Implements class RealSpaceView
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "RealSpaceView.h"
#include "RealSpaceModel.h"
#include <ba3d/widget.h>
#include <QVBoxLayout>

RealSpaceView::RealSpaceView(QWidget* parent)
    : QWidget(parent)
    , m_3dview(new RealSpace::Widget3D)
{
    QVBoxLayout* layout = new QVBoxLayout;
    layout->setMargin(0);
    layout->setSpacing(0);

    layout->addWidget(m_3dview);
    setLayout(layout);
}

void RealSpaceView::setModel(RealSpaceModel* model)
{
    m_3dview->setModel(model);
}

void RealSpaceView::defaultView()
{
    m_3dview->defaultView();
}

void RealSpaceView::edgeView()
{
    m_3dview->edgeView();
}

void RealSpaceView::faceView()
{
    m_3dview->faceView();
}
