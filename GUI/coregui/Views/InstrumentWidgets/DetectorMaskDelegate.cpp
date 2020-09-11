// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/InstrumentWidgets/DetectorMaskDelegate.cpp
//! @brief     Implements class DetectorMaskDelegate
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/coregui/Views/InstrumentWidgets/DetectorMaskDelegate.h"
#include "GUI/coregui/Models/AxesItems.h"
#include "GUI/coregui/Models/ComboProperty.h"
#include "GUI/coregui/Models/DetectorItems.h"
#include "GUI/coregui/Models/InstrumentItems.h"
#include "GUI/coregui/Models/InstrumentModel.h"
#include "GUI/coregui/Models/IntensityDataItem.h"
#include "GUI/coregui/Models/JobItemUtils.h"
#include "GUI/coregui/Models/MaskItems.h"
#include "GUI/coregui/Models/ModelPath.h"
#include "GUI/coregui/Views/MaskWidgets/MaskEditor.h"

DetectorMaskDelegate::DetectorMaskDelegate(QObject* parent)
    : QObject(parent), m_tempIntensityDataModel(new SessionModel("TempIntensityDataModel", this)),
      m_instrumentModel(nullptr), m_detectorItem(nullptr), m_intensityItem(nullptr)
{
}

void DetectorMaskDelegate::initMaskEditorContext(MaskEditor* maskEditor,
                                                 InstrumentModel* instrumentModel,
                                                 DetectorItem* detectorItem)
{
    m_instrumentModel = instrumentModel;
    m_detectorItem = detectorItem;

    ASSERT(m_instrumentModel);
    ASSERT(m_detectorItem);

    createIntensityDataItem();
    m_detectorItem->createMaskContainer();

    maskEditor->setMaskContext(m_instrumentModel,
                               m_instrumentModel->indexOfItem(m_detectorItem->maskContainerItem()),
                               m_intensityItem);
}

//! Creates IntensityDataItem from DetectorItem for later usage in MaskEditor.
//! As amplitude, value 1.0 is set for each bin.
//! The object additionally tuned to appear nicely on ColorMap plot.
void DetectorMaskDelegate::createIntensityDataItem()
{
    m_tempIntensityDataModel->clear();

    m_intensityItem =
        dynamic_cast<IntensityDataItem*>(m_tempIntensityDataModel->insertNewItem("IntensityData"));
    ASSERT(m_intensityItem);

    m_intensityItem->getItem(IntensityDataItem::P_PROJECTIONS_FLAG)->setEnabled(false);
    m_intensityItem->setItemValue(IntensityDataItem::P_IS_INTERPOLATED, false);

    auto& zAxisItem = m_intensityItem->item<AmplitudeAxisItem>(IntensityDataItem::P_ZAXIS);
    zAxisItem.setItemValue(BasicAxisItem::P_IS_VISIBLE, false);
    zAxisItem.setItemValue(BasicAxisItem::P_MIN_DEG, 0.0);
    zAxisItem.setItemValue(BasicAxisItem::P_MAX_DEG, 2.0);
    zAxisItem.setItemValue(AmplitudeAxisItem::P_IS_LOGSCALE, false);
    zAxisItem.setItemValue(AmplitudeAxisItem::P_LOCK_MIN_MAX, true);

    // creating output data corresponding to the detector
    auto instrument = dynamic_cast<const GISASInstrumentItem*>(
        ModelPath::ancestor(m_detectorItem, "GISASInstrument"));
    JobItemUtils::createDefaultDetectorMap(m_intensityItem, instrument);

    m_intensityItem->getOutputData()->setAllTo(1.0);
    m_intensityItem->getItem(DataItem::P_AXES_UNITS)->setEnabled(false);
}
