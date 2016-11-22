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

#include "IMaterial.h"
#include <vector>

//! An homogeneous material with a refractive index.
//! @ingroup materials

class BA_CORE_API_ HomogeneousMaterial : public IMaterial
{
public:
    //! Constructs a material with _name_ and _refractive_index_.
    HomogeneousMaterial(const std::string &name, const complex_t refractive_index)
        : IMaterial(name), m_refractive_index(refractive_index)
    {}

    //! Constructs a material with _name_ and refractive_index parameters
    //! delta and beta (n = 1 - delta + i*beta).
    HomogeneousMaterial(const std::string &name, double refractive_index_delta,
                        double refractive_index_beta)
        : IMaterial(name)
        , m_refractive_index(complex_t(1.0 - refractive_index_delta, refractive_index_beta)) {}
    virtual ~HomogeneousMaterial() {}

    virtual HomogeneousMaterial* clone() const {
        return new HomogeneousMaterial(getName(), getRefractiveIndex()); }
    virtual HomogeneousMaterial* cloneInverted() const { return clone(); }

    virtual complex_t getRefractiveIndex() const { return m_refractive_index; }
    void setRefractiveIndex(const complex_t refractive_index) {
        m_refractive_index = refractive_index; }

#ifndef SWIG
    //! Get the scattering matrix (~potential V) from the material.
    //! This matrix appears in the full three-dimensional Schroedinger equation.
    virtual Eigen::Matrix2cd getScatteringMatrix(double) const {
        return m_refractive_index * m_refractive_index * Eigen::Matrix2cd::Identity(); }
#endif

    //! Create a new material that is transformed with respect to this one
    virtual const IMaterial* createTransformedMaterial(const Transform3D&) const {
        return new HomogeneousMaterial(getName(), getRefractiveIndex()); }

protected:
    virtual void print(std::ostream &ostr) const {
        ostr << "HomMat:" << getName() << "<" << this << ">{ "
             << "R=" << m_refractive_index << "}"; }

    complex_t m_refractive_index; //!< complex index of refraction
};

#endif // HOMOGENEOUSMATERIAL_H
