// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Vector/EigenCore.h
//! @brief     Include to deal with Eigen alignment centrally
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_CORE_VECTOR_EIGENCORE_H
#define BORNAGAIN_CORE_VECTOR_EIGENCORE_H

// This include file is introduced to deal with Eigen alignment
// see http://eigen.tuxfamily.org/dox-devel/group__TopicStructHavingEigenMembers.html

#ifndef SWIG
#ifdef _WIN32
#include <Eigen/Core>
#else
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#include <Eigen/Core>
#pragma GCC diagnostic pop
#endif
#endif

#endif // BORNAGAIN_CORE_VECTOR_EIGENCORE_H
