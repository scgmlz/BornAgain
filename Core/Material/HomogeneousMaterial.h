// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Material/HomogeneousMaterial.h
//! @brief     Defines and implements class HomogeneousMaterial.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef HOMOGENEOUSMATERIAL_H
#define HOMOGENEOUSMATERIAL_H

#include "INamed.h"
#include "Complex.h"
#include "Vectors3D.h"
#include "EigenCore.h"
#include <vector>

class Transform3D;
class WavevectorInfo;

//! An homogeneous material with a refractive index and (optionally) a magnetic field.
//! @ingroup materials

class BA_CORE_API_ HomogeneousMaterial : public INamed
{
public:
    //! Constructs a default material (vacuum).
    HomogeneousMaterial();

    //! Constructs a material with _name_ and _refractive_index_.
    HomogeneousMaterial(const std::string &name, const complex_t refractive_index,
                        kvector_t magnetization=kvector_t());

    //! Constructs a material with _name_ and refractive_index parameters
    //! delta and beta (n = 1 - delta + i*beta).
    HomogeneousMaterial(const std::string &name, double refractive_index_delta,
                        double refractive_index_beta, kvector_t magnetization=kvector_t());
    ~HomogeneousMaterial() {}

    //! Constructs a material with inverted magnetization
    HomogeneousMaterial inverted() const;

    complex_t refractiveIndex() const;
    complex_t refractiveIndex2() const;
    void setRefractiveIndex(const complex_t refractive_index);

    //! Indicates whether the interaction with the material is scalar.
    //! This means that different polarization states will be diffracted equally
    bool isScalarMaterial() const;

    bool isMagneticMaterial() const { return !isScalarMaterial(); }

    //! Get the magnetization (in A/m)
    kvector_t magnetization() const;

    //! Set the magnetizationd (in A/m)
    void setMagnetization(const kvector_t magnetization);

    //! Returns \pi/(wl*wl) - sld, with wl being the wavelength
    complex_t scalarSubstrSLD(const WavevectorInfo& wavevectors) const;

#ifndef SWIG
    //! Returns \pi/(wl*wl) - sld matrix with magnetization corrections. wl denotes the wavelength
    Eigen::Matrix2cd polarizedSubstrSLD(const WavevectorInfo& wavevectors) const;
#endif

    HomogeneousMaterial transformedMaterial(const Transform3D& transform) const;

    friend BA_CORE_API_ std::ostream& operator<<(
            std::ostream& ostr, const HomogeneousMaterial& mat);
private:
    void print(std::ostream &ostr) const;

    complex_t m_refractive_index; //!< complex index of refraction
    kvector_t m_magnetization; //!< magnetization
};

// Functions for calculating the reduced potential, used for obtaining the Fresnel coefficients:
complex_t ScalarReducedPotential(complex_t n, kvector_t k, double n_ref);

#ifndef SWIG
Eigen::Matrix2cd PolarizedReducedPotential(complex_t n, kvector_t b_field,
                                           kvector_t k, double n_ref);
#endif

// Comparison operators:
BA_CORE_API_ bool operator==(const HomogeneousMaterial& left, const HomogeneousMaterial& right);
BA_CORE_API_ bool operator!=(const HomogeneousMaterial& left, const HomogeneousMaterial& right);

#endif // HOMOGENEOUSMATERIAL_H
