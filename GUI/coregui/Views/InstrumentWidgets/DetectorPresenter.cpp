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

#include "GUI/coregui/Views/InstrumentWidgets/DetectorPresenter.h"
#include "GUI/coregui/Models/SessionItem.h"
#include "GUI/coregui/Views/InstrumentWidgets/RectangularDetectorEditor.h"
#include "GUI/coregui/Views/InstrumentWidgets/SphericalDetectorEditor.h"
#include "GUI/coregui/utils/GUIHelpers.h"

namespace
{
const QString SphericalDetectorPresentation = "Spherical";
const QString RectangularDetectorPresentation = "Rectangular";
} // namespace

DetectorPresenter::DetectorPresenter(QWidget* parent) : ItemComboWidget(parent)
{
    registerWidget(SphericalDetectorPresentation, create_new<SphericalDetectorEditor>);
    registerWidget(RectangularDetectorPresentation, create_new<RectangularDetectorEditor>);
    setToolBarVisible(false);
}

QString DetectorPresenter::itemPresentation() const
{
    if (!currentItem())
        return {};

    if (currentItem()->modelType() == "SphericalDetector")
        return SphericalDetectorPresentation;
    else if (currentItem()->modelType() == "RectangularDetector")
        return RectangularDetectorPresentation;
    else
        throw GUIHelpers::Error("DetectorPresenter::itemPresentation() -> Error. Wrong item "
                                "type '"
                                + currentItem()->modelType() + "'");
}

QStringList DetectorPresenter::activePresentationList(SessionItem* item)
{
    Q_UNUSED(item);
    return QStringList() << SphericalDetectorPresentation << RectangularDetectorPresentation;
}
