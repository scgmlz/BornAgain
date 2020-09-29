// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Detector/DetectionProperties.h
//! @brief     Defines class DetectionProperties.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_CORE_DETECTOR_DETECTIONPROPERTIES_H
#define BORNAGAIN_CORE_DETECTOR_DETECTIONPROPERTIES_H

#include "Core/Parametrization/INode.h"
#include "Core/Vector/EigenCore.h"
#include "Core/Vector/Vectors3D.h"

//! Detector properties (efficiency, transmission).
//! @ingroup detector

class DetectionProperties : public INode
{
public:
    DetectionProperties(kvector_t direction, double efficiency, double total_transmission);
    DetectionProperties();
    DetectionProperties(const DetectionProperties& other);

    virtual ~DetectionProperties() = default;

    //! Sets the polarization analyzer characteristics of the detector
    void setAnalyzerProperties(const kvector_t direction, double efficiency,
                               double total_transmission);

    //! Return the polarization density matrix (in spin basis along z-axis)
    Eigen::Matrix2cd analyzerOperator() const;

    //! Retrieve the analyzer characteristics
    kvector_t analyzerDirection() const;
    double analyzerEfficiency() const; //!< will always return positive value
    double analyzerTotalTransmission() const;

    void accept(INodeVisitor* visitor) const final { visitor->visit(this); }

private:
    //! Verify if the given analyzer properties are physical
    bool checkAnalyzerProperties(const kvector_t direction, double efficiency,
                                 double total_transmission) const;

    kvector_t m_direction;       //!< direction of polarization analysis
    double m_efficiency;         //!< efficiency of polarization analysis
    double m_total_transmission; //!< total transmission of polarization analysis
};

#endif // BORNAGAIN_CORE_DETECTOR_DETECTIONPROPERTIES_H
