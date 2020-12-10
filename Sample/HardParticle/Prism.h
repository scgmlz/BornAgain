//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Sample/HardParticle/Prism.h
//! @brief     Defines class Prism.
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
#ifndef BORNAGAIN_SAMPLE_HARDPARTICLE_PRISM_H
#define BORNAGAIN_SAMPLE_HARDPARTICLE_PRISM_H

#include "Sample/HardParticle/PolyhedralComponents.h"
#include "Sample/HardParticle/PolyhedralTopology.h"
#include <memory>

class Prism {
public:
    Prism() = delete;
    Prism(const Prism&) = delete;
    Prism(bool symmetry_Ci, double height, const std::vector<kvector_t>& vertices);
    double area() const;
    const std::vector<kvector_t>& vertices(); //! needed for topZ, bottomZ computation
    complex_t evaluate_for_q(const cvector_t& q) const;
    // complex_t evaluate_centered(const cvector_t& q) const;
private:
    std::unique_ptr<PolyhedralFace> m_base;
    double m_height;
    std::vector<kvector_t> m_vertices; //! for topZ, bottomZ computation only
};

#endif // BORNAGAIN_SAMPLE_HARDPARTICLE_PRISM_H
#endif // USER_API
