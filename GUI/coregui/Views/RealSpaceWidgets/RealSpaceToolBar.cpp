// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/RealSpaceWidgets/RealSpaceToolBar.cpp
//! @brief     Implements class RealSpaceWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "RealSpaceToolBar.h"
#include "mainwindow_constants.h"

#include <QCheckBox>
#include <QToolButton>

namespace
{
const double increaseLayerSizeScale = 1.25;
const double decreaseLayerSizeScale = 0.8;
}

RealSpaceToolBar::RealSpaceToolBar(QWidget* parent)
    : StyledToolBar(parent), m_defaultViewButton(new QToolButton),
      m_sideViewButton(new QToolButton), m_topViewButton(new QToolButton),
      m_lockViewCheckBox(new QCheckBox), m_increaseLayerSizeButton(new QToolButton),
      m_decreaseLayerSizeButton(new QToolButton),
      m_savePictureButton(new QToolButton)
{
    setMinimumSize(Constants::styled_toolbar_height, Constants::styled_toolbar_height);

    // Save image -- this first so it is available for smaller widget sizes
    m_savePictureButton->setText("Save Picture");
    m_savePictureButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    m_savePictureButton->setToolTip("Save 3D real space view as .png file");
    connect(m_savePictureButton, &QToolButton::clicked, this,
            [&]() { emit RealSpaceToolBar::savePictureAction(); });
    addWidget(m_savePictureButton);

    addSeparator();

    // Default View
    m_defaultViewButton->setText("Default View");
    // m_defaultViewButton->setIcon(QIcon(":/SampleDesigner/images/toolbar_recycle.png"));
    m_defaultViewButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    m_defaultViewButton->setToolTip("Reset view and zoom level to default");
    connect(m_defaultViewButton, &QToolButton::clicked, this, &RealSpaceToolBar::defaultViewAction);
    addWidget(m_defaultViewButton);

    addSeparator();

    // Side View
    m_sideViewButton->setText("Side View");
    // m_sideViewButton->setIcon(QIcon(":/SampleDesigner/images/toolbar_recycle.png"));
    m_sideViewButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    m_sideViewButton->setToolTip("View sample from the side at current zoom level");
    connect(m_sideViewButton, &QToolButton::clicked, this, &RealSpaceToolBar::sideViewAction);
    addWidget(m_sideViewButton);

    addSeparator();

    // Top View
    m_topViewButton->setText("Top View");
    // m_topViewButton->setIcon(QIcon(":/SampleDesigner/images/toolbar_recycle.png"));
    m_topViewButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    m_topViewButton->setToolTip("View sample from the top at current zoom level");
    connect(m_topViewButton, &QToolButton::clicked, this, &RealSpaceToolBar::topViewAction);
    addWidget(m_topViewButton);

    addSeparator();

    // Lock View
    m_lockViewCheckBox->setText("Lock View");
    m_lockViewCheckBox->setToolTip("Lock/unlock current sample selection");
    m_lockViewCheckBox->setCheckable(true);
    connect(m_lockViewCheckBox, &QCheckBox::clicked, this,
            [&]() { emit RealSpaceToolBar::lockViewAction(m_lockViewCheckBox->isChecked()); });
    addWidget(m_lockViewCheckBox);

    addSeparator();

    // Increase layer size
    m_increaseLayerSizeButton->setText("Enlarge");
    // m_increaseLayerSizeButton->setIcon(QIcon(":/SampleDesigner/images/toolbar_recycle.png"));
    m_increaseLayerSizeButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    m_increaseLayerSizeButton->setToolTip("Increase layer size");
    connect(m_increaseLayerSizeButton, &QToolButton::clicked, this,
            [&]() { emit RealSpaceToolBar::changeLayerSizeAction(increaseLayerSizeScale); });
    addWidget(m_increaseLayerSizeButton);

    addSeparator();

    // Decrease layer size
    m_decreaseLayerSizeButton->setText("Reduce");
    // m_decreaseLayerSizeButton->setIcon(QIcon(":/SampleDesigner/images/toolbar_recycle.png"));
    m_decreaseLayerSizeButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    m_decreaseLayerSizeButton->setToolTip("Decrease layer size");
    connect(m_decreaseLayerSizeButton, &QToolButton::clicked, this,
            [&]() { emit RealSpaceToolBar::changeLayerSizeAction(decreaseLayerSizeScale); });
    addWidget(m_decreaseLayerSizeButton);

    addSeparator();

}
