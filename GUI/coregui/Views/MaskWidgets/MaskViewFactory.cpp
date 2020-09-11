// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/MaskWidgets/MaskViewFactory.cpp
//! @brief     Implements class MaskViewFactory
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/coregui/Views/MaskWidgets/MaskViewFactory.h"
#include "GUI/coregui/Models/SessionItem.h"
#include "GUI/coregui/Views/MaskWidgets/EllipseView.h"
#include "GUI/coregui/Views/MaskWidgets/IShape2DView.h"
#include "GUI/coregui/Views/MaskWidgets/IntensityDataView.h"
#include "GUI/coregui/Views/MaskWidgets/LineViews.h"
#include "GUI/coregui/Views/MaskWidgets/MaskAllView.h"
#include "GUI/coregui/Views/MaskWidgets/MaskContainerView.h"
#include "GUI/coregui/Views/MaskWidgets/PolygonPointView.h"
#include "GUI/coregui/Views/MaskWidgets/PolygonView.h"
#include "GUI/coregui/Views/MaskWidgets/RectangleView.h"
#include "GUI/coregui/Views/MaskWidgets/RegionOfInterestView.h"
#include "GUI/coregui/utils/GUIHelpers.h"

IShape2DView* MaskViewFactory::createMaskView(SessionItem* item, ISceneAdaptor* adaptor)
{
    IShape2DView* result(0);
    QString model_type = item->modelType();

    if (model_type == "MaskContainer") {
        result = new MaskContainerView();
    }

    else if (model_type == "ProjectionContainer") {
        result = new MaskContainerView();
    }

    else if (model_type == "RectangleMask") {
        result = new RectangleView();
    }

    else if (model_type == "PolygonMask") {
        result = new PolygonView();
    }

    else if (model_type == "PolygonPoint") {
        result = new PolygonPointView();
    }

    else if (model_type == "VerticalLineMask") {
        result = new VerticalLineView();
    }

    else if (model_type == "HorizontalLineMask") {
        result = new HorizontalLineView();
    }

    else if (model_type == "EllipseMask") {
        result = new EllipseView();
    }

    else if (model_type == "MaskAllMask") {
        result = new MaskAllView();
    }

    else if (model_type == "RegionOfInterest") {
        result = new RegionOfInterestView();
    }

    else {
        throw GUIHelpers::Error("MaskViewFactory::createSampleView() -> Error! "
                                "Can't create a view for "
                                + model_type);
    }

    result->setParameterizedItem(item);
    result->setSceneAdaptor(adaptor);

    return result;
}
