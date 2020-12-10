//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Device/Instrument/Instrument.h
//! @brief     Defines class Instrument.
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
#ifndef BORNAGAIN_DEVICE_INSTRUMENT_INSTRUMENT_H
#define BORNAGAIN_DEVICE_INSTRUMENT_INSTRUMENT_H

#include "Device/Beam/Beam.h"
#include <memory>

class IDetector;
class IDetector2D;

//! Assembles beam, detector and their relative positions with respect to the sample.
//! @ingroup simulation_internal

class Instrument : public INode {
public:
    Instrument();
    Instrument(const Beam& beam, const IDetector& detector);
    Instrument(const Instrument& other);
    Instrument& operator=(const Instrument& other);

    virtual ~Instrument();

    void accept(INodeVisitor* visitor) const final { visitor->visit(this); }

    Beam& beam() { return m_beam; }
    const Beam& beam() const { return m_beam; }
    void setBeam(const Beam& beam);

    //! Sets the beam wavelength and incoming angles
    void setBeamParameters(double wavelength, double alpha_i, double phi_i);

    const IDetector* getDetector() const;
    IDetector& detector();
    const IDetector& detector() const;

    IDetector2D& detector2D();
    const IDetector2D& detector2D() const;

    //! Sets the detector (axes can be overwritten later)
    void setDetector(const IDetector& detector);

    //! init detector with beam settings
    void initDetector();

    std::vector<const INode*> getChildren() const;

protected:
    Beam m_beam;
    std::unique_ptr<IDetector> m_detector;
};

#endif // BORNAGAIN_DEVICE_INSTRUMENT_INSTRUMENT_H
#endif // USER_API
