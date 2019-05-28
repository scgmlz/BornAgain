// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/InstrumentWidgets/DetectorPresenter.h
//! @brief     Defines class DetectorPresenter
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef DETECTORPRESENTER_H
#define DETECTORPRESENTER_H

#include "ItemComboWidget.h"

//! Contains stack of detector editors and the logic to show proper editor for certain type
//! of detector item (SphericalDetectorEditor or FlatDetectorEditor).
//! Main component of GISASDetectorEditor.

class BA_CORE_API_ DetectorPresenter : public ItemComboWidget
{
    Q_OBJECT

public:
    explicit DetectorPresenter(QWidget* parent = nullptr);

protected:
    QString itemPresentation() const override;
    QStringList activePresentationList(SessionItem* item) override;
};

#endif  // DETECTORPRESENTER_H
