// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/InstrumentWidgets/GISASDetectorEditor.cpp
//! @brief     Implements class GISASDetectorEditor
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/coregui/Views/InstrumentWidgets/GISASDetectorEditor.h"
#include "GUI/coregui/Models/DetectorItems.h"
#include "GUI/coregui/Models/GroupItem.h"
#include "GUI/coregui/Models/InstrumentItems.h"
#include "GUI/coregui/Views/InstrumentWidgets/DetectorPresenter.h"
#include "GUI/coregui/Views/PropertyEditor/ComponentEditor.h"
#include <QVBoxLayout>

GISASDetectorEditor::GISASDetectorEditor(QWidget* parent)
    : SessionItemWidget(parent), m_detectorTypeEditor(new ComponentEditor(
                                     ComponentEditor::PlainWidget | ComponentEditor::W_NoChildren)),
      m_detectorPresenter(new DetectorPresenter)
{
    auto mainLayout = new QVBoxLayout;
    mainLayout->addWidget(m_detectorTypeEditor);
    mainLayout->addWidget(m_detectorPresenter);
    mainLayout->addStretch();
    setLayout(mainLayout);
}

void GISASDetectorEditor::subscribeToItem()
{
    currentItem()->mapper()->setOnPropertyChange(
        [this](const QString& name) {
            if (name == Instrument2DItem::P_DETECTOR)
                updateDetectorPresenter();
        },
        this);

    m_detectorTypeEditor->setItem(instrumentItem()->detectorGroup());
    updateDetectorPresenter();
}

void GISASDetectorEditor::unsubscribeFromItem()
{
    m_detectorTypeEditor->clearEditor();
}

Instrument2DItem* GISASDetectorEditor::instrumentItem()
{
    auto result = dynamic_cast<Instrument2DItem*>(currentItem());
    ASSERT(result);
    return result;
}

//! Shows detector editor corresponding to the currently selected detector in detectorGroup.

void GISASDetectorEditor::updateDetectorPresenter()
{
    m_detectorPresenter->setItem(instrumentItem()->detectorItem());
}
