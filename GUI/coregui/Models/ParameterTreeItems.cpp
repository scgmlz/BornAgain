// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/ParameterTreeItems.cpp
//! @brief     Implements classes for ParameterTreeItems
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "ParameterTreeItems.h"
#include "BeamItem.h"
#include "DistributionItems.h"
#include "FitParameterHelper.h"
#include "InstrumentItems.h"
#include "ModelPath.h"
#include "RectangularDetectorItem.h"
#include "SessionModel.h"
#include "SphericalDetectorItem.h"

namespace {
bool containsNames(const QString& text, const QStringList& names);
}

// ----------------------------------------------------------------------------

ParameterLabelItem::ParameterLabelItem()
    : SessionItem(Constants::ParameterLabelType)
{
    const QString T_CHILDREN = "children tag";
    registerTag(T_CHILDREN, 0, -1, QStringList()
                << Constants::ParameterLabelType << Constants::ParameterType);
    setDefaultTag(T_CHILDREN);
}

const QString ParameterItem::P_LINK = "Link";
const QString ParameterItem::P_BACKUP = "Backup";
const QString ParameterItem::P_DOMAIN = "Domain";
ParameterItem::ParameterItem()
    : SessionItem(Constants::ParameterType)
{
    // Link to original PropertyItem in one of components of MultiLayerItem or InstrumentItem
    addProperty(P_LINK, "");
    // The back up value of PropertyItem to be able to reset parameter tuning tree to initial state
    addProperty(P_BACKUP, 0.0);
    // The domain name of corresponding ISample's registered parameter
    addProperty(P_DOMAIN, "");
}

// ----------------------------------------------------------------------------

//! Sets current value to the original PropertyItem of MultiLayerItem/InstrumentItem.

void ParameterItem::propagateValueToLink(double newValue)
{
    setValue(newValue);

    if (SessionItem *item = linkedItem())
            item->setValue(newValue);
}

//! Returns corresponding linked item in MultiLayerItem/IsntrumentItem

SessionItem *ParameterItem::linkedItem()
{
    const SessionItem *jobItem = ModelPath::ancestor(this, Constants::JobItemType);
    Q_ASSERT(jobItem);
    QString link = jobItem->itemName() + "/" + getItemValue(P_LINK).toString();
    return model()->itemForIndex(ModelPath::getIndexFromPath(model(), link));
}

//! Restore the value from backup and propagate it to the linked item.

void ParameterItem::restoreFromBackup()
{
    double newValue = getItemValue(P_BACKUP).toDouble();
    propagateValueToLink(newValue);
}

//! Returns true if item can be used to drag-and-drop to FitParameterContainer.
//! In other words, if translation to domain name is implemented and valid.

bool ParameterItem::isFittable() const
{
    static const QVector<QPair<QStringList, QStringList>> black_list {
        {// Global scope
            {
                QString()
            },
            {
                Constants::DistributionSigmaFactor
            }
        },
        {// Instrument scope
            {
                Constants::GISASInstrumentType,
                Constants::OffSpecInstrumentType,
                Constants::SpecularInstrumentType
            },
            {// Distribution types
                Constants::DistributionGateType, Constants::DistributionLorentzType,
                Constants::DistributionGaussianType, Constants::DistributionLogNormalType,
                Constants::DistributionCosineType, Constants::DistributionTrapezoidType,

                // Detector axes
                SphericalDetectorItem::P_PHI_AXIS, SphericalDetectorItem::P_ALPHA_AXIS,
                RectangularDetectorItem::P_X_AXIS, RectangularDetectorItem::P_Y_AXIS,
                OffSpecInstrumentItem::P_ALPHA_AXIS,

                // Rectangular detector positioning
                RectangularDetectorItem::P_ALIGNMENT, RectangularDetectorItem::P_NORMAL,
                RectangularDetectorItem::P_DIRECTION, RectangularDetectorItem::P_U0,
                RectangularDetectorItem::P_V0, RectangularDetectorItem::P_DBEAM_U0,
                RectangularDetectorItem::P_DBEAM_V0, RectangularDetectorItem::P_DISTANCE,

                // Detector resolution
                Constants::ResolutionFunction2DGaussianType,

                // Beam angle parameters
                BeamItem::P_INCLINATION_ANGLE, BeamItem::P_AZIMUTHAL_ANGLE
            }
        }
    };
    Q_ASSERT(ModelPath::ancestor(this, Constants::JobItemType));

    const QString& par_path = FitParameterHelper::getParameterItemPath(this);

    for (const auto& item : black_list) {
        if (item.first.size() == 1 && item.first[0].isNull()) { // checking global scope
            if (containsNames(par_path, item.second))
                return false;
        } else { // checking everything else
            if (containsNames(par_path, item.first) && containsNames(par_path, item.second))
                return false;
        }
    }
    return true;
}

// ----------------------------------------------------------------------------

ParameterContainerItem::ParameterContainerItem()
    : SessionItem(Constants::ParameterContainerType)
{
    const QString T_CHILDREN = "children tag";
    registerTag(T_CHILDREN, 0, -1, QStringList() << Constants::ParameterLabelType);
    setDefaultTag(T_CHILDREN);
}

namespace {
bool containsNames(const QString& text, const QStringList& names)
{
    for (const auto& name : names)
        if (text.contains(name))
            return true;
    return false;
}
}
