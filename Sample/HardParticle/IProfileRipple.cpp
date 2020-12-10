//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Sample/HardParticle/IProfileRipple.cpp
//! @brief     Implements interface ISawtoothRipple.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "Sample/HardParticle/IProfileRipple.h"
#include "Sample/HardParticle/Ripples.h"
#include "Sample/Shapes/Box.h"
#include "Sample/Shapes/RippleCosine.h"
#include "Sample/Shapes/RippleSawtooth.h"

//  ************************************************************************************************
//  interface IProfileRipple
//  ************************************************************************************************

IProfileRipple::IProfileRipple(const NodeMeta& meta, const std::vector<double>& PValues)
    : IBornFF(nodeMetaUnion({{"Length", "nm", "Characteristic length", 0, INF, 1.},
                             {"Width", "nm", "Width", 0, INF, 1.},
                             {"Height", "nm", "Height", 0, INF, 1.}},
                            meta),
              PValues)
    , m_length(m_P[0])
    , m_width(m_P[1])
    , m_height(m_P[2]) {}

double IProfileRipple::radialExtension() const {
    return (m_width + m_length) / 4.0;
}

complex_t IProfileRipple::evaluate_for_q(cvector_t q) const {
    return factor_x(q.x()) * factor_yz(q.y(), q.z());
}

//  ************************************************************************************************
//  interface IProfileRectangularRipple
//  ************************************************************************************************

IProfileRectangularRipple::IProfileRectangularRipple(const NodeMeta& meta,
                                                     const std::vector<double>& PValues)
    : IProfileRipple(meta, PValues) {
    onChange();
}

//! Complex form factor.
complex_t IProfileRectangularRipple::factor_yz(complex_t qy, complex_t qz) const {
    return ripples::profile_yz_bar(qy, qz, m_width, m_height);
}

void IProfileRectangularRipple::onChange() {
    m_shape = std::make_unique<Box>(m_length, m_width, m_height);
}

//  ************************************************************************************************
//  interface ICosineRipple
//  ************************************************************************************************

ICosineRipple::ICosineRipple(const NodeMeta& meta, const std::vector<double>& PValues)
    : IProfileRipple(meta, PValues) {
    onChange();
}

//! Complex form factor.
complex_t ICosineRipple::factor_yz(complex_t qy, complex_t qz) const {
    return ripples::profile_yz_cosine(qy, qz, m_width, m_height);
}

void ICosineRipple::onChange() {
    m_shape = std::make_unique<RippleCosine>(m_length, m_width, m_height);
}

//  ************************************************************************************************
//  interface ISawtoothRipple
//  ************************************************************************************************

ISawtoothRipple::ISawtoothRipple(const NodeMeta& meta, const std::vector<double>& PValues)
    : IProfileRipple(
        nodeMetaUnion({{"AsymmetryLength", "nm", "Asymmetry of width", -INF, INF, 0.}}, meta),
        PValues)
    , m_asymmetry(m_P[3]) {
    onChange();
}

//! Complex form factor.
complex_t ISawtoothRipple::factor_yz(complex_t qy, complex_t qz) const {
    return ripples::profile_yz_triangular(qy, qz, m_width, m_height, m_asymmetry);
}

void ISawtoothRipple::onChange() {
    m_shape = std::make_unique<RippleSawtooth>(m_length, m_width, m_height, m_asymmetry);
}
