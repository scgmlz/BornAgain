// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Instrument/DetectionProperties.h
//! @brief     Defines class DetectionProperties.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef DETECTIONPROPERTIES_H
#define DETECTIONPROPERTIES_H

#include "WinDllMacros.h"
#include "EigenCore.h"
#include "Vectors3D.h"

//! Detector properties (efficiency, transmission).
//! @ingroup simulation

class BA_CORE_API_ DetectionProperties {
public:
    DetectionProperties();

    //! Sets the polarization analyzer characteristics of the detector
    void setAnalyzerProperties(const kvector_t direction, double efficiency,
                               double total_transmission);

    //! Gets the polarization density matrix (in spin basis along z-axis)
    Eigen::Matrix2cd analyzerOperator() const;

private:
    //! Initialize polarization
    void initPolarizationOperator();

    Eigen::Matrix2cd calculateAnalyzerOperator(
        const kvector_t direction, double efficiency, double total_transmission = 1.0) const;

    //! Verify if the given analyzer properties are physical
    bool checkAnalyzerProperties(const kvector_t direction, double efficiency,
                                 double total_transmission) const;

    Eigen::Matrix2cd m_analyzer_operator; //!< polarization analyzer operator
};

#endif // DETECTIONPROPERTIES_H
