// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Vector/Transform3D.h
//! @brief      Declares class Transform3D.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef TRANSFORM3D_H
#define TRANSFORM3D_H

#include "Vectors3D.h"
#include "Complex.h"
#include "EigenCore.h"

#include <vector>

//! Vector transformations in three dimensions.
//! @ingroup tools_internal

class BA_CORE_API_ Transform3D {
public:
    enum ERotationType { EULER, XAXIS, YAXIS, ZAXIS };

    //! Constructs unit transformation
    Transform3D();

    //! Copy constructor
    Transform3D(const Transform3D& other);

    //! Destructor
    ~Transform3D() {}

    //! Clones the transformation
    Transform3D *clone() const;

    //! Creates identity transformation (default)
    static Transform3D createIdentity();

    //! Creates rotation around x-axis
    static Transform3D createRotateX(double phi);

    //! Creates rotation around y-axis
    static Transform3D createRotateY(double phi);

    //! Creates rotation around z-axis
    static Transform3D createRotateZ(double phi);

    //! Creates rotation defined by Euler angles
    static Transform3D createRotateEuler(double alpha, double beta, double gamma);

    //! Calculates the Euler angles corresponding to the rotation
    void calculateEulerAngles(double *p_alpha, double *p_beta, double *p_gamma) const;

    //! Calculates the rotation angle for a rotation around the x-axis alone
    //! Only meaningfull if the actual rotation is around the x-axis
    double calculateRotateXAngle() const;

    //! Calculates the rotation angle for a rotation around the y-axis alone
    //! Only meaningfull if the actual rotation is around the y-axis
    double calculateRotateYAngle() const;

    //! Calculates the rotation angle for a rotation around the z-axis alone
    //! Only meaningfull if the actual rotation is around the z-axis
    double calculateRotateZAngle() const;

    //! Returns the inverse transformation.
    Transform3D getInverse() const;

    //! Return transformed vector _v_.
    kvector_t transformed(const kvector_t& v) const;

    //! Return transformed vector _v_.
    cvector_t transformed(const cvector_t& v) const;

    //! Return transformed vector _v_.
    kvector_t transformedInverse(const kvector_t& v) const;

    //! Return transformed vector _v_.
    cvector_t transformedInverse(const cvector_t& v) const;

    //! Composes two transformations
    Transform3D operator*(const Transform3D &other) const;

    //! Provides equality operator
    bool operator==(const Transform3D &other) const;

    //! Retrieve the rotation type (general, around x, y or z-axis)
    ERotationType getRotationType() const;

    //! Determine if the transformation is trivial (identity)
    bool isIdentity() const;

    friend std::ostream& operator<<(std::ostream& ostr, const Transform3D& m)
    { m.print(ostr); return ostr; }

    void print(std::ostream& ostr) const;

    bool isXRotation() const;
    bool isYRotation() const;
    bool isZRotation() const;
private:
#ifndef SWIG
    Transform3D(const Eigen::Matrix3d &matrix);
    Eigen::Matrix3d m_matrix;
    Eigen::Matrix3d m_inverse_matrix;
#endif
};

//! Calculates the z-coordinate of the lowest vertex after rotation
double BottomZ(const std::vector<kvector_t>& vertices, const Transform3D& rotation);

//! Calculates the z-coordinate of the highest vertex after rotation
double TopZ(const std::vector<kvector_t>& vertices, const Transform3D& rotation);

#endif // TRANSFORM3D_H
