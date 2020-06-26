// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Instrument/DetectionProperties.h
//! @brief     Defines class DetectionProperties.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef DETECTIONPROPERTIES_H
#define DETECTIONPROPERTIES_H

#include "EigenCore.h"
#include "INode.h"
#include "Vectors3D.h"
#include "WinDllMacros.h"

//! Detector properties (efficiency, transmission).
//! @ingroup detector

class BA_CORE_API_ DetectionProperties : public INode
{
public:
    DetectionProperties();
    DetectionProperties(const DetectionProperties& other);

    virtual ~DetectionProperties();

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
    void init_parameters();
    //! Verify if the given analyzer properties are physical
    bool checkAnalyzerProperties(const kvector_t direction, double efficiency,
                                 double total_transmission) const;

    kvector_t m_direction;       //!< direction of polarization analysis
    double m_efficiency;         //!< efficiency of polarization analysis
    double m_total_transmission; //!< total transmission of polarization analysis
};

#endif // DETECTIONPROPERTIES_H
