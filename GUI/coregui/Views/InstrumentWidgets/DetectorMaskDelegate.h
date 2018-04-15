// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/InstrumentWidgets/DetectorMaskDelegate.h
//! @brief     Defines class DetectorMaskDelegate
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef DETECTORMASKDELEGATE_H
#define DETECTORMASKDELEGATE_H

#include "WinDllMacros.h"
#include <QModelIndex>
#include <QObject>

class InstrumentModel;
class IntensityDataItem;
class MaskEditor;
class SessionModel;
class DetectorItem;

//! The DetectorMaskDelegate class provides synchronization between DetectorItem (defined
//! in InstrumentModel) and temporary IntensityDataItem (defined in temporary SessionModel).
//! The later one is used by MaskEditor for mask drawing.

class BA_CORE_API_ DetectorMaskDelegate : public QObject
{
    Q_OBJECT

public:
    DetectorMaskDelegate(QObject* parent);

    void initMaskEditorContext(MaskEditor* maskEditor, InstrumentModel* instrumentModel,
                               DetectorItem* detectorItem);

private:
    void createIntensityDataItem();

    SessionModel* m_tempIntensityDataModel;
    InstrumentModel* m_instrumentModel;
    DetectorItem* m_detectorItem;
    IntensityDataItem* m_intensityItem;
};

#endif // DETECTORMASKDELEGATE_H

