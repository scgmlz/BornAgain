// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/DetectorItems.cpp
//! @brief     Implements classes DetectorItems
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/coregui/Models/DetectorItems.h"
#include "Core/Detector/IDetector2D.h"
#include "Core/Detector/ResolutionFunction2DGaussian.h"
#include "GUI/coregui/Models/MaskItems.h"
#include "GUI/coregui/Models/ParameterTranslators.h"
#include "GUI/coregui/Models/ResolutionFunctionItems.h"
#include "GUI/coregui/Models/SessionItemUtils.h"
#include "GUI/coregui/Models/SessionModel.h"

using SessionItemUtils::GetVectorItem;

namespace
{
const QString res_func_group_label = "Type";
const QString analyzer_direction_tooltip = "Direction of the polarization analysis";
const QString analyzer_efficiency_tooltip = "Efficiency of the polarization analysis";
const QString analyzer_transmission_tooltip = "Total transmission of the polarization analysis";
} // namespace

const QString DetectorItem::T_MASKS = "Mask tag";
const QString DetectorItem::P_RESOLUTION_FUNCTION = "Resolution function";
const QString DetectorItem::P_ANALYZER_DIRECTION = "Analyzer direction";
const QString DetectorItem::P_ANALYZER_EFFICIENCY = QString::fromStdString("Efficiency");
const QString DetectorItem::P_ANALYZER_TOTAL_TRANSMISSION = QString::fromStdString("Transmission");

DetectorItem::DetectorItem(const QString& modelType) : SessionItem(modelType)
{
    registerTag(T_MASKS, 0, -1, QStringList() << "MaskContainer");
    setDefaultTag(T_MASKS);

    addGroupProperty(P_ANALYZER_DIRECTION, "Vector")->setToolTip(analyzer_direction_tooltip);
    addProperty(P_ANALYZER_EFFICIENCY, 0.0)
        ->setLimits(RealLimits::limitless())
        .setToolTip(analyzer_efficiency_tooltip);
    addProperty(P_ANALYZER_TOTAL_TRANSMISSION, 1.0)->setToolTip(analyzer_transmission_tooltip);

    QString additional_name = QString::fromStdString("Analyzer");
    addTranslator(VectorParameterTranslator(P_ANALYZER_DIRECTION, "Direction", {additional_name}));
    addTranslator(AddElementTranslator(P_ANALYZER_EFFICIENCY, additional_name));
    addTranslator(AddElementTranslator(P_ANALYZER_TOTAL_TRANSMISSION, additional_name));

    mapper()->setOnPropertyChange([this](const QString& name) {
        if (name == P_RESOLUTION_FUNCTION)
            update_resolution_function_tooltips();
    });
}

std::unique_ptr<IDetector2D> DetectorItem::createDetector() const
{
    auto result = createDomainDetector();
    addMasksToDomain(result.get());

    if (auto resFunc = createResolutionFunction())
        result->setResolutionFunction(*resFunc);

    kvector_t analyzer_dir = GetVectorItem(*this, P_ANALYZER_DIRECTION);
    double analyzer_eff = getItemValue(P_ANALYZER_EFFICIENCY).toDouble();
    double analyzer_total_trans = getItemValue(P_ANALYZER_TOTAL_TRANSMISSION).toDouble();
    if (analyzer_dir.mag() > 0.0)
        result->setAnalyzerProperties(analyzer_dir, analyzer_eff, analyzer_total_trans);

    return result;
}

void DetectorItem::clearMasks()
{
    if (auto maskContainer = maskContainerItem())
        delete takeRow(rowOfChild(maskContainer));
}

MaskContainerItem* DetectorItem::maskContainerItem() const
{
    return dynamic_cast<MaskContainerItem*>(getItem(T_MASKS));
}

void DetectorItem::createMaskContainer()
{
    if (!maskContainerItem())
        model()->insertNewItem("MaskContainer", this->index());
}

void DetectorItem::importMasks(const MaskContainerItem* maskContainer)
{
    clearMasks();

    if (maskContainer)
        model()->copyItem(maskContainer, this, T_MASKS);
}

void DetectorItem::register_resolution_function()
{
    auto item = addGroupProperty(P_RESOLUTION_FUNCTION, "Resolution function group");
    item->setDisplayName(res_func_group_label);
    item->setToolTip("Detector resolution function");
}

void DetectorItem::update_resolution_function_tooltips()
{
    auto& resfuncItem = groupItem<ResolutionFunctionItem>(DetectorItem::P_RESOLUTION_FUNCTION);

    if (resfuncItem.modelType() == "ResolutionFunction2DGaussian") {
        QString units = modelType() == "SphericalDetector" ? "deg" : "mm";

        resfuncItem.getItem(ResolutionFunction2DGaussianItem::P_SIGMA_X)
            ->setToolTip("Resolution along horizontal axis (in " + units + ")");
        resfuncItem.getItem(ResolutionFunction2DGaussianItem::P_SIGMA_Y)
            ->setToolTip("Resolution along vertical axis (in " + units + ")");
    }
}

std::unique_ptr<IResolutionFunction2D> DetectorItem::createResolutionFunction() const
{
    auto& resfuncItem = groupItem<ResolutionFunctionItem>(DetectorItem::P_RESOLUTION_FUNCTION);
    return resfuncItem.createResolutionFunction(axesToDomainUnitsFactor());
}

void DetectorItem::addMasksToDomain(IDetector2D* detector) const
{
    auto maskContainer = maskContainerItem();

    if (!maskContainer)
        return;

    const double scale = axesToDomainUnitsFactor();

    for (int i_row = maskContainer->children().size(); i_row > 0; --i_row) {
        if (auto maskItem = dynamic_cast<MaskItem*>(maskContainer->children().at(i_row - 1))) {

            if (maskItem->modelType() == "RegionOfInterest") {
                double xlow = scale * maskItem->getItemValue(RectangleItem::P_XLOW).toDouble();
                double ylow = scale * maskItem->getItemValue(RectangleItem::P_YLOW).toDouble();
                double xup = scale * maskItem->getItemValue(RectangleItem::P_XUP).toDouble();
                double yup = scale * maskItem->getItemValue(RectangleItem::P_YUP).toDouble();
                detector->setRegionOfInterest(xlow, ylow, xup, yup);

            } else {
                std::unique_ptr<IShape2D> shape(maskItem->createShape(scale));
                bool mask_value = maskItem->getItemValue(MaskItem::P_MASK_VALUE).toBool();
                detector->addMask(*shape, mask_value);
            }
        }
    }
}
