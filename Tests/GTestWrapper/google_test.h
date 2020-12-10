//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/GTestWrapper/google_test.h
//! @brief     Wraps gtest.h, and provides tests for complex number.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_TESTS_GTESTWRAPPER_GOOGLE_TEST_H
#define BORNAGAIN_TESTS_GTESTWRAPPER_GOOGLE_TEST_H

#ifdef _MSC_VER
#define _VARIADIC_MAX 10
#endif

#ifdef _WIN32
#pragma warning(push)
#pragma warning(disable : 4275)
#include <gtest/gtest.h>
#pragma warning(pop)
#else
#include <gtest/gtest.h>
#endif

#include <memory>

#define EXPECT_NEAR_COMPLEX(z1, z2, eps)                                                           \
    EXPECT_NEAR(z1.real(), z2.real(), eps);                                                        \
    EXPECT_NEAR(z1.imag(), z2.imag(), eps);

#define EXPECT_NEAR_VECTOR2CD(v1, v2, eps)                                                         \
    EXPECT_NEAR_COMPLEX(v1(0), v2(0), eps);                                                        \
    EXPECT_NEAR_COMPLEX(v1(1), v2(1), eps);

#define EXPECT_NEAR_MATRIXCOEFF(c1, c2, eps)                                                       \
    EXPECT_NEAR_VECTOR2CD(c1->T1plus(), c2->T1plus(), eps);                                        \
    EXPECT_NEAR_VECTOR2CD(c1->R1plus(), c2->R1plus(), eps);                                        \
    EXPECT_NEAR_VECTOR2CD(c1->T2plus(), c2->T2plus(), eps);                                        \
    EXPECT_NEAR_VECTOR2CD(c1->R2plus(), c2->R2plus(), eps);                                        \
    EXPECT_NEAR_VECTOR2CD(c1->T1min(), c2->T1min(), eps);                                          \
    EXPECT_NEAR_VECTOR2CD(c1->R1min(), c2->R1min(), eps);                                          \
    EXPECT_NEAR_VECTOR2CD(c1->T2min(), c2->T2min(), eps);                                          \
    EXPECT_NEAR_VECTOR2CD(c1->R2min(), c2->R2min(), eps);                                          \
    EXPECT_NEAR_VECTOR2CD(c1->getKz(), c2->getKz(), eps)

#endif // BORNAGAIN_TESTS_GTESTWRAPPER_GOOGLE_TEST_H
