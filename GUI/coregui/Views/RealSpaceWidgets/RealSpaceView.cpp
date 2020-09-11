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

#include "GUI/coregui/Views/RealSpaceWidgets/RealSpaceView.h"
#include "GUI/ba3d/widget.h"
#include "GUI/coregui/Views/RealSpaceWidgets/RealSpaceModel.h"
#include <QVBoxLayout>

RealSpaceView::RealSpaceView(QWidget* parent) : QWidget(parent), m_3dview(new RealSpace::Widget3D)
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

void RealSpaceView::sideView()
{
    m_3dview->sideView();
}

void RealSpaceView::topView()
{
    m_3dview->topView();
}

RealSpace::Camera& RealSpaceView::getCamera()
{
    return m_3dview->cam();
}
