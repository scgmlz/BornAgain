// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/DepthProbeInstrumentItem.h
//! @brief     Defines DepthProbeInstrumentItem class
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_MODELS_DEPTHPROBEINSTRUMENTITEM_H
#define BORNAGAIN_GUI_COREGUI_MODELS_DEPTHPROBEINSTRUMENTITEM_H

#include "GUI/coregui/Models/InstrumentItems.h"

class DepthProbeSimulation;

//! Depth probe instrument.

class BA_CORE_API_ DepthProbeInstrumentItem : public InstrumentItem
{
public:
    static const QString P_BEAM;
    static const QString P_Z_AXIS;

    DepthProbeInstrumentItem();

    SpecularBeamItem* beamItem() const override;

    std::unique_ptr<Instrument> createInstrument() const override;
    std::vector<int> shape() const override;
    void updateToRealData(const RealDataItem* item) override;

    // FIXME switch to base Simulation class after InstrumentItem refactoring and
    // after Simulation gets createUnitConverter method
    std::unique_ptr<DepthProbeSimulation> createSimulation() const;

    std::unique_ptr<IUnitConverter> createUnitConverter() const;
};

#endif // BORNAGAIN_GUI_COREGUI_MODELS_DEPTHPROBEINSTRUMENTITEM_H
