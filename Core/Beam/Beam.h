// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Beam/Beam.h
//! @brief     Defines class Beam.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_CORE_BEAM_BEAM_H
#define BORNAGAIN_CORE_BEAM_BEAM_H

#include "Core/Parametrization/INode.h"
#include "Core/Vector/EigenCore.h"
#include "Core/Vector/Vectors3D.h"

class IFootprintFactor;

//! Beam defined by wavelength, direction and intensity.
//! @ingroup beam

class BA_CORE_API_ Beam : public INode
{
public:
    Beam(double wavelength, double alpha, double phi, double intensity);

    Beam(const Beam& other);
    Beam& operator=(const Beam& other);

    virtual ~Beam();

    static Beam horizontalBeam();

    //! Returns the wavevector
    kvector_t getCentralK() const;

    //! Sets the wavevector in terms of wavelength and incoming angles
    void setCentralK(double wavelength, double alpha_i, double phi_i);

    //! Returns the beam intensity in neutrons/sec
    double getIntensity() const { return m_intensity; }

    //! Sets the beam intensity in neutrons/sec
    void setIntensity(double intensity) { m_intensity = intensity; }

    //! Returns footprint factor.
    const IFootprintFactor* footprintFactor() const;

    //! Sets footprint factor to the beam.
    void setFootprintFactor(const IFootprintFactor& shape_factor);

    //! Sets beam to sample width ratio in footprint factor.
    void setWidthRatio(double width_ratio);

    //! Sets the polarization density matrix according to the given Bloch vector
    void setPolarization(const kvector_t bloch_vector);

    kvector_t getBlochVector() const;

#ifndef SWIG
    //! Returns the polarization density matrix (in spin basis along z-axis)
    Eigen::Matrix2cd getPolarization() const;
#endif

    double getWavelength() const { return m_wavelength; }
    double getAlpha() const { return m_alpha; }
    double getPhi() const { return m_phi; }

    void accept(INodeVisitor* visitor) const override { visitor->visit(this); }
    std::vector<const INode*> getChildren() const override;

private:
    double m_wavelength;
    double m_alpha;
    double m_phi;
    double m_intensity;                               //!< beam intensity (neutrons/sec)
    std::unique_ptr<IFootprintFactor> m_shape_factor; //!< footprint correction handler
    kvector_t m_bloch_vector; //!< Bloch vector encoding the beam's polarization
};

#endif // BORNAGAIN_CORE_BEAM_BEAM_H
