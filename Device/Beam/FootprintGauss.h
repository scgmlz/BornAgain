//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Device/Beam/FootprintGauss.h
//! @brief     Defines class FootprintGauss.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_DEVICE_BEAM_FOOTPRINTGAUSS_H
#define BORNAGAIN_DEVICE_BEAM_FOOTPRINTGAUSS_H

#include "Device/Beam/IFootprintFactor.h"

//! Gaussian beam footprint.
//!
//! Beam width is the full width at half maximum.
//! @ingroup beam

class FootprintGauss : public IFootprintFactor {
public:
    FootprintGauss(const std::vector<double> P);
    FootprintGauss(double width_ratio);

    void accept(INodeVisitor* visitor) const override { visitor->visit(this); }

    FootprintGauss* clone() const override;

    //! Calculate footprint correction coefficient from the beam incident angle _alpha_.
    double calculate(double alpha) const override;

    std::string name() const override { return "FootprintGauss"; }
};

#endif // BORNAGAIN_DEVICE_BEAM_FOOTPRINTGAUSS_H
