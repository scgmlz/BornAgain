//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Sample/Scattering/IBornFF.h
//! @brief     Defines interface IBornFF.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef USER_API
#ifndef BORNAGAIN_SAMPLE_SCATTERING_IBORNFF_H
#define BORNAGAIN_SAMPLE_SCATTERING_IBORNFF_H

#include "Sample/Scattering/IFormFactor.h"

class IShape;

//! Nested structure that holds slicing effects on position and removed parts.

//! @ingroup formfactors_internal

struct SlicingEffects {
    kvector_t position;
    double dz_bottom;
    double dz_top;
};

//! Abstract base class for Born form factors.
//!
//! In contrast to the generic IFormFactor, a Born form factor does not depend
//! on the incoming and outgoing wave vectors ki and kf, except through their
//! difference, the scattering vector q=ki-kf.

//! @ingroup formfactors_internal

class IBornFF : public IFormFactor {
public:
    IBornFF();
    IBornFF(const NodeMeta& meta, const std::vector<double>& PValues);
    ~IBornFF();

    IBornFF* clone() const override = 0;

    void setAmbientMaterial(const Material&) override {}

    complex_t evaluate(const WavevectorInfo& wavevectors) const override;

#ifndef SWIG
    Eigen::Matrix2cd evaluatePol(const WavevectorInfo& wavevectors) const override;
#endif

    virtual double bottomZ(const IRotation& rotation) const override;
    virtual double topZ(const IRotation& rotation) const override;

    //! Returns scattering amplitude for complex scattering wavevector q=k_i-k_f.
    //! This method is public only for convenience of plotting form factors in Python.
    virtual complex_t evaluate_for_q(cvector_t q) const = 0;

protected:
    //! Default implementation only allows rotations along z-axis
    bool canSliceAnalytically(const IRotation& rot) const override;

#ifndef SWIG
    //! Returns scattering amplitude for complex scattering wavevector q=k_i-k_f in case
    //! of matrix interactions. Default implementation calls evaluate_for_q(q) and
    //! multiplies with the unit matrix.
    virtual Eigen::Matrix2cd evaluate_for_q_pol(cvector_t q) const;
#endif

    //! IShape object, used to retrieve vertices (which may be approximate in the case
    //! of round shapes). For soft particles, this will be a hard mean shape.
    std::unique_ptr<IShape> m_shape;

    //! Helper method for slicing
    static SlicingEffects computeSlicingEffects(ZLimits limits, const kvector_t& position,
                                                double height);

    //! Calculates the z-coordinate of the lowest vertex after rotation
    static double BottomZ(const std::vector<kvector_t>& vertices, const IRotation& rotation);

    //! Calculates the z-coordinate of the highest vertex after rotation
    static double TopZ(const std::vector<kvector_t>& vertices, const IRotation& rotation);
};

#endif // BORNAGAIN_SAMPLE_SCATTERING_IBORNFF_H
#endif // USER_API
