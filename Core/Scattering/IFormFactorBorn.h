// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Scattering/IFormFactorBorn.h
//! @brief     Defines pure virtual interface class IFormFactorBorn.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_CORE_SCATTERING_IFORMFACTORBORN_H
#define BORNAGAIN_CORE_SCATTERING_IFORMFACTORBORN_H

#include "Core/Scattering/IFormFactor.h"
#include "Core/Shapes/IShape.h"
#include "Core/Vector/Vectors3D.h"

struct SlicingEffects; // defined below

//! Pure virtual base class for Born form factors.
//!
//! In contrast to the generic IFormFactor, a Born form factor does not depend
//! on the incoming and outgoing wave vectors ki and kf, except through their
//! difference, the scattering vector q=ki-kf.

//! @ingroup formfactors_internal

class IFormFactorBorn : public IFormFactor
{
public:
    IFormFactorBorn() = default;
    IFormFactorBorn(const NodeMeta& meta, const std::vector<double>& PValues);

    IFormFactorBorn* clone() const override = 0;

    void setAmbientMaterial(Material) override {}

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
    std::unique_ptr<IShape> mP_shape;

    //! Helper method for slicing
    SlicingEffects computeSlicingEffects(ZLimits limits, const kvector_t& position,
                                         double height) const;

    //! Calculates the z-coordinate of the lowest vertex after rotation
    static double BottomZ(const std::vector<kvector_t>& vertices, const IRotation& rotation);

    //! Calculates the z-coordinate of the highest vertex after rotation
    static double TopZ(const std::vector<kvector_t>& vertices, const IRotation& rotation);
};

//! Nested structure that holds slicing effects on position and removed parts.

//! @ingroup formfactors_internal

struct SlicingEffects {
    kvector_t position;
    double dz_bottom;
    double dz_top;
};

#ifdef POLYHEDRAL_DIAGNOSTIC
//! Information about the latest form factor evaluation. Not thread-safe.
//! Used only by external test program.
class Diagnosis
{
public:
    int maxOrder;
    int nExpandedFaces;
    int debmsg;
    bool request_convergence;
    bool operator!=(const Diagnosis& other) const
    {
        return maxOrder != other.maxOrder || nExpandedFaces != other.nExpandedFaces;
    }
    friend std::ostream& operator<<(std::ostream& stream, const Diagnosis& diag)
    {
        return stream << " [" << diag.nExpandedFaces << ":" << diag.maxOrder << "]";
    }
};
#endif

#endif // BORNAGAIN_CORE_SCATTERING_IFORMFACTORBORN_H
