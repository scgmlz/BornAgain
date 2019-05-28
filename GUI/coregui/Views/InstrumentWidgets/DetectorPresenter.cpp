// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/InstrumentWidgets/DetectorPresenter.cpp
//! @brief     Implements class DetectorPresenter
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "DetectorPresenter.h"
#include "SphericalDetectorEditor.h"
#include "FlatDetectorEditor.h"
#include "SessionItem.h"
#include "GUIHelpers.h"

namespace {
const QString SphericalDetectorPresentation = "Spherical";
const QString FlatDetectorPresentation = "Flat";
}

DetectorPresenter::DetectorPresenter(QWidget* parent)
    : ItemComboWidget(parent)
{
    registerWidget(SphericalDetectorPresentation, create_new<SphericalDetectorEditor>);
    registerWidget(FlatDetectorPresentation, create_new<FlatDetectorEditor>);
    setToolBarVisible(false);
}

QString DetectorPresenter::itemPresentation() const
{
    if(!currentItem())
        return {};

    if (currentItem()->modelType() == Constants::SphericalDetectorType)
        return SphericalDetectorPresentation;
    else if (currentItem()->modelType() == Constants::FlatDetectorType)
        return FlatDetectorPresentation;
    else
        throw GUIHelpers::Error("DetectorPresenter::itemPresentation() -> Error. Wrong item "
                                "type '"+currentItem()->modelType()+"'");
}

QStringList DetectorPresenter::activePresentationList(SessionItem* item)
{
    Q_UNUSED(item);
    return QStringList() << SphericalDetectorPresentation << FlatDetectorPresentation;
}
