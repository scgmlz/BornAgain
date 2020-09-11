// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/ImportDataWidgets/RealDataPresenter.cpp
//! @brief     Implements class RealDataPresenter
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/coregui/Views/ImportDataWidgets/RealDataPresenter.h"
#include "Core/Basics/Assert.h"
#include "GUI/coregui/Models/RealDataItem.h"
#include "GUI/coregui/Views/ImportDataWidgets/RealDataMaskWidget.h"
#include "GUI/coregui/Views/IntensityDataWidgets/IntensityDataProjectionsWidget.h"
#include "GUI/coregui/Views/IntensityDataWidgets/IntensityDataWidget.h"
#include "GUI/coregui/Views/SpecularDataWidgets/SpecularDataWidget.h"
#include "GUI/coregui/utils/GUIHelpers.h"
#include <QAction>

RealDataPresenter::RealDataPresenter(QWidget* parent) : ItemComboWidget(parent)
{
    registerWidget("Color Map", create_new<IntensityDataWidget>);
    registerWidget("Projections", create_new<IntensityDataProjectionsWidget>);
    registerWidget("Mask Editor", create_new<RealDataMaskWidget>);
    registerWidget("Reflectometry", create_new<SpecularDataWidget>);
}

QList<QAction*> RealDataPresenter::actionList()
{
    return QList<QAction*>();
}

QStringList RealDataPresenter::activePresentationList(SessionItem* item)
{
    ASSERT(item && dynamic_cast<RealDataItem*>(item));
    const auto& underlying_data_model = dynamic_cast<RealDataItem*>(item)->underlyingDataModel();

    QStringList result;
    if (underlying_data_model == "IntensityData")
        result << "Color Map"
               << "Projections"
               << "Mask Editor";
    else if (underlying_data_model == "SpecularData")
        result << "Reflectometry";
    else
        throw GUIHelpers::Error(
            "Error in RealDataPresenter::activePresentationList: unsupported data type");
    return result;
}
