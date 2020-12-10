//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Sample/Interference/SSCApproximationStrategy.h
//! @brief     Defines class SSCApproximationStrategy.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifdef SWIG
#error no need to expose this header to Swig
#endif

#ifndef USER_API
#ifndef BORNAGAIN_SAMPLE_INTERFERENCE_SSCAPPROXIMATIONSTRATEGY_H
#define BORNAGAIN_SAMPLE_INTERFERENCE_SSCAPPROXIMATIONSTRATEGY_H

#include "Sample/Interference/IInterferenceFunctionStrategy.h"
#include <Eigen/StdVector>

class InterferenceFunctionRadialParaCrystal;
class SimulationElement;

//! Strategy class to compute the total scattering from a particle layout
//! in the size-spacing correlation approximation.
//! @ingroup algorithms_internal

class SSCApproximationStrategy : public IInterferenceFunctionStrategy {
public:
    SSCApproximationStrategy(const std::vector<FormFactorCoherentSum>& weighted_formfactors,
                             const InterferenceFunctionRadialParaCrystal* iff,
                             SimulationOptions sim_params, bool polarized, double kappa);

private:
    double scalarCalculation(const SimulationElement& sim_element) const override;
    double polarizedCalculation(const SimulationElement& sim_element) const override;

    void init(const std::vector<FormFactorCoherentSum>& ff_wrappers);

    complex_t
    getCharacteristicSizeCoupling(double qp,
                                  const std::vector<FormFactorCoherentSum>& ff_wrappers) const;
    complex_t calculatePositionOffsetPhase(double qp, double radial_extension) const;

    std::unique_ptr<InterferenceFunctionRadialParaCrystal> m_iff;
    double m_kappa;
    double m_mean_radius;
};

#endif // BORNAGAIN_SAMPLE_INTERFERENCE_SSCAPPROXIMATIONSTRATEGY_H
#endif // USER_API
