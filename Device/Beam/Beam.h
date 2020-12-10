//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Device/Beam/Beam.h
//! @brief     Defines class Beam.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_DEVICE_BEAM_BEAM_H
#define BORNAGAIN_DEVICE_BEAM_BEAM_H

#include "Base/Vector/Direction.h"
#include "Base/Vector/EigenCore.h"
#include "Param/Node/INode.h"

class IFootprintFactor;

//! An incident neutron or x-ray beam.
//! @ingroup beam

class Beam : public INode {
public:
    Beam(double intensity, double wavelength, const Direction& direction);

    Beam(const Beam& other);
    Beam& operator=(const Beam& other);

    virtual ~Beam();

    static Beam horizontalBeam();

    void accept(INodeVisitor* visitor) const override { visitor->visit(this); }
    std::vector<const INode*> getChildren() const override;

    //! Returns the beam intensity in neutrons/sec
    double intensity() const { return m_intensity; }
    double wavelength() const { return m_wavelength; }
    // Direction& direction() { return m_direction; }
    Direction direction() const { return {m_alpha, m_phi}; } // TODO -> const .. &
    //! Returns the wavevector
    kvector_t getCentralK() const;

    kvector_t getBlochVector() const;
    //! Returns footprint factor.
    const IFootprintFactor* footprintFactor() const;
#ifndef SWIG
    //! Returns the polarization density matrix (in spin basis along z-axis)
    Eigen::Matrix2cd getPolarization() const;
#endif

    void setWavelength(double wavelength);
    void setDirection(const Direction& direction);
    void setInclination(const double alpha);
    //! Sets the beam intensity in neutrons/sec
    void setIntensity(double intensity) { m_intensity = intensity; }
    //! Sets footprint factor to the beam.
    void setFootprintFactor(const IFootprintFactor& shape_factor);
    //! Sets beam to sample width ratio in footprint factor.
    void setWidthRatio(double width_ratio);
    //! Sets the polarization density matrix according to the given Bloch vector
    void setPolarization(const kvector_t bloch_vector);

private:
    Beam();             // needed by Swig
    double m_intensity; //!< beam intensity (neutrons/sec)
    double m_wavelength;
    // Direction m_direction; TODO
    double m_alpha;
    double m_phi;
    std::unique_ptr<IFootprintFactor> m_shape_factor; //!< footprint correction handler
    kvector_t m_bloch_vector; //!< Bloch vector encoding the beam's polarization
};

#endif // BORNAGAIN_DEVICE_BEAM_BEAM_H
